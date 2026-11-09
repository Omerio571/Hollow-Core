#pragma once

#include "Tile.hpp"

// C++ libraries
#include <vector>

class TileMap
{
public:
	TileMap(int width, int height);

	bool IsInside(int x, int y) const;

	Tile* GetTile(int x, int y);

	int GetWidth() const;
	int GetHeight() const;

private:
	const int width{};
	const int height{};

	std::vector<Tile> tiles;

};