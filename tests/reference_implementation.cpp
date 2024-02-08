/////////////////////////////////////////////////////////////////////////////////
// This file is part of 'Fast-Small-Crypto'
// 
// Copyright (c) 2024 by Alain Espinosa.
/////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#ifndef _MSC_VER
#include <bit>

#ifndef _rotl
	#define _rotl   std::rotl
#endif

#ifndef _rotl64
	#define _rotl64 std::rotl
#endif

#endif

#define ROTATE32(x,shift)	_rotl(x,shift)
#define ROTATE64(x,shift)	_rotl64(x,shift)

// MD4
#define ROUND1(a,b,c,d,k,s) (a = ROTATE32(a + (d ^ (b & (c ^ d))) + k, s))
#define ROUND2(a,b,c,d,k,s) (a = ROTATE32(a + ((b & c) ^ (d & (b ^ c))) + k + 0x5A827999, s))
#define ROUND3(a,b,c,d,k,s) (a = ROTATE32(a + (b ^ c ^ d) + k + 0x6ED9EBA1, s))
static void md4_transform(uint32_t state[4], const uint32_t block[16])
{
	uint32_t a = state[0];
	uint32_t b = state[1];
	uint32_t c = state[2];
	uint32_t d = state[3];

	ROUND1(a, b, c, d, block[ 0],  3);
	ROUND1(d, a, b, c, block[ 1],  7);
	ROUND1(c, d, a, b, block[ 2], 11);
	ROUND1(b, c, d, a, block[ 3], 19);
	ROUND1(a, b, c, d, block[ 4],  3);
	ROUND1(d, a, b, c, block[ 5],  7);
	ROUND1(c, d, a, b, block[ 6], 11);
	ROUND1(b, c, d, a, block[ 7], 19);
	ROUND1(a, b, c, d, block[ 8],  3);
	ROUND1(d, a, b, c, block[ 9],  7);
	ROUND1(c, d, a, b, block[10], 11);
	ROUND1(b, c, d, a, block[11], 19);
	ROUND1(a, b, c, d, block[12],  3);
	ROUND1(d, a, b, c, block[13],  7);
	ROUND1(c, d, a, b, block[14], 11);
	ROUND1(b, c, d, a, block[15], 19);
	
	ROUND2(a, b, c, d, block[ 0],  3);
	ROUND2(d, a, b, c, block[ 4],  5);
	ROUND2(c, d, a, b, block[ 8],  9);
	ROUND2(b, c, d, a, block[12], 13);
	ROUND2(a, b, c, d, block[ 1],  3);
	ROUND2(d, a, b, c, block[ 5],  5);
	ROUND2(c, d, a, b, block[ 9],  9);
	ROUND2(b, c, d, a, block[13], 13);
	ROUND2(a, b, c, d, block[ 2],  3);
	ROUND2(d, a, b, c, block[ 6],  5);
	ROUND2(c, d, a, b, block[10],  9);
	ROUND2(b, c, d, a, block[14], 13);
	ROUND2(a, b, c, d, block[ 3],  3);
	ROUND2(d, a, b, c, block[ 7],  5);
	ROUND2(c, d, a, b, block[11],  9);
	ROUND2(b, c, d, a, block[15], 13);

	ROUND3(a, b, c, d, block[ 0],  3);
	ROUND3(d, a, b, c, block[ 8],  9);
	ROUND3(c, d, a, b, block[ 4], 11);
	ROUND3(b, c, d, a, block[12], 15);
	ROUND3(a, b, c, d, block[ 2],  3);
	ROUND3(d, a, b, c, block[10],  9);
	ROUND3(c, d, a, b, block[ 6], 11);
	ROUND3(b, c, d, a, block[14], 15);
	ROUND3(a, b, c, d, block[ 1],  3);
	ROUND3(d, a, b, c, block[ 9],  9);
	ROUND3(c, d, a, b, block[ 5], 11);
	ROUND3(b, c, d, a, block[13], 15);
	ROUND3(a, b, c, d, block[ 3],  3);
	ROUND3(d, a, b, c, block[11],  9);
	ROUND3(c, d, a, b, block[ 7], 11);
	ROUND3(b, c, d, a, block[15], 15);

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}

