#include "Isometric.hpp"
#include "Config.hpp"

Vector2 GridToIsometric(float x, float y)
{

	const float halfWidth = Config::tileWidth / 2.f;
	const float halfHeight = Config::tileHeight / 2.f;

	const float isoX = (x - y) * halfWidth;
	const float isoY = (x + y) * halfHeight;

	return{ isoX,isoY };
}
