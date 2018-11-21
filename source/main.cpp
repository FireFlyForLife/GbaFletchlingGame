#include "Intellisense.h"
#include <cstring>
#include "math/basic_math.h"
#include "tonc.h"
#include "maikode_lib/GbaRegisters.h"
#include <ctime>
#include "Game.h"
#include "TestGame.h"
#include "small_utils.h"

using namespace BMath;

#define BREAK_NOCASH __asm("mov r11, r11")

// //Screen coord to buffer index
// u16 coordToIndex(u16 x, u16 y);
// void clearScreen(u16 clearColor);


// time_t startTime = 0;
// time_t lastFrameTime = 0;
// time_t currentTime = 0;
// float time_elapsed()
// {
// 	return difftime(currentTime, startTime);
// }
// float delta_time()
// {
// 	return difftime( currentTime, lastFrameTime);
// }
// void init_time()
// {
// 	startTime = time(0);
// 	lastFrameTime = startTime;
// 	currentTime = startTime;
// }
// void tick_time()
// {
// 	currentTime = time(0);
// }

int main()
{
	//nocash_puts("Test!!");

	//BREAK_NOCASH;

	//REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

	//clearScreen(RGB15(50, 0, 0));
	// nocash_puts("Hello Test 123 test!!!");
	//
	Game<TestGame> testGame;
	//
	RunGameLoop(testGame);

	return 0;
}

//int oldmain()
//{
//	// //set GBA rendering context to MODE 3 Bitmap Rendering
//	// *(unsigned int*)0x04000000 = 0x0403;
//	//
//	// int t = 0;
//	// while(1){
//	// 	int x,y;
//	// 	for(x = 0; x < 240; ++x){
//	// 		for( y = 0; y < 160; ++y){
//	// 			reinterpret_cast<unsigned short*>(0x06000000)[x+y*240] = ((((x&y)+t) & 0x1F) << 10)|
//	// 			((((x&y)+t*3)&0x1F)<<5) | ((((x&y)+t * 5)&0x1F)<<0);
//	// 		}
//	// 	}
//	// 	t = time(0);
//	// }
//
//	SetMode(MODE_3 | BG2_ENABLE);
//	
//	clearScreen(RGB(46, 141, 239));
//
//	//init_time();
//
//	s16 x = SCREEN_WIDTH / 2;
//	s16 y = SCREEN_HEIGHT / 2;
//
//	//time_t lastMoveTime = time_elapsed();
//	const float moveDelay = 0.5f;
//
//	while (1) {
//		//tick_time();
//		
//		//if (difftime(lastMoveTime, currentTime) > moveDelay) {
//			s8 horizontal = 0;
//			s8 vertical = 0;
//			if (keyDown(KEY_LEFT)) horizontal -= 1;
//			if (keyDown(KEY_RIGHT)) horizontal += 1;
//			if (keyDown(KEY_UP)) vertical += 1;
//			if (keyDown(KEY_DOWN)) vertical -= 1;
//
//			x = Clamp<s16>(x + horizontal, 0, SCREEN_WIDTH - 1);
//			y = Clamp<s16>(y + vertical, 0, SCREEN_HEIGHT - 1);
//
//			FrontBuffer[coordToIndex(x, y)] = RGB(210, 0, 0);
//
//			//lastMoveTime = currentTime;
//		//}
//	}
//	
//	return 0;
//}

// void clearScreen(u16 clearColor)
// {
// 	for (u16 i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i)
// 		mykd::FrontBuffer_[i] = clearColor;
// }

// u16 coordToIndex(u16 x, u16 y)
// {
// 	return y * SCREEN_WIDTH + x;
// }