// MD5
static void md5_transform(uint32_t state[4], const uint32_t block[16])
{
	uint32_t a = state[0];
	uint32_t b = state[1];
	uint32_t c = state[2];
	uint32_t d = state[3];

	/* Round 1 */
	a += (d ^ (b & (c ^ d))) + block[0 ] + 0xd76aa478; a = _rotl(a,  7) + b;
	d += (c ^ (a & (b ^ c))) + block[1 ] + 0xe8c7b756; d = _rotl(d, 12) + a;
	c += (b ^ (d & (a ^ b))) + block[2 ] + 0x242070db; c = _rotl(c, 17) + d;
	b += (a ^ (c & (d ^ a))) + block[3 ] + 0xc1bdceee; b = _rotl(b, 22) + c;

	a += (d ^ (b & (c ^ d))) + block[4 ] + 0xf57c0faf; a = _rotl(a,  7) + b;
	d += (c ^ (a & (b ^ c))) + block[5 ] + 0x4787c62a; d = _rotl(d, 12) + a;
	c += (b ^ (d & (a ^ b))) + block[6 ] + 0xa8304613; c = _rotl(c, 17) + d;
	b += (a ^ (c & (d ^ a))) + block[7 ] + 0xfd469501; b = _rotl(b, 22) + c;

	a += (d ^ (b & (c ^ d))) + block[8 ] + 0x698098d8; a = _rotl(a,  7) + b;
	d += (c ^ (a & (b ^ c))) + block[9 ] + 0x8b44f7af; d = _rotl(d, 12) + a;
	c += (b ^ (d & (a ^ b))) + block[10] + 0xffff5bb1; c = _rotl(c, 17) + d;
	b += (a ^ (c & (d ^ a))) + block[11] + 0x895cd7be; b = _rotl(b, 22) + c;

	a += (d ^ (b & (c ^ d))) + block[12] + 0x6b901122; a = _rotl(a,  7) + b;
	d += (c ^ (a & (b ^ c))) + block[13] + 0xfd987193; d = _rotl(d, 12) + a;
	c += (b ^ (d & (a ^ b))) + block[14] + 0xa679438e; c = _rotl(c, 17) + d;
	b += (a ^ (c & (d ^ a))) + block[15] + 0x49b40821; b = _rotl(b, 22) + c;

	/* Round 2 */
	a += (c ^ (d & (b ^ c))) + block[1 ] + 0xf61e2562; a = _rotl(a,  5) + b;
	d += (b ^ (c & (a ^ b))) + block[6 ] + 0xc040b340; d = _rotl(d,  9) + a;
	c += (a ^ (b & (d ^ a))) + block[11] + 0x265e5a51; c = _rotl(c, 14) + d;
	b += (d ^ (a & (c ^ d))) + block[0 ] + 0xe9b6c7aa; b = _rotl(b, 20) + c;

	a += (c ^ (d & (b ^ c))) + block[5 ] + 0xd62f105d; a = _rotl(a,  5) + b;
	d += (b ^ (c & (a ^ b))) + block[10] + 0x02441453; d = _rotl(d,  9) + a;
	c += (a ^ (b & (d ^ a))) + block[15] + 0xd8a1e681; c = _rotl(c, 14) + d;
	b += (d ^ (a & (c ^ d))) + block[4 ] + 0xe7d3fbc8; b = _rotl(b, 20) + c;

	a += (c ^ (d & (b ^ c))) + block[9 ] + 0x21e1cde6; a = _rotl(a,  5) + b;
	d += (b ^ (c & (a ^ b))) + block[14] + 0xc33707d6; d = _rotl(d,  9) + a;
	c += (a ^ (b & (d ^ a))) + block[3 ] + 0xf4d50d87; c = _rotl(c, 14) + d;
	b += (d ^ (a & (c ^ d))) + block[8 ] + 0x455a14ed; b = _rotl(b, 20) + c;

	a += (c ^ (d & (b ^ c))) + block[13] + 0xa9e3e905; a = _rotl(a,  5) + b;
	d += (b ^ (c & (a ^ b))) + block[2 ] + 0xfcefa3f8; d = _rotl(d,  9) + a;
	c += (a ^ (b & (d ^ a))) + block[7 ] + 0x676f02d9; c = _rotl(c, 14) + d;
	b += (d ^ (a & (c ^ d))) + block[12] + 0x8d2a4c8a; b = _rotl(b, 20) + c;

	/* Round 3 */
	a += (b ^ c ^ d) + block[5 ] + 0xfffa3942; a = _rotl(a,  4) + b;
	d += (a ^ b ^ c) + block[8 ] + 0x8771f681; d = _rotl(d, 11) + a;
	c += (d ^ a ^ b) + block[11] + 0x6d9d6122; c = _rotl(c, 16) + d;
	b += (c ^ d ^ a) + block[14] + 0xfde5380c; b = _rotl(b, 23) + c;

	a += (b ^ c ^ d) + block[1 ] + 0xa4beea44; a = _rotl(a,  4) + b;
	d += (a ^ b ^ c) + block[4 ] + 0x4bdecfa9; d = _rotl(d, 11) + a;
	c += (d ^ a ^ b) + block[7 ] + 0xf6bb4b60; c = _rotl(c, 16) + d;
	b += (c ^ d ^ a) + block[10] + 0xbebfbc70; b = _rotl(b, 23) + c;

	a += (b ^ c ^ d) + block[13] + 0x289b7ec6; a = _rotl(a,  4) + b;
	d += (a ^ b ^ c) + block[0 ] + 0xeaa127fa; d = _rotl(d, 11) + a;
	c += (d ^ a ^ b) + block[3 ] + 0xd4ef3085; c = _rotl(c, 16) + d;
	b += (c ^ d ^ a) + block[6 ] + 0x04881d05; b = _rotl(b, 23) + c;

	a += (b ^ c ^ d) + block[9 ] + 0xd9d4d039; a = _rotl(a,  4) + b;
	d += (a ^ b ^ c) + block[12] + 0xe6db99e5; d = _rotl(d, 11) + a;
	c += (d ^ a ^ b) + block[15] + 0x1fa27cf8; c = _rotl(c, 16) + d;
	b += (c ^ d ^ a) + block[2 ] + 0xc4ac5665; b = _rotl(b, 23) + c;

	/* Round 4 */
	a += (c ^ (b | ~d)) + block[0 ] + 0xf4292244; a = _rotl(a,  6) + b;
	d += (b ^ (a | ~c)) + block[7 ] + 0x432aff97; d = _rotl(d, 10) + a;
	c += (a ^ (d | ~b)) + block[14] + 0xab9423a7; c = _rotl(c, 15) + d;
	b += (d ^ (c | ~a)) + block[5 ] + 0xfc93a039; b = _rotl(b, 21) + c;

	a += (c ^ (b | ~d)) + block[12] + 0x655b59c3; a = _rotl(a,  6) + b;
	d += (b ^ (a | ~c)) + block[3 ] + 0x8f0ccc92; d = _rotl(d, 10) + a;
	c += (a ^ (d | ~b)) + block[10] + 0xffeff47d; c = _rotl(c, 15) + d;
	b += (d ^ (c | ~a)) + block[1 ] + 0x85845dd1; b = _rotl(b, 21) + c;

	a += (c ^ (b | ~d)) + block[8 ] + 0x6fa87e4f; a = _rotl(a,  6) + b;
	d += (b ^ (a | ~c)) + block[15] + 0xfe2ce6e0; d = _rotl(d, 10) + a;
	c += (a ^ (d | ~b)) + block[6 ] + 0xa3014314; c = _rotl(c, 15) + d;
	b += (d ^ (c | ~a)) + block[13] + 0x4e0811a1; b = _rotl(b, 21) + c;

	a += (c ^ (b | ~d)) + block[4 ] + 0xf7537e82; a = _rotl(a,  6) + b;
	d += (b ^ (a | ~c)) + block[11] + 0xbd3af235; d = _rotl(d, 10) + a;
	c += (a ^ (d | ~b)) + block[2 ] + 0x2ad7d2bb; c = _rotl(c, 15) + d;
	b += (d ^ (c | ~a)) + block[9 ] + 0xeb86d391; b = _rotl(b, 21) + c;

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}

