#pragma once

// Outer Headers
#include <raylib.h>

// My Headers
#include "Config.hpp"


class Game
{
public:
	// Prepare EVERYTHING the game needs before it begins running
	bool Initialize();

	// Manage the game's execution until the player exits 
	// Handles co-ordination between HandleInput, Render and Update
	void Run();

	// Release resources acquired during initialization and gameplay
	void ShutDown();

private:
	// Handles the players actions
	void HandleInput(float dt);

	// Advance the world's state
	void Update(float dt);

	// Display the current Game State
	void Render();

	// Temporarily being implemented in Game
	
	// Grid & textures
	Texture2D grassTexture{};

	void RenderGrid();
	bool InitTextures(Texture2D& theTexture, const char* texturePath);
	void UninitTextures(Texture2D& theTexture);

	// camera
	Camera2D camera{};

	void InitCamera(Camera2D& cam);
	void CamInputs(Camera2D& cam, float dt);
};