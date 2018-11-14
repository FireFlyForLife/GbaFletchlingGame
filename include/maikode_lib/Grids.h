#pragma once
#include <cstdint>
#include <array>
#include <vector>
#include <cassert>

namespace mykd {
	template<typename T, uint32_t W, uint32_t H>
	class Grid2DFixedSize
	{
		std::array<std::array<T, W>, H> cells;

	public:
		Grid2DFixedSize() = default;

		constexpr uint32_t Width() const;
		constexpr uint32_t Height() const;

		T& GetAt(uint32_t x, uint32_t y);
		const T& GetAt(uint32_t x, uint32_t y) const;
		void SetAt(uint32_t x, uint32_t y, T&& value);
	};

	template<typename T>
	class Grid2D
	{
		std::vector<std::vector<T>> cells;

	public:
		Grid2D() = default;

		uint32_t Width() const;
		uint32_t Height() const;

		T& GetAt(uint32_t x, uint32_t y);
		const T& GetAt(uint32_t x, uint32_t y) const;
		void SetAt(uint32_t x, uint32_t y, T&& value);
	};
}

//========================================================================
// IMPLEMENTATION:
//========================================================================
namespace mykd
{
	///class Grid2DFixedSize:
	///=======================

	template <typename T, uint32_t W, uint32_t H>
	constexpr uint32_t Grid2DFixedSize<T, W, H>::Width() const
	{
		return W;
	}

	template <typename T, uint32_t W, uint32_t H>
	constexpr uint32_t Grid2DFixedSize<T, W, H>::Height() const
	{
		return H;
	}

	template <typename T, uint32_t W, uint32_t H>
	T& Grid2DFixedSize<T, W, H>::GetAt(uint32_t x, uint32_t y)
	{
		assert(x < Width() && y < Height());

		return cells[y][x];
	}

	template <typename T, uint32_t W, uint32_t H>
	const T& Grid2DFixedSize<T, W, H>::GetAt(uint32_t x, uint32_t y) const
	{
		assert(x < Width() && y < Height());

		return cells[y][x];
	}

	template <typename T, uint32_t W, uint32_t H>
	void Grid2DFixedSize<T, W, H>::SetAt(uint32_t x, uint32_t y, T&& value)
	{
		assert(x < Width() && y < Height());

		cells[y][x] = value;
	}


	///class Grid2D:
	///=======================

	template <typename T>
	uint32_t Grid2D<T>::Width() const
	{
		return static_cast<uint32_t>(cells[0].size());
	}

	template <typename T>
	uint32_t Grid2D<T>::Height() const
	{
		return static_cast<uint32_t>(cells.size());
	}

	template <typename T>
	T& Grid2D<T>::GetAt(uint32_t x, uint32_t y)
	{
		assert(x < Width() && y < Height());

		return cells[y][x];
	}

	template <typename T>
	const T& Grid2D<T>::GetAt(uint32_t x, uint32_t y) const
	{
		assert(x < Width() && y < Height());

		return cells[y][x];
	}

	template <typename T>
	void Grid2D<T>::SetAt(uint32_t x, uint32_t y, T&& value)
	{
		assert(x < Width() && y < Height());

		cells[y][x] = value;
	}
}