// SHA1
#define SHA1_RW(w0, w1, w2, w3)	(W[w0] = ROTATE32((W[w0] ^ W[w1] ^ W[w2] ^ W[w3]), 1))
static void sha1_transform(uint32_t state[5], const uint32_t block[16])
{
	uint32_t A = state[0];
	uint32_t B = state[1];
	uint32_t C = state[2];
	uint32_t D = state[3];
	uint32_t E = state[4];
	uint32_t W[16];
	memcpy(W, block, sizeof(W));

	// Round 1
	E += ROTATE32(A, 5) + (D ^ (B & (C ^ D))) + 0x5a827999 + W[0 ]; B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (C ^ (A & (B ^ C))) + 0x5a827999 + W[1 ]; A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (B ^ (E & (A ^ B))) + 0x5a827999 + W[2 ]; E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (A ^ (D & (E ^ A))) + 0x5a827999 + W[3 ]; D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (E ^ (C & (D ^ E))) + 0x5a827999 + W[4 ]; C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + (D ^ (B & (C ^ D))) + 0x5a827999 + W[5 ]; B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (C ^ (A & (B ^ C))) + 0x5a827999 + W[6 ]; A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (B ^ (E & (A ^ B))) + 0x5a827999 + W[7 ]; E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (A ^ (D & (E ^ A))) + 0x5a827999 + W[8 ]; D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (E ^ (C & (D ^ E))) + 0x5a827999 + W[9 ]; C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + (D ^ (B & (C ^ D))) + 0x5a827999 + W[10]; B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (C ^ (A & (B ^ C))) + 0x5a827999 + W[11]; A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (B ^ (E & (A ^ B))) + 0x5a827999 + W[12]; E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (A ^ (D & (E ^ A))) + 0x5a827999 + W[13]; D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (E ^ (C & (D ^ E))) + 0x5a827999 + W[14]; C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + (D ^ (B & (C ^ D))) + 0x5a827999 + W[15]; B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (C ^ (A & (B ^ C))) + 0x5a827999 + SHA1_RW(0, 13,  8, 2); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (B ^ (E & (A ^ B))) + 0x5a827999 + SHA1_RW(1, 14,  9, 3); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (A ^ (D & (E ^ A))) + 0x5a827999 + SHA1_RW(2, 15, 10, 4); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (E ^ (C & (D ^ E))) + 0x5a827999 + SHA1_RW(3,  0, 11, 5); C = ROTATE32(C, 30);

	// Round 2
	E += ROTATE32(A, 5) + (B ^ C ^ D) + 0x6ed9eba1 + SHA1_RW(4 , 1 , 12, 6); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (A ^ B ^ C) + 0x6ed9eba1 + SHA1_RW(5 , 2 , 13, 7); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (E ^ A ^ B) + 0x6ed9eba1 + SHA1_RW(6 , 3 , 14, 8); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (D ^ E ^ A) + 0x6ed9eba1 + SHA1_RW(7 , 4 , 15, 9); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (C ^ D ^ E) + 0x6ed9eba1 + SHA1_RW(8 , 5 , 0, 10); C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + (B ^ C ^ D) + 0x6ed9eba1 + SHA1_RW(9 , 6 , 1, 11); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (A ^ B ^ C) + 0x6ed9eba1 + SHA1_RW(10, 7 , 2, 12); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (E ^ A ^ B) + 0x6ed9eba1 + SHA1_RW(11, 8 , 3, 13); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (D ^ E ^ A) + 0x6ed9eba1 + SHA1_RW(12, 9 , 4, 14); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (C ^ D ^ E) + 0x6ed9eba1 + SHA1_RW(13, 10, 5, 15); C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + (B ^ C ^ D) + 0x6ed9eba1 + SHA1_RW(14, 11, 6,  0); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (A ^ B ^ C) + 0x6ed9eba1 + SHA1_RW(15, 12, 7,  1); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (E ^ A ^ B) + 0x6ed9eba1 + SHA1_RW(0 , 13, 8,  2); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (D ^ E ^ A) + 0x6ed9eba1 + SHA1_RW(1 , 14, 9,  3); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (C ^ D ^ E) + 0x6ed9eba1 + SHA1_RW(2 , 15, 10, 4); C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + (B ^ C ^ D) + 0x6ed9eba1 + SHA1_RW(3 ,  0, 11, 5); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (A ^ B ^ C) + 0x6ed9eba1 + SHA1_RW(4 ,  1, 12, 6); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (E ^ A ^ B) + 0x6ed9eba1 + SHA1_RW(5 ,  2, 13, 7); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (D ^ E ^ A) + 0x6ed9eba1 + SHA1_RW(6 ,  3, 14, 8); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (C ^ D ^ E) + 0x6ed9eba1 + SHA1_RW(7 ,  4, 15, 9); C = ROTATE32(C, 30);

	// Round 3
	E += ROTATE32(A, 5) + ((B & C) | (D & (B | C))) + 0x8F1BBCDC + SHA1_RW( 8,  5,  0, 10); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + ((A & B) | (C & (A | B))) + 0x8F1BBCDC + SHA1_RW( 9,  6,  1, 11); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + ((E & A) | (B & (E | A))) + 0x8F1BBCDC + SHA1_RW(10,  7,  2, 12); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + ((D & E) | (A & (D | E))) + 0x8F1BBCDC + SHA1_RW(11,  8,  3, 13); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + ((C & D) | (E & (C | D))) + 0x8F1BBCDC + SHA1_RW(12,  9,  4, 14); C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + ((B & C) | (D & (B | C))) + 0x8F1BBCDC + SHA1_RW(13, 10,  5, 15); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + ((A & B) | (C & (A | B))) + 0x8F1BBCDC + SHA1_RW(14, 11,  6,  0); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + ((E & A) | (B & (E | A))) + 0x8F1BBCDC + SHA1_RW(15, 12,  7,  1); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + ((D & E) | (A & (D | E))) + 0x8F1BBCDC + SHA1_RW( 0, 13,  8,  2); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + ((C & D) | (E & (C | D))) + 0x8F1BBCDC + SHA1_RW( 1, 14,  9,  3); C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + ((B & C) | (D & (B | C))) + 0x8F1BBCDC + SHA1_RW( 2, 15, 10,  4); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + ((A & B) | (C & (A | B))) + 0x8F1BBCDC + SHA1_RW( 3,  0, 11,  5); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + ((E & A) | (B & (E | A))) + 0x8F1BBCDC + SHA1_RW( 4,  1, 12,  6); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + ((D & E) | (A & (D | E))) + 0x8F1BBCDC + SHA1_RW( 5,  2, 13,  7); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + ((C & D) | (E & (C | D))) + 0x8F1BBCDC + SHA1_RW( 6,  3, 14,  8); C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + ((B & C) | (D & (B | C))) + 0x8F1BBCDC + SHA1_RW( 7,  4, 15,  9); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + ((A & B) | (C & (A | B))) + 0x8F1BBCDC + SHA1_RW( 8,  5,  0, 10); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + ((E & A) | (B & (E | A))) + 0x8F1BBCDC + SHA1_RW( 9,  6,  1, 11); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + ((D & E) | (A & (D | E))) + 0x8F1BBCDC + SHA1_RW(10,  7,  2, 12); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + ((C & D) | (E & (C | D))) + 0x8F1BBCDC + SHA1_RW(11,  8,  3, 13); C = ROTATE32(C, 30);
								
	// Round 4
	E += ROTATE32(A, 5) + (B ^ C ^ D) + 0xCA62C1D6 + SHA1_RW(12,  9,  4, 14); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (A ^ B ^ C) + 0xCA62C1D6 + SHA1_RW(13, 10,  5, 15); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (E ^ A ^ B) + 0xCA62C1D6 + SHA1_RW(14, 11,  6,  0); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (D ^ E ^ A) + 0xCA62C1D6 + SHA1_RW(15, 12,  7,  1); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (C ^ D ^ E) + 0xCA62C1D6 + SHA1_RW( 0, 13,  8,  2); C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + (B ^ C ^ D) + 0xCA62C1D6 + SHA1_RW( 1, 14,  9,  3); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (A ^ B ^ C) + 0xCA62C1D6 + SHA1_RW( 2, 15, 10,  4); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (E ^ A ^ B) + 0xCA62C1D6 + SHA1_RW( 3,  0, 11,  5); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (D ^ E ^ A) + 0xCA62C1D6 + SHA1_RW( 4,  1, 12,  6); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (C ^ D ^ E) + 0xCA62C1D6 + SHA1_RW( 5,  2, 13,  7); C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + (B ^ C ^ D) + 0xCA62C1D6 + SHA1_RW( 6,  3, 14,  8); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (A ^ B ^ C) + 0xCA62C1D6 + SHA1_RW( 7,  4, 15,  9); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (E ^ A ^ B) + 0xCA62C1D6 + SHA1_RW( 8,  5,  0, 10); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (D ^ E ^ A) + 0xCA62C1D6 + SHA1_RW( 9,  6,  1, 11); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (C ^ D ^ E) + 0xCA62C1D6 + SHA1_RW(10,  7,  2, 12); C = ROTATE32(C, 30);
	E += ROTATE32(A, 5) + (B ^ C ^ D) + 0xCA62C1D6 + SHA1_RW(11,  8,  3, 13); B = ROTATE32(B, 30);
	D += ROTATE32(E, 5) + (A ^ B ^ C) + 0xCA62C1D6 + SHA1_RW(12,  9,  4, 14); A = ROTATE32(A, 30);
	C += ROTATE32(D, 5) + (E ^ A ^ B) + 0xCA62C1D6 + SHA1_RW(13, 10,  5, 15); E = ROTATE32(E, 30);
	B += ROTATE32(C, 5) + (D ^ E ^ A) + 0xCA62C1D6 + SHA1_RW(14, 11,  6,  0); D = ROTATE32(D, 30);
	A += ROTATE32(B, 5) + (C ^ D ^ E) + 0xCA62C1D6 + SHA1_RW(15, 12,  7,  1); C = ROTATE32(C, 30);

	state[0] += A;
	state[1] += B;
	state[2] += C;
	state[3] += D;
	state[4] += E;
}

