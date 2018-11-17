#include "RaycastRenderer.h"
#include "maikode_lib/Grids.h"

#include "math/gba_sin.h"
#include "small_utils.h"

static void BitmapDrawVerticalLine(uint16_t x, uint16_t y1,  uint16_t y2, u16 color)
{
	if (y1 > y2)
		std::swap(y1, y2);
	for (uint16_t i = y1; i < y2 + 1; ++i)
		mykd::FrontBuffer_[coordToIndex(x, i)] = color;
}

void RaycastRenderer::Render(const mykd::Grid2DFixedSize<Tiles, 24, 24>& grid,
	const std::vector<mykd::GbaSprite>& sprites)
{
	const int w = SCREEN_WIDTH;
	const int h = SCREEN_HEIGHT;


	for (int x = 0; x < w; x++) {
		//calculate ray position and direction
		double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = int(posX);
		int mapY = int(posY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = std::abs(1 / rayDirX);
		double deltaDistY = std::abs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0) {
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (static_cast<unsigned>(grid.GetAt(mapX, mapY)) > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)drawEnd = h - 1;

		//choose wall color
		uint16_t color;
		switch (grid.GetAt(mapX, mapY)) {
		case Tiles::Wall :  color = CLR_RED;  break; //red
		case Tiles::Something:  color = CLR_GREEN;  break; //green
		default: color = CLR_YELLOW; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1) { color = color / 2; }

		//draw the pixels of the stripe as a vertical line
		BitmapDrawVerticalLine(x, drawStart, drawEnd, color);
	}
	//timing for input and FPS counter
	// oldTime = time;
	// time = getTicks();
	
	//constexpr double frameTime = 1.0 / 60.0; //frameTime is the time this frame has taken, in seconds
	// print(1.0 / frameTime); //FPS counter
	// redraw();
	// cls();

	//speed modifiers
	// double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
	// double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
	// //move forward if no wall in front of you
	// if (keyDown(KEY_UP)) {
	// 	if (grid.GetAt(int(posX + dirX * moveSpeed), int(posY)) == Tiles::Empty) posX += dirX * moveSpeed;
	// 	if (grid.GetAt(int(posX), int(posY + dirY * moveSpeed)) == Tiles::Empty) posY += dirY * moveSpeed;
	// }
	// //move backwards if no wall behind you
	// if (keyDown(KEY_DOWN)) {
	// 	if (grid.GetAt(int(posX - dirX * moveSpeed), int(posY)) == Tiles::Empty) posX -= dirX * moveSpeed;
	// 	if (grid.GetAt(int(posX), int(posY - dirY * moveSpeed)) == Tiles::Empty) posY -= dirY * moveSpeed;
	// }
	// //rotate to the right
	// if (keyDown(KEY_RIGHT)) {
	// 	//both camera direction and camera plane must be rotated
	// 	double oldDirX = dirX;
	// 	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	// 	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	// 	double oldPlaneX = planeX;
	// 	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	// 	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	// }
	// //rotate to the left
	// if (keyDown(KEY_LEFT)) {
	// 	//both camera direction and camera plane must be rotated
	// 	double oldDirX = dirX;
	// 	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	// 	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	// 	double oldPlaneX = planeX;
	// 	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	// 	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	// }
}
