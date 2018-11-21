#pragma once
#include "tonc.h"
#include "maikode_lib/GbaRegisters.h"

inline void clearScreen(u16 clearColor)
{
	m3_fill(clearColor);
}

inline u16 coordToIndex(u16 x, u16 y)
{
	return y * SCREEN_WIDTH + x;
}
