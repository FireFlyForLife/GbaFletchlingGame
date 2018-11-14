#pragma once
#include <array>
#include <vector>

namespace mykd
{
	template<typename T>
	struct Point
	{
		static_assert(std::is_arithmetic_v<T>, "Point needs to be number!");

		T x, y;
	};

	inline std::vector<Point<u16>> RectangleCoords(u16 w, u16 h, u16 x = 0, u16 y = 0)
	{
		std::vector<Point<u16>> coords;
		coords.reserve(w*h);

		for (u16 ypos = y; ypos < y + h; ++ypos) {
			for (u16 xpos = x; xpos < x + w; ++xpos) {
				coords.push_back(Point<u16>{xpos, ypos});
			}
		}

		return coords;
	}
}
