#include "Game.hpp"
#include "Isometric.hpp"

#include <raymath.h>

// Public functions

using namespace Config;

bool Game::Initialize()
{
	SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_VSYNC_HINT);

	InitWindow(windowWidth, windowHeight, gameName); // uses Config

	if (!IsWindowReady()) return false;

	SetTargetFPS(targetFPS); // uses Config

	if (!InitTextures(grassTexture, grassTilePath)) // uses Config
	{
		ShutDown();
		return false;
	}
		
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
	CloseWindow();
}

// Private functions

void Game::HandleInput(float dt)
{
	CamInputs(camera, dt);
}

void Game::Update(float dt)
{
}

void Game::Render()
{
	BeginDrawing();
	ClearBackground(BLACK);

	BeginMode2D(camera);

	RenderGrid();

	EndMode2D();

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

			position.x -= grassTexture.width / 2.f;

			DrawTextureV(grassTexture, position, WHITE);
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
}

void Game::InitCamera(Camera2D& cam)
{
	cam.offset = { GetScreenWidth() / 2.f , GetScreenHeight() / 2.f};

	cam.target = GridToIsometric
	(
		(Config::gridWidth - 1) / 2.f,
		(Config::gridHeight - 1) / 2.f
	);

	cam.rotation = 0.f;
	cam.zoom = 1.f;
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

		float distance = Config::camSpeed * dt / camera.zoom;

		Vector2 movement = Vector2Scale(direction, distance);

		cam.target = Vector2Add(cam.target, movement);
	}

	float wheel = GetMouseWheelMove();

	cam.zoom = Clamp(cam.zoom + wheel * Config::zoomIntensity, Config::minZoom, Config::maxZoom);
}
