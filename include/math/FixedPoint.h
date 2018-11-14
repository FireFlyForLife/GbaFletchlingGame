#pragma once
#include <cstdint>

#define 	FIX_SHIFT   8
#define 	FIX_SCALE   ( 1<<FIX_SHIFT	)
#define 	FIX_MASK   ( FIX_SCALE-1	)
#define 	FIX_SCALEF   ( (float)FIX_SCALE	)
#define 	FIX_SCALEF_INV   ( 1.0/FIX_SCALEF	)
#define 	FIX_ONE   FIX_SCALE
#define 	FX_RECIPROCAL(a, fp)   ( ((1<<(fp))+(a)-1)/(a) )
#define 	FX_RECIMUL(x, a, fp)   ( ((x)*((1<<(fp))+(a)-1)/(a))>>(fp) )

#define FIXED int32_t

template<uint32_t IntegerPart, uint32_t FractionalPart>
class FixedPoint
{
	uint32_t m_value;

public:
	FixedPoint(uint32_t fixedPointInteger) : m_value(fixedPointInteger)
	{}

	//Return a value which represents '1.0f' in fixed point
	constexpr static FixedPoint One();

	//Return the scale of the fixed point, this will represent '1.0f'
	constexpr static uint32_t Scale();

	//Return the scale of the fixed point in floating point, this will represent '1.0f'
	constexpr static float ScaleF();

	//Return a mask of this fixed point?
	constexpr static uint32_t Mask();

	operator uint32_t() const { return m_value; }
};



//============================================
// Fixed Point Implementation
//============================================

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr FixedPoint<IntegerPart, FractionalPart> FixedPoint<IntegerPart, FractionalPart>::One()
{
	return FixedPoint{1 << FractionalPart}; 
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr uint32_t FixedPoint<IntegerPart, FractionalPart>::Scale()
{
	return 1 << FractionalPart;
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr float FixedPoint<IntegerPart, FractionalPart>::ScaleF()
{
	return static_cast<float>(Scale());
}

template <uint32_t IntegerPart, uint32_t FractionalPart>
constexpr uint32_t FixedPoint<IntegerPart, FractionalPart>::Mask()
{
	return Scale() - 1;
}
