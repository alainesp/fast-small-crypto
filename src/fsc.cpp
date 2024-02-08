/////////////////////////////////////////////////////////////////////////////////
// This file is part of 'Fast-Small-Crypto'
// 
// Copyright (c) 2024 by Alain Espinosa.
/////////////////////////////////////////////////////////////////////////////////
#include <version>
#include <cassert>
#include <cstdint>

#ifdef __cpp_lib_byteswap
	#include <bit>
	#define byteswap64(v) std::byteswap(v)
	#define byteswap32(v) std::byteswap(v)
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
	#define byteswap64(v) __builtin_bswap64(v)
	#define byteswap32(v) __builtin_bswap32(v)
#elif defined(_MSC_VER)
	#define byteswap64(v) _byteswap_uint64(v)
	#define byteswap32(v) _byteswap_ulong(v)
#else
	static inline uint64_t byteswap64(uint64_t v) noexcept
	{
		v = ((v & 0x00000000FFFFFFFFull) << 32) | ((v & 0xFFFFFFFF00000000ull) >> 32);
		v = ((v & 0x0000FFFF0000FFFFull) << 16) | ((v & 0xFFFF0000FFFF0000ull) >> 16);
		v = ((v & 0x00FF00FF00FF00FFull) <<  8) | ((v & 0xFF00FF00FF00FF00ull) >>  8);
		return v;
	}
	static inline uint32_t byteswap32(uint32_t v) noexcept
	{
		return (((v >> 24) & 0xff) | ((v >> 8) & 0xff00) | ((v << 8) & 0xff0000) | ((v << 24) & 0xff000000));
	}
#endif
