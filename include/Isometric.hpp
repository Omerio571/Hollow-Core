#pragma once

#include <raylib.h>

Vector2 GridToIsometric(float x, float y);
Vector2 IsometricToGrid(Vector2 screenPos, const Camera2D& cam);