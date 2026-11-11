#include "TileMap.hpp"

TileMap::TileMap(int width, int height)
	:width(width),
	height(height),
	tiles(width * height)
{}

bool TileMap::IsInside(const int x, const int y) const
{
	return x >= 0 && x < width && y >= 0 && y < height;
}

void TileMap::ChangeOccupancy(const int x, const int y, bool changeOccupancyTo)
{
	Tile* tile = GetTile(x, y);
	if (tile)
	{
		tile->occupied = changeOccupancyTo;
	}
}

bool TileMap::GetOccupancy(const int x, const int y)
{
	const Tile* tile = GetTile(x, y);
	if (tile)
	{
		return tile->occupied;
	}
	return true;
}

Tile* TileMap::GetTile(const int x, const int y)
{
	if(!IsInside(x,y))
		return nullptr;

	return &tiles[y * width + x];
}

int TileMap::GetWidth() const
{
	return width;
}

int TileMap::GetHeight() const
{
	return height;
}
