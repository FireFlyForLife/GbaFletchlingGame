#pragma once
#include "tonc.h"
#include "Game.h"

#include "Intellisense.h"
#include "maikode_lib/Grids.h"
#include "RaycastRenderer.h"


class TestGame
{
public:
	using Super = Game<TestGame>;

	TestGame(Super& super);

	void Init();
	void Update();
	void Render();
	void Shutdown();

private:
	s16 x = SCREEN_WIDTH / 2;
	s16 y = SCREEN_HEIGHT /2;

	mykd::Grid2DFixedSize<RaycastRenderer::Tiles, 24, 24> grid;

	RaycastRenderer renderer;
private:
	Super& super;
};
