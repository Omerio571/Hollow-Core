#include "TileMap.hpp"

TileMap::TileMap(int width, int height)
	:width(width),
	height(height),
	tiles(width * height)
{}

bool TileMap::IsInside(int x, int y) const
{
	return x >= 0 && x < width && y >= 0 && y < height;
}

Tile* TileMap::GetTile(int x, int y)
{
	if(!IsInside(x,y))
		return nullptr;

	return &tiles[y * width + x];
}

int TileMap::GetWidth() const
{
	return 0;
}

int TileMap::GetHeight() const
{
	return 0;
}
