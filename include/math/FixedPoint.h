#pragma once
#include <cstdint>
#include "tonc.h"

// #define 	FIX_SHIFT   8
// #define 	FIX_SCALE   ( 1<<FIX_SHIFT	)
// #define 	FIX_MASK   ( FIX_SCALE-1	)
// #define 	FIX_SCALEF   ( (float)FIX_SCALE	)
// #define 	FIX_SCALEF_INV   ( 1.0/FIX_SCALEF	)
// #define 	FIX_ONE   FIX_SCALE
// #define 	FX_RECIPROCAL(a, fp)   ( ((1<<(fp))+(a)-1)/(a) )
// #define 	FX_RECIMUL(x, a, fp)   ( ((x)*((1<<(fp))+(a)-1)/(a))>>(fp) )
//
// #define FIXED int32_t

template<uint32_t IntegerPart, uint32_t FractionalPart>
class TFixedPoint
{
	int32_t m_value;

	static_assert((IntegerPart + FractionalPart) % 8 == 0, "IntegerPart and Fractionalpart together have to be divisible by 8 bits");
	static_assert(FractionalPart == 8 && 
		sizeof(m_value)*8 - IntegerPart == 8, "Currently only 24.8FixedPoint is supported, as I use tonic_math.h");


	//Our constructors need to have no implicit conversions to be accessed. This is because int, unsigned and float can be implicitly converted.
	//So the compiler thinks they are ambigues. The same goes for an 'int' type to int32_t even though they are the same type.
	//So we need to check that the default int is actually the int we want.
	static_assert(sizeof(int) == sizeof(int32_t), "ERROR: int32_t is not an alias of int!! this causes issues with constructor overloads!");
	static_assert(sizeof(unsigned int) == sizeof(uint32_t), "ERROR: uint32_t is not an alias of unsigned int!! this causes issues with constructor overloads!");
public:
	constexpr TFixedPoint() : m_value(0)
	{}

	constexpr explicit TFixedPoint(int integer) : m_value(int2fx(integer))
	{}

	constexpr explicit TFixedPoint(unsigned int integer) : m_value(int2fx(integer))
	{}

	constexpr explicit TFixedPoint(float f) : m_value(float2fx(f))
	{}

	~TFixedPoint() = default;
	constexpr TFixedPoint(const TFixedPoint& other) = default;
	constexpr TFixedPoint(TFixedPoint&& other) noexcept = default;
	constexpr TFixedPoint& operator=(const TFixedPoint& other) = default;
	constexpr TFixedPoint& operator=(TFixedPoint&& other) noexcept = default;

	//Return a value which represents '1.0f' in fixed point
	constexpr static TFixedPoint One();

	//Return the scale of the fixed point, this will represent '1.0f'
	constexpr static uint32_t Scale();

	//Return the scale of the fixed point in floating point, this will represent '1.0f'
	constexpr static float ScaleF();

	//Return a mask of this fixed point?
	constexpr static uint32_t Mask();

	constexpr TFixedPoint operator*(TFixedPoint other) const;
	constexpr TFixedPoint operator/(TFixedPoint other) const;
	constexpr TFixedPoint operator+(TFixedPoint other) const;
	constexpr TFixedPoint operator-(TFixedPoint other) const;
	constexpr TFixedPoint& operator*=(TFixedPoint other);
	constexpr TFixedPoint& operator/=(TFixedPoint other);
	constexpr TFixedPoint& operator+=(TFixedPoint other);
	constexpr TFixedPoint& operator-=(TFixedPoint other);
	constexpr TFixedPoint operator-() const;

	constexpr bool operator<(TFixedPoint other) const;
	constexpr bool operator>(TFixedPoint other) const;
	constexpr bool operator==(TFixedPoint other) const;
	constexpr bool operator!=(TFixedPoint other) const;
	constexpr bool operator<=(TFixedPoint other) const;
	constexpr bool operator>=(TFixedPoint other) const;

	// Computational methods:
	
	//Returns the fractional part of the integer. the result will thus always be unsigned.
	uint32_t GetFraction() const;

	// Conversion functions:

	//Converts this fixed point integer to a normal integer
	constexpr int32_t ToInt() const;

	//Converts this fixed point integer to a unsigned integer
	constexpr uint32_t ToUint() const;

	//Converts this fixed point integer to a floating point
	constexpr float ToFloat() const;
};



//============================================
// Fixed Point aliases
//============================================

using FixedPointInt = TFixedPoint<24, 8>;
using FixedPoint = FixedPointInt;



