#pragma once

#include <raylib.h>

enum class TerrainType
{
	Grass,
	Dirt,
	Stone
};

struct Tile
{
	TerrainType terrain = TerrainType::Dirt;

	Color tileColor = { GRV(), 255, GRV(), 255}; // Get Random Values for Color

	bool occupied = false;

	// Remove when implementing rendering
	unsigned char GRV()
	{
		return static_cast<unsigned char>(GetRandomValue(240, 255));
	}
};