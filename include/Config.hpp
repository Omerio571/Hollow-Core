#pragma once

namespace Config
{
	// The games name
	inline constexpr char gameName[] = "Hollow Core";

	// Tile location
	inline constexpr char grassTilePath[] = "assets/tiles/GrassBlock.png";


	// Window Configurations
	inline constexpr int windowWidth = 800;
	inline constexpr int windowHeight = 600;

	inline constexpr int targetFPS = 60;

	// World Configurations
	inline constexpr int gridWidth = 12;
	inline constexpr int gridHeight = 12;

	// Tile ground footprint dimensions, in pixels
	inline constexpr float tileWidth = 32.0f;
	inline constexpr float tileHeight = 16.0f;

	// Camera Config
	inline constexpr float camSpeed = 300.f;
	inline constexpr float zoomIntensity = 1.f;
	inline constexpr float minZoom = 1.f;
	inline constexpr float maxZoom = 3.f;
}