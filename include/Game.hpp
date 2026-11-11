#pragma once

// Outer Headers
#include <raylib.h>

// my Headers
#include "TileMap.hpp"
#include "Building.hpp"
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

	// Temporary 
	
	// camera

	Camera2D GetRenderCamera() const;

private:
	// Handles the players actions
	void HandleInput(float dt);

	// Advance the world's state
	void Update(float dt);

	// Display the current Game State
	void Render();

	// Temporarily being implemented in Game
	
	// Initialize settings
	///// Empty for now

	// Grid & textures
	Texture2D grassTexture{};
	Texture2D dirtTexture{};

	void RenderGrid();
	bool InitTextures(Texture2D& theTexture, const char* texturePath);
	void UninitTextures(Texture2D& theTexture);

	// camera
	Camera2D camera{};

	void InitCamera(Camera2D& cam);
	void CamInputs(Camera2D& cam, float dt);
	Camera2D GetCam() const;

	// Testing
	void DisplayCurrentTilePos();

	// Input & Rendering
	Texture2D hoverModeTexture{};
	Texture2D buildModeTexture{};

	Vector2 hoveredTile{};

	enum class MouseMode
	{
		Normal,
		BuildingPlacement
	};

	MouseMode mouseMode = MouseMode::Normal;
	Color tileValidityColor{};

	void HandleMouseMode();

	void UpdateWorldMousePos();
	void RenderHoveredTile();

	void HandleTerrainEditing();
	void ToggleTileTerrain(Tile* theTile);

	TileMap tileMap{ Config::gridWidth, Config::gridHeight };

	// Building Blocks
	std::vector<Building> buildings;

	int GetBuildingVectorIndex(int x, int y);
	bool IsItBreakableBuilding( int buildingIndex );

	void UpdateTileValidityColor();
	Vector2 CalcBuildingOffset(Vector2 buildingPosition);

	void RenderPreviewBuild();

	bool CanModifyTile(int x, int y);
	bool CanRemoveBuilding( int buildingIndex );
	bool TryPlaceBuilding(int x, int y, BuildingType type);
	bool TryRemoveBuilding(int x, int y);

	void HandlePlaceBuildingWithMouse();
	void HandleRemoveBuildingWithMouse();

	void RenderBuildings();

	// Introduce Multiple Buildings
	BuildingType selectedBuilding = BuildingType::Rock;

	Texture2D rockTexture{};
	Texture2D bushTexture{};

	Texture* selectedTexture = &rockTexture;

	void SelectBuilding(BuildingType type);
	void HandleSelectingABuilding();
};