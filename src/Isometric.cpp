#include "Isometric.hpp"
#include "Config.hpp"

Vector2 GridToIsometric(float x, float y)
{
	float isoX = (x - y) * Config::halfTileWidth;
	float isoY = (x + y) * Config::halfTileHeight;

	return{ isoX,isoY };
}

Vector2 IsometricToGrid(Vector2 screenPos, const Camera2D& cam)
{
	Vector2 worldPos2D = GetScreenToWorld2D(screenPos, cam);

	float A = worldPos2D.x / Config::halfTileWidth;
	float B = worldPos2D.y / Config::halfTileHeight;

	Vector2 gridPos =
	{
		(A + B) / 2.f,
		(B - A) / 2.f
	};

	return gridPos;
}


