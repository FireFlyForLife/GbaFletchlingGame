#include "TestGame.h"
#include "math/basic_math.h"
#include "assets/coloredsquares.h"
#include "maikode_lib/GridUtils.h"
#include "RaycastRenderer.h"
#include "small_utils.h"

using namespace BMath;

template<uint16_t W, uint16_t H>
static void FillGrid(mykd::Grid2DFixedSize<RaycastRenderer::Tiles, H, W>& grid, const std::array<std::array<int, H>, W>& arr)
{
	for (int _y = 0; _y < H; ++_y)
	{
		for(int _x = 0; _x < W; ++_x)
		{
			RaycastRenderer::Tiles tileType = static_cast<RaycastRenderer::Tiles>(arr[_y][_x]);
			grid.SetAt(_x, _y, std::move(tileType));
		}
	}
}

TestGame::TestGame(Super& super) : grid(), super(super)
{
	std::array<std::array<int, 24>, 24> worldMap = { {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}};
	FillGrid<24, 24>(grid, worldMap);
}


void TestGame::Init()
{
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

	// clearScreen(RGB8(46, 41, 39));
}

void TestGame::Update()
{
	if (true || super.frameCount % 50 == 0) {
		s8 horizontal = 0;
		s8 vertical = 0;
		if (KEY_DOWN_NOW(KEY_LEFT)) horizontal -= 1;
		if (KEY_DOWN_NOW(KEY_RIGHT)) horizontal += 1;
		if (KEY_DOWN_NOW(KEY_UP)) vertical -= 1;
		if (KEY_DOWN_NOW(KEY_DOWN)) vertical += 1;

		x = Clamp<s16>(x + horizontal, 0, SCREEN_WIDTH - 1);
		y = Clamp<s16>(y + vertical, 0, SCREEN_HEIGHT - 1);
	}
}

void TestGame::Render()
{
	clearScreen(RGB15(10, 10, 0));

	// // Fill screen with grey color
	// m3_fill(RGB15(12, 12, 14));
	//
	// //Rectangles:
	// m3_rect(12, 8, 108, 72, CLR_RED);
	// m3_rect(108, 72, 132, 88, CLR_LIME);
	// m3_rect(132, 88, 228, 152, CLR_BLUE);
	//
	// // Rectangle frames
	// m3_frame(132, 8, 228, 72, CLR_CYAN);
	// m3_frame(109, 73, 131, 87, CLR_BLACK);
	// m3_frame(12, 88, 108, 152, CLR_YELLOW);
	//
	// // Lines in top right frame
	// for (ii = 0; ii <= 8; ii++) {
	// 	jj = 3 * ii + 7;
	// 	m3_line(132 + 11 * ii, 9, 226, 12 + 7 * ii, RGB15(jj, 0, jj));
	// 	m3_line(226 - 11 * ii, 70, 133, 69 - 7 * ii, RGB15(jj, 0, jj));
	// }
	//
	// // Lines in bottom left frame
	// for (ii = 0; ii <= 8; ii++) {
	// 	jj = 3 * ii + 7;
	// 	m3_line(15 + 11 * ii, 88, 104 - 11 * ii, 150, RGB15(0, jj, jj));
	// }

	
	 // for(auto[x, y] : mykd::RectangleCoords(16, 16))
	 // {
	 // 	mykd::FrontBuffer_[coordToIndex(x, y)] = coloredsquaresBitmap[y * 16 + x];
	 // }

	renderer.Render(grid, {});

	//Draw player pixel
	//mykd::FrontBuffer_[coordToIndex(x, y)] = RGB8(0, 10, 0);

	vid_vsync();
}

void TestGame::Shutdown()
{
}
