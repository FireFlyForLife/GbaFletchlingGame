#pragma once

#if defined(__clang__)
//TODO: Test
#define FORCE_INLINE __attribute__((always_inline))
#elif defined(__GNUC__) || defined(__GNUG__)
//TODO: Test
#define FORCE_INLINE __attribute__((always_inline))
#elif defined(_MSC_VER)
#define FORCE_INLINE __forceinline
#else
#pragma warning("Unknown compiler! FORCE_INLINE will not correctly!")
#define FORCE_INLINE inline
#endif