// SHA256
#define R_E(x) (ROTATE32(x, 26) ^ ROTATE32(x, 21) ^ ROTATE32(x,  7))
#define R_A(x) (ROTATE32(x, 30) ^ ROTATE32(x, 19) ^ ROTATE32(x, 10))
#define R0(x)  (ROTATE32(x, 25) ^ ROTATE32(x, 14) ^ (x>>  3))
#define R1(x)  (ROTATE32(x, 15) ^ ROTATE32(x, 13) ^ (x>> 10))
static void sha256_transform(uint32_t state[8], const uint32_t block[16])
{
	uint32_t A = state[0];
	uint32_t B = state[1];
	uint32_t C = state[2];
	uint32_t D = state[3];
	uint32_t E = state[4];
	uint32_t F = state[5];
	uint32_t G = state[6];
	uint32_t H = state[7];
	uint32_t W[16];
	memcpy(W, block, sizeof(W));

	/* Rounds */
	H += R_E(E) + (G ^ (E & (F ^ G))) + 0x428A2F98 + W[ 0]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	G += R_E(D) + (F ^ (D & (E ^ F))) + 0x71374491 + W[ 1]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	F += R_E(C) + (E ^ (C & (D ^ E))) + 0xB5C0FBCF + W[ 2]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	E += R_E(B) + (D ^ (B & (C ^ D))) + 0xE9B5DBA5 + W[ 3]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	D += R_E(A) + (C ^ (A & (B ^ C))) + 0x3956C25B + W[ 4]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	C += R_E(H) + (B ^ (H & (A ^ B))) + 0x59F111F1 + W[ 5]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	B += R_E(G) + (A ^ (G & (H ^ A))) + 0x923F82A4 + W[ 6]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	A += R_E(F) + (H ^ (F & (G ^ H))) + 0xAB1C5ED5 + W[ 7]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
	H += R_E(E) + (G ^ (E & (F ^ G))) + 0xD807AA98 + W[ 8]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	G += R_E(D) + (F ^ (D & (E ^ F))) + 0x12835B01 + W[ 9]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	F += R_E(C) + (E ^ (C & (D ^ E))) + 0x243185BE + W[10]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	E += R_E(B) + (D ^ (B & (C ^ D))) + 0x550C7DC3 + W[11]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	D += R_E(A) + (C ^ (A & (B ^ C))) + 0x72BE5D74 + W[12]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	C += R_E(H) + (B ^ (H & (A ^ B))) + 0x80DEB1FE + W[13]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	B += R_E(G) + (A ^ (G & (H ^ A))) + 0x9BDC06A7 + W[14]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	A += R_E(F) + (H ^ (F & (G ^ H))) + 0xC19BF174 + W[15]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));

	W[ 0] += R1(W[14]) + W[9 ] + R0(W[1 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0xE49B69C1 + W[ 0]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 1] += R1(W[15]) + W[10] + R0(W[2 ]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0xEFBE4786 + W[ 1]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[ 2] += R1(W[0 ]) + W[11] + R0(W[3 ]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0x0FC19DC6 + W[ 2]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[ 3] += R1(W[1 ]) + W[12] + R0(W[4 ]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0x240CA1CC + W[ 3]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[ 4] += R1(W[2 ]) + W[13] + R0(W[5 ]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0x2DE92C6F + W[ 4]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[ 5] += R1(W[3 ]) + W[14] + R0(W[6 ]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0x4A7484AA + W[ 5]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[ 6] += R1(W[4 ]) + W[15] + R0(W[7 ]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0x5CB0A9DC + W[ 6]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[ 7] += R1(W[5 ]) + W[0 ] + R0(W[8 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x76F988DA + W[ 7]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
	W[ 8] += R1(W[6 ]) + W[1 ] + R0(W[9 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0x983E5152 + W[ 8]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 9] += R1(W[7 ]) + W[2 ] + R0(W[10]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0xA831C66D + W[ 9]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[10] += R1(W[8 ]) + W[3 ] + R0(W[11]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0xB00327C8 + W[10]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[11] += R1(W[9 ]) + W[4 ] + R0(W[12]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0xBF597FC7 + W[11]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[12] += R1(W[10]) + W[5 ] + R0(W[13]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0xC6E00BF3 + W[12]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[13] += R1(W[11]) + W[6 ] + R0(W[14]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0xD5A79147 + W[13]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[14] += R1(W[12]) + W[7 ] + R0(W[15]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0x06CA6351 + W[14]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[15] += R1(W[13]) + W[8 ] + R0(W[0 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x14292967 + W[15]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
																    
	W[ 0] += R1(W[14]) + W[9 ] + R0(W[1 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0x27B70A85 + W[ 0]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 1] += R1(W[15]) + W[10] + R0(W[2 ]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0x2E1B2138 + W[ 1]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[ 2] += R1(W[0 ]) + W[11] + R0(W[3 ]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0x4D2C6DFC + W[ 2]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[ 3] += R1(W[1 ]) + W[12] + R0(W[4 ]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0x53380D13 + W[ 3]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[ 4] += R1(W[2 ]) + W[13] + R0(W[5 ]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0x650A7354 + W[ 4]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[ 5] += R1(W[3 ]) + W[14] + R0(W[6 ]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0x766A0ABB + W[ 5]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[ 6] += R1(W[4 ]) + W[15] + R0(W[7 ]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0x81C2C92E + W[ 6]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[ 7] += R1(W[5 ]) + W[0 ] + R0(W[8 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x92722C85 + W[ 7]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
	W[ 8] += R1(W[6 ]) + W[1 ] + R0(W[9 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0xA2BFE8A1 + W[ 8]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 9] += R1(W[7 ]) + W[2 ] + R0(W[10]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0xA81A664B + W[ 9]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[10] += R1(W[8 ]) + W[3 ] + R0(W[11]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0xC24B8B70 + W[10]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[11] += R1(W[9 ]) + W[4 ] + R0(W[12]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0xC76C51A3 + W[11]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[12] += R1(W[10]) + W[5 ] + R0(W[13]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0xD192E819 + W[12]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[13] += R1(W[11]) + W[6 ] + R0(W[14]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0xD6990624 + W[13]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[14] += R1(W[12]) + W[7 ] + R0(W[15]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0xF40E3585 + W[14]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[15] += R1(W[13]) + W[8 ] + R0(W[0 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x106AA070 + W[15]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
																    
	W[ 0] += R1(W[14]) + W[9 ] + R0(W[1 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0x19A4C116 + W[ 0]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 1] += R1(W[15]) + W[10] + R0(W[2 ]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0x1E376C08 + W[ 1]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[ 2] += R1(W[0 ]) + W[11] + R0(W[3 ]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0x2748774C + W[ 2]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[ 3] += R1(W[1 ]) + W[12] + R0(W[4 ]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0x34B0BCB5 + W[ 3]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[ 4] += R1(W[2 ]) + W[13] + R0(W[5 ]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0x391C0CB3 + W[ 4]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[ 5] += R1(W[3 ]) + W[14] + R0(W[6 ]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0x4ED8AA4A + W[ 5]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[ 6] += R1(W[4 ]) + W[15] + R0(W[7 ]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0x5B9CCA4F + W[ 6]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[ 7] += R1(W[5 ]) + W[0 ] + R0(W[8 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x682E6FF3 + W[ 7]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
	W[ 8] += R1(W[6 ]) + W[1 ] + R0(W[9 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0x748F82EE + W[ 8]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 9] += R1(W[7 ]) + W[2 ] + R0(W[10]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0x78A5636F + W[ 9]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[10] += R1(W[8 ]) + W[3 ] + R0(W[11]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0x84C87814 + W[10]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[11] += R1(W[9 ]) + W[4 ] + R0(W[12]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0x8CC70208 + W[11]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[12] += R1(W[10]) + W[5 ] + R0(W[13]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0x90BEFFFA + W[12]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[13] += R1(W[11]) + W[6 ] + R0(W[14]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0xA4506CEB + W[13]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[14] += R1(W[12]) + W[7 ] + R0(W[15]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0xBEF9A3F7 + W[14]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[15] += R1(W[13]) + W[8 ] + R0(W[0 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0xC67178F2 + W[15]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));

	state[0] += A;
	state[1] += B;
	state[2] += C;
	state[3] += D;
	state[4] += E;
	state[5] += F;
	state[6] += G;
	state[7] += H;
}

// SHA512
#undef R_E
#undef R_A
#undef R0
#undef R1
#define R_E(x) (ROTATE64(x, 50) ^ ROTATE64(x, 46) ^ ROTATE64(x, 23))
#define R_A(x) (ROTATE64(x, 36) ^ ROTATE64(x, 30) ^ ROTATE64(x, 25))
#define R0(x)  (ROTATE64(x, 63) ^ ROTATE64(x, 56) ^ (x >> 7))
#define R1(x)  (ROTATE64(x, 45) ^ ROTATE64(x, 3 ) ^ (x >> 6))
static void sha512_transform(uint64_t state[8], const uint64_t block[16])
{
	uint64_t A = state[0];
	uint64_t B = state[1];
	uint64_t C = state[2];
	uint64_t D = state[3];
	uint64_t E = state[4];
	uint64_t F = state[5];
	uint64_t G = state[6];
	uint64_t H = state[7];
	uint64_t W[16];
	memcpy(W, block, sizeof(W));

	/* Rounds */
	H += R_E(E) + (G ^ (E & (F ^ G))) + 0x428A2F98D728AE22ULL + W[ 0]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	G += R_E(D) + (F ^ (D & (E ^ F))) + 0x7137449123EF65CDULL + W[ 1]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	F += R_E(C) + (E ^ (C & (D ^ E))) + 0xB5C0FBCFEC4D3B2FULL + W[ 2]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	E += R_E(B) + (D ^ (B & (C ^ D))) + 0xE9B5DBA58189DBBCULL + W[ 3]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	D += R_E(A) + (C ^ (A & (B ^ C))) + 0x3956C25BF348B538ULL + W[ 4]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	C += R_E(H) + (B ^ (H & (A ^ B))) + 0x59F111F1B605D019ULL + W[ 5]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	B += R_E(G) + (A ^ (G & (H ^ A))) + 0x923F82A4AF194F9BULL + W[ 6]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	A += R_E(F) + (H ^ (F & (G ^ H))) + 0xAB1C5ED5DA6D8118ULL + W[ 7]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
	H += R_E(E) + (G ^ (E & (F ^ G))) + 0xD807AA98A3030242ULL + W[ 8]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	G += R_E(D) + (F ^ (D & (E ^ F))) + 0x12835B0145706FBEULL + W[ 9]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	F += R_E(C) + (E ^ (C & (D ^ E))) + 0x243185BE4EE4B28CULL + W[10]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	E += R_E(B) + (D ^ (B & (C ^ D))) + 0x550C7DC3D5FFB4E2ULL + W[11]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	D += R_E(A) + (C ^ (A & (B ^ C))) + 0x72BE5D74F27B896FULL + W[12]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	C += R_E(H) + (B ^ (H & (A ^ B))) + 0x80DEB1FE3B1696B1ULL + W[13]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	B += R_E(G) + (A ^ (G & (H ^ A))) + 0x9BDC06A725C71235ULL + W[14]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	A += R_E(F) + (H ^ (F & (G ^ H))) + 0xC19BF174CF692694ULL + W[15]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));

	W[ 0] += R1(W[14]) + W[9 ] + R0(W[1 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0xE49B69C19EF14AD2ULL + W[ 0]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 1] += R1(W[15]) + W[10] + R0(W[2 ]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0xEFBE4786384F25E3ULL + W[ 1]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[ 2] += R1(W[0 ]) + W[11] + R0(W[3 ]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0x0FC19DC68B8CD5B5ULL + W[ 2]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[ 3] += R1(W[1 ]) + W[12] + R0(W[4 ]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0x240CA1CC77AC9C65ULL + W[ 3]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[ 4] += R1(W[2 ]) + W[13] + R0(W[5 ]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0x2DE92C6F592B0275ULL + W[ 4]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[ 5] += R1(W[3 ]) + W[14] + R0(W[6 ]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0x4A7484AA6EA6E483ULL + W[ 5]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[ 6] += R1(W[4 ]) + W[15] + R0(W[7 ]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0x5CB0A9DCBD41FBD4ULL + W[ 6]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[ 7] += R1(W[5 ]) + W[0 ] + R0(W[8 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x76F988DA831153B5ULL + W[ 7]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
	W[ 8] += R1(W[6 ]) + W[1 ] + R0(W[9 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0x983E5152EE66DFABULL + W[ 8]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 9] += R1(W[7 ]) + W[2 ] + R0(W[10]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0xA831C66D2DB43210ULL + W[ 9]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[10] += R1(W[8 ]) + W[3 ] + R0(W[11]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0xB00327C898FB213FULL + W[10]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[11] += R1(W[9 ]) + W[4 ] + R0(W[12]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0xBF597FC7BEEF0EE4ULL + W[11]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[12] += R1(W[10]) + W[5 ] + R0(W[13]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0xC6E00BF33DA88FC2ULL + W[12]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[13] += R1(W[11]) + W[6 ] + R0(W[14]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0xD5A79147930AA725ULL + W[13]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[14] += R1(W[12]) + W[7 ] + R0(W[15]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0x06CA6351E003826FULL + W[14]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[15] += R1(W[13]) + W[8 ] + R0(W[0 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x142929670A0E6E70ULL + W[15]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
																    																						  
	W[ 0] += R1(W[14]) + W[9 ] + R0(W[1 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0x27B70A8546D22FFCULL + W[ 0]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 1] += R1(W[15]) + W[10] + R0(W[2 ]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0x2E1B21385C26C926ULL + W[ 1]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[ 2] += R1(W[0 ]) + W[11] + R0(W[3 ]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0x4D2C6DFC5AC42AEDULL + W[ 2]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[ 3] += R1(W[1 ]) + W[12] + R0(W[4 ]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0x53380D139D95B3DFULL + W[ 3]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[ 4] += R1(W[2 ]) + W[13] + R0(W[5 ]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0x650A73548BAF63DEULL + W[ 4]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[ 5] += R1(W[3 ]) + W[14] + R0(W[6 ]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0x766A0ABB3C77B2A8ULL + W[ 5]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[ 6] += R1(W[4 ]) + W[15] + R0(W[7 ]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0x81C2C92E47EDAEE6ULL + W[ 6]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[ 7] += R1(W[5 ]) + W[0 ] + R0(W[8 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x92722C851482353BULL + W[ 7]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
	W[ 8] += R1(W[6 ]) + W[1 ] + R0(W[9 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0xA2BFE8A14CF10364ULL + W[ 8]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 9] += R1(W[7 ]) + W[2 ] + R0(W[10]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0xA81A664BBC423001ULL + W[ 9]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[10] += R1(W[8 ]) + W[3 ] + R0(W[11]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0xC24B8B70D0F89791ULL + W[10]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[11] += R1(W[9 ]) + W[4 ] + R0(W[12]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0xC76C51A30654BE30ULL + W[11]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[12] += R1(W[10]) + W[5 ] + R0(W[13]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0xD192E819D6EF5218ULL + W[12]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[13] += R1(W[11]) + W[6 ] + R0(W[14]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0xD69906245565A910ULL + W[13]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[14] += R1(W[12]) + W[7 ] + R0(W[15]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0xF40E35855771202AULL + W[14]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[15] += R1(W[13]) + W[8 ] + R0(W[0 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x106AA07032BBD1B8ULL + W[15]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
		
	W[ 0] += R1(W[14]) + W[9 ] + R0(W[1 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0x19A4C116B8D2D0C8ULL + W[ 0]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 1] += R1(W[15]) + W[10] + R0(W[2 ]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0x1E376C085141AB53ULL + W[ 1]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[ 2] += R1(W[0 ]) + W[11] + R0(W[3 ]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0x2748774CDF8EEB99ULL + W[ 2]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[ 3] += R1(W[1 ]) + W[12] + R0(W[4 ]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0x34B0BCB5E19B48A8ULL + W[ 3]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[ 4] += R1(W[2 ]) + W[13] + R0(W[5 ]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0x391C0CB3C5C95A63ULL + W[ 4]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[ 5] += R1(W[3 ]) + W[14] + R0(W[6 ]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0x4ED8AA4AE3418ACBULL + W[ 5]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[ 6] += R1(W[4 ]) + W[15] + R0(W[7 ]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0x5B9CCA4F7763E373ULL + W[ 6]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[ 7] += R1(W[5 ]) + W[0 ] + R0(W[8 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x682E6FF3D6B2B8A3ULL + W[ 7]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
	W[ 8] += R1(W[6 ]) + W[1 ] + R0(W[9 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0x748F82EE5DEFB2FCULL + W[ 8]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 9] += R1(W[7 ]) + W[2 ] + R0(W[10]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0x78A5636F43172F60ULL + W[ 9]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[10] += R1(W[8 ]) + W[3 ] + R0(W[11]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0x84C87814A1F0AB72ULL + W[10]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[11] += R1(W[9 ]) + W[4 ] + R0(W[12]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0x8CC702081A6439ECULL + W[11]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[12] += R1(W[10]) + W[5 ] + R0(W[13]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0x90BEFFFA23631E28ULL + W[12]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[13] += R1(W[11]) + W[6 ] + R0(W[14]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0xA4506CEBDE82BDE9ULL + W[13]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[14] += R1(W[12]) + W[7 ] + R0(W[15]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0xBEF9A3F7B2C67915ULL + W[14]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[15] += R1(W[13]) + W[8 ] + R0(W[0 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0xC67178F2E372532BULL + W[15]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
																																							  
	W[ 0] += R1(W[14]) + W[9 ] + R0(W[1 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0xCA273ECEEA26619CULL + W[ 0]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 1] += R1(W[15]) + W[10] + R0(W[2 ]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0xD186B8C721C0C207ULL + W[ 1]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[ 2] += R1(W[0 ]) + W[11] + R0(W[3 ]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0xEADA7DD6CDE0EB1EULL + W[ 2]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[ 3] += R1(W[1 ]) + W[12] + R0(W[4 ]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0xF57D4F7FEE6ED178ULL + W[ 3]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[ 4] += R1(W[2 ]) + W[13] + R0(W[5 ]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0x06F067AA72176FBAULL + W[ 4]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[ 5] += R1(W[3 ]) + W[14] + R0(W[6 ]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0x0A637DC5A2C898A6ULL + W[ 5]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[ 6] += R1(W[4 ]) + W[15] + R0(W[7 ]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0x113F9804BEF90DAEULL + W[ 6]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[ 7] += R1(W[5 ]) + W[0 ] + R0(W[8 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x1B710B35131C471BULL + W[ 7]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));
	W[ 8] += R1(W[6 ]) + W[1 ] + R0(W[9 ]); H += R_E(E) + (G ^ (E & (F ^ G))) + 0x28db77f523047d84ULL + W[ 8]; D += H; H += R_A(A) + ((A & B) | (C & (A | B)));
	W[ 9] += R1(W[7 ]) + W[2 ] + R0(W[10]); G += R_E(D) + (F ^ (D & (E ^ F))) + 0x32caab7b40c72493ULL + W[ 9]; C += G; G += R_A(H) + ((H & A) | (B & (H | A)));
	W[10] += R1(W[8 ]) + W[3 ] + R0(W[11]); F += R_E(C) + (E ^ (C & (D ^ E))) + 0x3c9ebe0a15c9bebcULL + W[10]; B += F; F += R_A(G) + ((G & H) | (A & (G | H)));
	W[11] += R1(W[9 ]) + W[4 ] + R0(W[12]); E += R_E(B) + (D ^ (B & (C ^ D))) + 0x431d67c49c100d4cULL + W[11]; A += E; E += R_A(F) + ((F & G) | (H & (F | G)));
	W[12] += R1(W[10]) + W[5 ] + R0(W[13]); D += R_E(A) + (C ^ (A & (B ^ C))) + 0x4cc5d4becb3e42b6ULL + W[12]; H += D; D += R_A(E) + ((E & F) | (G & (E | F)));
	W[13] += R1(W[11]) + W[6 ] + R0(W[14]); C += R_E(H) + (B ^ (H & (A ^ B))) + 0x597f299cfc657e2aULL + W[13]; G += C; C += R_A(D) + ((D & E) | (F & (D | E)));
	W[14] += R1(W[12]) + W[7 ] + R0(W[15]); B += R_E(G) + (A ^ (G & (H ^ A))) + 0x5fcb6fab3ad6faecULL + W[14]; F += B; B += R_A(C) + ((C & D) | (E & (C | D)));
	W[15] += R1(W[13]) + W[8 ] + R0(W[0 ]); A += R_E(F) + (H ^ (F & (G ^ H))) + 0x6c44198c4a475817ULL + W[15]; E += A; A += R_A(B) + ((B & C) | (D & (B | C)));

	state[0] += A;
	state[1] += B;
	state[2] += C;
	state[3] += D;
	state[4] += E;
	state[5] += F;
	state[6] += G;
	state[7] += H;
}