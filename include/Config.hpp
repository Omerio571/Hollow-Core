#pragma once

#include <raylib.h>

namespace Config
{
	// The games name
	inline constexpr char gameName[] = "Hollow Core";

	// Asset location
	inline constexpr char grassTilePath[] = "assets/tiles/GrassBlock.png";
	inline constexpr char tileHoverIndicator[] = "assets/helperUI/tileHoverIndicator.png";
	inline constexpr char tileBuildIndicator[] = "assets/helperUI/tileBuildIndicator.png";

	// Window Configurations
	inline constexpr int windowWidth = 800;
	inline constexpr int windowHeight = 600;

	inline constexpr int targetFPS = 60;

	// World Configurations
	inline constexpr int gridWidth = 8;
	inline constexpr int gridHeight = 6;

	// Tile ground footprint dimensions, in pixels
	inline constexpr float tileWidth = 32.0f;
	inline constexpr float tileHeight = 16.0f;

	inline constexpr float halfTileWidth = tileWidth / 2.f;
	inline constexpr float halfTileHeight = tileHeight / 2.f;

	// Camera Config
	inline constexpr float camSpeed = 500.f;
	inline constexpr float zoomStep = 1.f;
	inline constexpr float minZoom = 1.f;
	inline constexpr float maxZoom = 8.f;

	inline constexpr float initRotation = 0.f;
	inline constexpr float initZoom = 2.f;

	// UI colours

	inline constexpr Color textColor = BLUE;
	inline constexpr Color validHoverColor = { 180,255,200, 200 };
	inline constexpr Color invalHoverColor = { 255,180,200, 200 };
}