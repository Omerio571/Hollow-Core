#pragma once

#include "Tile.hpp"

// C++ libraries
#include <vector>

class TileMap
{
public:
	TileMap(int width, int height);

	bool IsInside(const int x, const int y) const;
	void ChangeOccupancy(const int x, const int y, bool changeOccupancyTo);
	bool GetOccupancy(const int x, const int y);

	Tile* GetTile(const int x, const int y);

	int GetWidth() const;
	int GetHeight() const;

private:
	const int width{};
	const int height{};

	std::vector<Tile> tiles;

};