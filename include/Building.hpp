#pragma once 

#include <raylib.h>

enum class BuildingType
{
	Rock
};

struct Building
{
	int x;
	int y;

	BuildingType type;

	bool breakable{};
	
	Color tint{};
};