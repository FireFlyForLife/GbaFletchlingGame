#pragma once
#include "gba_lib/gba.h"

inline void clearScreen(u16 clearColor)
{
	for (u16 i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i)
		FrontBuffer[i] = clearColor;
}

inline u16 coordToIndex(u16 x, u16 y)
{
	return y * SCREEN_WIDTH + x;
}