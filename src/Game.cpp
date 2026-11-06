#include "Game.hpp"

// Public functions

using namespace Config;

bool Game::Initialize()
{
	SetConfigFlags(FLAG_WINDOW_TOPMOST && FLAG_VSYNC_HINT);

	InitWindow(windowWidth, windowHeight, gameName); // uses Config

	SetTargetFPS(targetFPS); // uses Config

	if (!IsWindowReady()) return false;
	else return true;
}

void Game::Run()
{
	while (!WindowShouldClose())
	{
		HandleInput();

		float dt = GetFrameTime();
		Update(dt);

		Render();
	}
}

void Game::ShutDown()
{
	CloseWindow();
}

// Private functions

void Game::Update(float dt)
{
}

void Game::HandleInput()
{
}

void Game::Render()
{
	BeginDrawing();

	EndDrawing();
}