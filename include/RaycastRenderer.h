#pragma once
#include <vector>
#include "maikode_lib/GbaSprite.h"
#include "maikode_lib/Grids.h"


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
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame
};
