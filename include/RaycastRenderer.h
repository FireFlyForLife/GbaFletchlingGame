#pragma once
#include <vector>
#include "maikode_lib/GbaSprite.h"
#include "maikode_lib/Grids.h"
#include "tonc.h"
#include "math/FixedPoint.h"


class RaycastRenderer
{
public:
	enum class Tiles
	{
		Empty = 0,
		Wall = 1,
		Something = 2,
	};

	RaycastRenderer() = default;

	void Render(const mykd::Grid2DFixedSize<Tiles, 24, 24>& grid, const std::vector<mykd::GbaSprite>& sprites);

private:
	FixedPoint posX{ 22 }, posY{ 12 };  //x and y start position
	FixedPoint dirX{ -1 }, dirY{ 0 }; //initial direction vector
	FixedPoint planeX{ 0 }, planeY{ 0.66f }; //the 2d raycaster version of camera plane

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame
};
