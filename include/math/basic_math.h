#pragma once

namespace BMath
{
	template<typename T>
	constexpr T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template<typename T>
	constexpr T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	template<typename T>
	constexpr T Clamp(T val, T min, T max)
	{
		return Max(Min(val, max), min);
	}

}