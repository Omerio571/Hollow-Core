// My headers
#include "Config.hpp"
#include "Game.hpp"
#include "Isometric.hpp"

// outer libraries
#include <raymath.h>

// C++ libraries
#include <cmath>
#include <string>

// Public functions

using namespace Config;

bool Game::Initialize()
{
	SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_VSYNC_HINT);

	InitWindow(windowWidth, windowHeight, gameName); // uses Config

	if (!IsWindowReady()) return false;

	SetTargetFPS(targetFPS); // uses Config

	if (!InitTextures(grassTexture, grassTilePath) || 
		!InitTextures(dirtTexture, dirtTilePath) ||
		!InitTextures(hoverTexture, tileHoverIndicator) ||
		!InitTextures(buildTexture, tileBuildIndicator)) // uses Config
	{
		ShutDown();
		return false;
	}

	Tile* tile = tileMap.GetTile(8, 8);
	 
	if (tile)
		tile->terrain = TerrainType::Grass;
		
	InitCamera(camera);

	return true;
}

void Game::Run()
{
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();

		HandleInput(dt);
		Update(dt);

		Render();
	}
}

void Game::ShutDown()
{
	UninitTextures(grassTexture);
	UninitTextures(dirtTexture);

	UninitTextures(hoverTexture);
	UninitTextures(buildTexture);
	CloseWindow();
}


// Temporary

// Camera

Camera2D Game::GetCam() const
{
	return camera;
}


// Private functions

void Game::HandleInput(float dt)
{
	CamInputs(camera, dt);
	HandleMouseMode();
}

void Game::Update(float dt)
{
	UpdateHoveredTile();
}

void Game::Render()
{
	Camera2D renderCam = GetRenderCamera();

	BeginDrawing();
	ClearBackground(BLACK);

	BeginMode2D(renderCam);

	RenderGrid();

	RenderHoveredTile();

	EndMode2D();

	DisplayCurrentTilePos();

	EndDrawing();
}





// Temporary functions

void Game::RenderGrid()
{
	for (int depth = 0; depth < Config::gridWidth + Config::gridHeight - 1; ++depth)
	{
		for (int x = 0; x < Config::gridWidth; ++x)
		{
			int y = depth - x;

			if (y < 0 || y >= Config::gridHeight)
				continue;

			Vector2 position = 
				GridToIsometric
				(
					static_cast<float>(x),
					static_cast<float>(y)
				);

			position.x -= Config::halfTileWidth;

			Tile* tile = tileMap.GetTile(x, y); 
			
			if (!tile)
				continue;

			const Texture2D& texture =
				(tile->terrain == TerrainType::Grass)
				? grassTexture
				: dirtTexture;

			DrawTextureV(texture, position, tile->tileColor);
		}
	}
}

bool Game::InitTextures(Texture2D& theTexture, const char* texturePath)
{
	theTexture = LoadTexture(texturePath);

	if (theTexture.id == 0)
	{
		TraceLog(LOG_ERROR, "Failed To Load the %s!", texturePath);
		return false;
	}

	SetTextureFilter(theTexture, TEXTURE_FILTER_POINT);
	return true;
}

void Game::UninitTextures(Texture2D& theTexture)
{
	if (theTexture.id != 0)
	{
		UnloadTexture(theTexture);
	}

	theTexture = {};
}

void Game::InitCamera(Camera2D& cam)
{
	cam.offset = { GetScreenWidth() / 2.f , GetScreenHeight() / 2.f};

	cam.target = GridToIsometric
	(
		(Config::gridWidth - 1) / 2.f,
		(Config::gridHeight - 1) / 2.f
	);

	cam.rotation = Config::initRotation;
	cam.zoom = Config::initZoom;
}

void Game::CamInputs(Camera2D& cam, float dt)
{
	Vector2 direction = { 0.f, 0.f };

	if (IsKeyDown(KEY_W)) direction.y -= 1.f;
	if (IsKeyDown(KEY_S)) direction.y += 1.f;

	if (IsKeyDown(KEY_A)) direction.x -= 1.f;
	if (IsKeyDown(KEY_D)) direction.x += 1.f;

	if (direction.x != 0.f || direction.y != 0.f)
	{
		direction = Vector2Normalize(direction);

		float distance = Config::camSpeed * dt / cam.zoom;

		Vector2 movement = Vector2Scale(direction, distance);

		cam.target = Vector2Add(cam.target, movement);
	}

	float wheel = GetMouseWheelMove();

	cam.zoom = Clamp(cam.zoom + wheel * Config::zoomStep, Config::minZoom, Config::maxZoom);
}

Camera2D Game::GetRenderCamera() const
{
	Camera2D renderCam = GetCam();

	const float zoom = renderCam.zoom;

	renderCam.target.x = std::round(renderCam.target.x * zoom) / zoom;
	renderCam.target.y = std::round(renderCam.target.y * zoom) / zoom;

	renderCam.offset.x = std::round(renderCam.offset.x);
	renderCam.offset.y = std::round(renderCam.offset.y);

	return renderCam;
}

// print mouse Pos

void Game::DisplayCurrentTilePos()
{
	///////////////////////////////////////////////////////////////////////////////
	std::string isoPosStr = 
		"tilePos: " + 
		std::to_string((int)hoveredTile.x) +
		", " +
		std::to_string((int)hoveredTile.y);
	///////////////////////////////////////////////////////////////////////////////

	DrawText(isoPosStr.c_str(), 20, 20, 20, Config::textColor);
}

// Hover Tile

void Game::HandleMouseMode()
{
	if (IsKeyPressed(KEY_B) && mouseMode == MouseMode::BuildingPlacement) 
		mouseMode = MouseMode::Normal;
	else if (IsKeyPressed(KEY_B) && mouseMode == MouseMode::Normal) 
		mouseMode = MouseMode::BuildingPlacement;
}

void Game::UpdateHoveredTile()
{
	hoveredTile = IsometricToGrid(GetMousePosition(), GetRenderCamera());

	hoveredTile.x = std::floor(hoveredTile.x);
	hoveredTile.y = std::floor(hoveredTile.y);

	if (!tileMap.IsInside((int)hoveredTile.x, (int)hoveredTile.y))
	{
		hoveredTileColor = Config::invalHoverColor;
		return;
	}

	hoveredTileColor = Config::validHoverColor;
}

void Game::RenderHoveredTile()
{
	const Texture2D& texture = (mouseMode == MouseMode::Normal) ? hoverTexture : buildTexture;

	Vector2 position = GridToIsometric(hoveredTile.x, hoveredTile.y);

	position.x -= texture.width / 2.f;

	DrawTextureV(texture, position, hoveredTileColor);
}

