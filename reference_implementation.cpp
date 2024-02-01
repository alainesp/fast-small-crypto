/////////////////////////////////////////////////////////////////////////////////
// This file is part of 'Fast-Small-Crypto'
// 
// Copyright (c) 2024 by Alain Espinosa.
/////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#ifndef _MSC_VER
#include <bit>
#define _rotl std::rotl
#endif

#define ROUND1(a,b,c,d,k,s) (a = _rotl(a + (d ^ (b & (c ^ d))) + k, s))
#define ROUND2(a,b,c,d,k,s) (a = _rotl(a + ((b & c) ^ (d & (b ^ c))) + k + 0x5A827999, s))
#define ROUND3(a,b,c,d,k,s) (a = _rotl(a + (b ^ c ^ d) + k + 0x6ED9EBA1, s))

static void md4_transform(uint32_t state[4], const uint32_t in[16])
{
	uint32_t a = state[0];
	uint32_t b = state[1];
	uint32_t c = state[2];
	uint32_t d = state[3];

	ROUND1(a, b, c, d, in[ 0], 3);
	ROUND1(d, a, b, c, in[ 1], 7);
	ROUND1(c, d, a, b, in[ 2], 11);
	ROUND1(b, c, d, a, in[ 3], 19);
	ROUND1(a, b, c, d, in[ 4], 3);
	ROUND1(d, a, b, c, in[ 5], 7);
	ROUND1(c, d, a, b, in[ 6], 11);
	ROUND1(b, c, d, a, in[ 7], 19);
	ROUND1(a, b, c, d, in[ 8], 3);
	ROUND1(d, a, b, c, in[ 9], 7);
	ROUND1(c, d, a, b, in[10], 11);
	ROUND1(b, c, d, a, in[11], 19);
	ROUND1(a, b, c, d, in[12], 3);
	ROUND1(d, a, b, c, in[13], 7);
	ROUND1(c, d, a, b, in[14], 11);
	ROUND1(b, c, d, a, in[15], 19);

	ROUND2(a, b, c, d, in[ 0], 3);
	ROUND2(d, a, b, c, in[ 4], 5);
	ROUND2(c, d, a, b, in[ 8], 9);
	ROUND2(b, c, d, a, in[12], 13);
	ROUND2(a, b, c, d, in[ 1], 3);
	ROUND2(d, a, b, c, in[ 5], 5);
	ROUND2(c, d, a, b, in[ 9], 9);
	ROUND2(b, c, d, a, in[13], 13);
	ROUND2(a, b, c, d, in[ 2], 3);
	ROUND2(d, a, b, c, in[ 6], 5);
	ROUND2(c, d, a, b, in[10], 9);
	ROUND2(b, c, d, a, in[14], 13);
	ROUND2(a, b, c, d, in[ 3], 3);
	ROUND2(d, a, b, c, in[ 7], 5);
	ROUND2(c, d, a, b, in[11], 9);
	ROUND2(b, c, d, a, in[15], 13);

	ROUND3(a, b, c, d, in[ 0], 3);
	ROUND3(d, a, b, c, in[ 8], 9);
	ROUND3(c, d, a, b, in[ 4], 11);
	ROUND3(b, c, d, a, in[12], 15);
	ROUND3(a, b, c, d, in[ 2], 3);
	ROUND3(d, a, b, c, in[10], 9);
	ROUND3(c, d, a, b, in[ 6], 11);
	ROUND3(b, c, d, a, in[14], 15);
	ROUND3(a, b, c, d, in[ 1], 3);
	ROUND3(d, a, b, c, in[ 9], 9);
	ROUND3(c, d, a, b, in[ 5], 11);
	ROUND3(b, c, d, a, in[13], 15);
	ROUND3(a, b, c, d, in[ 3], 3);
	ROUND3(d, a, b, c, in[11], 9);
	ROUND3(c, d, a, b, in[ 7], 11);
	ROUND3(b, c, d, a, in[15], 15);

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}