//============================================
// Fixed Point Implementation
//============================================

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr TFixedPoint<IntegerPart, FractionalPart> TFixedPoint<IntegerPart, FractionalPart>
	::One()
{
	return TFixedPoint{1 << FractionalPart}; 
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr uint32_t TFixedPoint<IntegerPart, FractionalPart>
	::Scale()
{
	return 1 << FractionalPart;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr float TFixedPoint<IntegerPart, FractionalPart>
	::ScaleF()
{
	return static_cast<float>(Scale());
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr uint32_t TFixedPoint<IntegerPart, FractionalPart>
	::Mask()
{
	return Scale() - 1;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr TFixedPoint<IntegerPart, FractionalPart> TFixedPoint<IntegerPart, FractionalPart>
	::operator*(TFixedPoint other) const
{
	return TFixedPoint{ fxmul(m_value, other.m_value) };
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr TFixedPoint<IntegerPart, FractionalPart> TFixedPoint<IntegerPart, FractionalPart>
	::operator/(TFixedPoint other) const
{
	return TFixedPoint{ fxdiv(m_value, other.m_value) };
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr TFixedPoint<IntegerPart, FractionalPart> TFixedPoint<IntegerPart, FractionalPart>
	::operator+(TFixedPoint other) const
{
	return TFixedPoint{ fxadd(m_value, other.m_value) };
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr TFixedPoint<IntegerPart, FractionalPart> TFixedPoint<IntegerPart, FractionalPart>
	::operator-(TFixedPoint other) const
{
	return TFixedPoint{ fxsub(m_value, other.m_value) };
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr TFixedPoint<IntegerPart, FractionalPart>& TFixedPoint<IntegerPart, FractionalPart>
	::operator*=(TFixedPoint other)
{
	m_value = fxmul(m_value, other.m_value);

	return *this;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr TFixedPoint<IntegerPart, FractionalPart>& TFixedPoint<IntegerPart, FractionalPart>
	::operator/=(TFixedPoint other)
{
	m_value = fxdiv(m_value, other.m_value);

	return *this;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr TFixedPoint<IntegerPart, FractionalPart>& TFixedPoint<IntegerPart, FractionalPart>
	::operator+=(TFixedPoint other)
{
	m_value = fxadd(m_value, other.m_value);

	return *this;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr TFixedPoint<IntegerPart, FractionalPart>& TFixedPoint<IntegerPart, FractionalPart>
	::operator-=(TFixedPoint other)
{
	m_value = fxsub(m_value, other.m_value);

	return *this;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr TFixedPoint<IntegerPart, FractionalPart> TFixedPoint<IntegerPart, FractionalPart>::operator-() const
{
	TFixedPoint copy{ *this };
	copy.m_value = -copy.m_value;
	return copy;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr bool TFixedPoint<IntegerPart, FractionalPart>
	::operator<(TFixedPoint other) const
{
	//First compare the integer parts
	int fullNum = ToInt();
	int fullNumOther = other.ToInt();
	if (fullNum != fullNumOther)
		return fullNum < fullNumOther;

	//integer parts are the same, compare the number after the decimal
	int fractNum = GetFraction();
	int fractNumOther = other.GetFraction();

	return fractNum < fractNumOther;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr bool TFixedPoint<IntegerPart, FractionalPart>
	::operator>(TFixedPoint other) const
{
	//First compare the integer parts
	int fullNum = ToInt();
	int fullNumOther = other.ToInt();
	if (fullNum != fullNumOther)
		return fullNum > fullNumOther;

	//integer parts are the same, compare the number after the decimal
	int fractNum = GetFraction();
	int fractNumOther = other.GetFraction();

	return fractNum > fractNumOther;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr bool TFixedPoint<IntegerPart, FractionalPart>
	::operator==(TFixedPoint other) const
{
	return m_value == other.m_value;
}

template<uint32_t IntegerPart, uint32_t FractionalPart>
constexpr bool TFixedPoint<IntegerPart, FractionalPart>
	::operator!=(TFixedPoint other) const
{
	return m_value != other.m_value;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr bool TFixedPoint<IntegerPart, FractionalPart>
	::operator<=(TFixedPoint other) const
{
	if (m_value == other.m_value)
		return true;

	return m_value < other.m_value;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr bool TFixedPoint<IntegerPart, FractionalPart>
	::operator>=(TFixedPoint other) const
{
	if (m_value == other.m_value)
		return true;

	return m_value > other.m_value;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
uint32_t TFixedPoint<IntegerPart, FractionalPart>
	::GetFraction() const
{
	return m_value & Mask();
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr int32_t TFixedPoint<IntegerPart, FractionalPart>
	::ToInt() const
{
	return fx2int(m_value);
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr uint32_t TFixedPoint<IntegerPart, FractionalPart>
	::ToUint() const
{
	return fx2uint(m_value);
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr float TFixedPoint<IntegerPart, FractionalPart>
	::ToFloat() const
{
	return fx2float(m_value);
}
