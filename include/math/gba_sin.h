#pragma once
//This file contains trigonometry functions using a LUT and fixed point math

#include <array>

#include "gcem.hpp"
#include "FixedPoint.h"
#include "tonc_math.h"

namespace mykd {
	template<typename T, size_t Size>
	constexpr std::array<T, Size> GenerateSinLut()
	{
		std::array<T, Size> lut{};

		const double conv = 2 * GCEM_PI / 360;
		for (int ii = 0; ii < 360; ii++) {
			lut[ii] = (FIXED)(gcem::sin<double>(conv*ii)*FIX_SCALEF);
		}

		return lut;
	}

	constexpr auto sin_lut = GenerateSinLut<FIXED, 360>();


	// FIXED sin_lut[360], cos_lut[360];
	//
	// // A really simple (and slow and wasteful) LUT builder
	// constexpr void sincos_init()
	// {
	// 	const double conv = 2 * GCEM_PI / 360;
	// 	for (int ii = 0; ii < 360; ii++) {
	// 		sin_lut[ii] = (FIXED)(sin(conv*ii)*FIX_SCALEF);
	// 		cos_lut[ii] = (FIXED)(cos(conv*ii)*FIX_SCALEF);
	// 	}
	// }

}