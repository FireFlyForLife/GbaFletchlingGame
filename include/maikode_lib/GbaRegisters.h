#pragma once

#include "ForceInline.h"
#include <cstdint>
#include <ratio>
#include "tonc.h"
#include <cassert>


namespace Sizes
{ 
	
}

/*
 * This header provides wrappers around the GBA registers with helper functions
 */
namespace mykd
{
	template<typename T, std::uintptr_t Adress, u32 Size>
	class GBARegister
	{
	public:
		static FORCE_INLINE T* GetPtr() { return reinterpret_cast<T*>(Adress); }

		T& operator*();
		const T& operator*() const;
		T& operator[](u32 index);
		const T& operator[](u32 index) const;
	};



	//Sprite memory
	class OAM_MemoryRegister :			public GBARegister<u16, 0x7000000, (1'000'000 / sizeof(u16))>
	{
		
	};
	extern OAM_MemoryRegister OAM_Memory;


	//Sprite palette (256/16 colors)
	class OBJ_PaletteMemoryRegister :	public GBARegister<u16, 0x5000200, 0>
	{
		
	};
	extern OBJ_PaletteMemoryRegister OBJ_PaletteMemory;


	//Sprite data(bitmapped)
	class OAM_Data_Register :			public GBARegister<u16, 0x6010000, 0>
	{
		
	};
	extern OAM_Data_Register OAM_Data;


	//FrontBuffer
	class FrontBufferRegister :		public GBARegister<u16, 0x6000000, SCREEN_WIDTH * SCREEN_HEIGHT / sizeof(u16)>
	{
		
	};
	extern FrontBufferRegister FrontBuffer_;
}

//=============================================================================
// IMPLEMENTATION
//=============================================================================
namespace mykd
{
	template <typename T, std::uintptr_t Adress, u32 Size>
	T& GBARegister<T, Adress, Size>::operator*()
	{
		return *GetPtr();
	}

	template <typename T, std::uintptr_t Adress, u32 Size>
	const T& GBARegister<T, Adress, Size>::operator*() const
	{
		return *GetPtr();
	}

	template <typename T, std::uintptr_t Adress, u32 Size>
	T& GBARegister<T, Adress, Size>::operator[](u32 index)
	{
		//assert(index < Size);
		return GetPtr()[index];
	}

	template <typename T, std::uintptr_t Adress, u32 Size>
	const T& GBARegister<T, Adress, Size>::operator[](u32 index) const
	{
		//assert(index < Size);
		return GetPtr()[index];
	}
}