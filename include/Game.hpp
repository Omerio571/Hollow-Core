#pragma once

// C++ headers
#include <string>

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
	void HandleInput();

	// Display the current Game State
	void Render();

	// Advance the world's state
	void Update(float dt);
};