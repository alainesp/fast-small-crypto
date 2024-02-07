//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA1 - Secure Hash Algorithm 1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#define SimdScalarType uint32_t
#include "simd.hpp"
using namespace simd;

/// <summary>
/// SHA1 compress block
/// </summary>
/// <param name="state">The SHA1 state</param>
/// <param name="block">The message to compress</param>
extern "C" void sha1_block_avx(simd::Vec128u32 state[5], const simd::Vec128u32 W[16]) noexcept
{
	simd::Vec128u32 E, A, C, D, B, W0, W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, W11, W12, W13, W14, W15, t;

	// Load state
	E = load(state +  4);	A = load(state +  0);	C = load(state +  2);	D = load(state +  3);	B = load(state +  1);
	W0  = load(W +  0);	W1  = load(W +  1);	W2  = load(W +  2);	W3  = load(W +  3);
	W4  = load(W +  4);	W5  = load(W +  5);	W6  = load(W +  6);	W7  = load(W +  7);
	W8  = load(W +  8);	W9  = load(W +  9);	W10 = load(W + 10);	W11 = load(W + 11);
	W12 = load(W + 12);	W13 = load(W + 13);	W14 = load(W + 14);	W15 = load(W + 15);

	// Round 1
	E += rotl<uint32_t,  5>(A,  5);	E += (D ^ (B & (C ^ D)));	E += UINT32_C(0x5a827999);	E += W0;	B = rotl<uint32_t, 30>(B, 30);
	D += rotl<uint32_t,  5>(E,  5);	D += (C ^ (A & (B ^ C)));	D += UINT32_C(0x5a827999);	D += W1;	A = rotl<uint32_t, 30>(A, 30);
	C += rotl<uint32_t,  5>(D,  5);	C += (B ^ (E & (A ^ B)));	C += UINT32_C(0x5a827999);	C += W2;	E = rotl<uint32_t, 30>(E, 30);
	B += rotl<uint32_t,  5>(C,  5);	B += (A ^ (D & (E ^ A)));	B += UINT32_C(0x5a827999);	B += W3;	D = rotl<uint32_t, 30>(D, 30);
	A += rotl<uint32_t,  5>(B,  5);	A += (E ^ (C & (D ^ E)));	A += UINT32_C(0x5a827999);	A += W4;	C = rotl<uint32_t, 30>(C, 30);
	E += rotl<uint32_t,  5>(A,  5);	E += (D ^ (B & (C ^ D)));	E += UINT32_C(0x5a827999);	E += W5;	B = rotl<uint32_t, 30>(B, 30);
	D += rotl<uint32_t,  5>(E,  5);	D += (C ^ (A & (B ^ C)));	D += UINT32_C(0x5a827999);	D += W6;	A = rotl<uint32_t, 30>(A, 30);
	C += rotl<uint32_t,  5>(D,  5);	C += (B ^ (E & (A ^ B)));	C += UINT32_C(0x5a827999);	C += W7;	E = rotl<uint32_t, 30>(E, 30);
	B += rotl<uint32_t,  5>(C,  5);	B += (A ^ (D & (E ^ A)));	B += UINT32_C(0x5a827999);	B += W8;	D = rotl<uint32_t, 30>(D, 30);
	A += rotl<uint32_t,  5>(B,  5);	A += (E ^ (C & (D ^ E)));	A += UINT32_C(0x5a827999);	A += W9;	C = rotl<uint32_t, 30>(C, 30);
	E += rotl<uint32_t,  5>(A,  5);	E += (D ^ (B & (C ^ D)));	E += UINT32_C(0x5a827999);	E += W10;	B = rotl<uint32_t, 30>(B, 30);
	D += rotl<uint32_t,  5>(E,  5);	D += (C ^ (A & (B ^ C)));	D += UINT32_C(0x5a827999);	D += W11;	A = rotl<uint32_t, 30>(A, 30);
	C += rotl<uint32_t,  5>(D,  5);	C += (B ^ (E & (A ^ B)));	C += UINT32_C(0x5a827999);	C += W12;	E = rotl<uint32_t, 30>(E, 30);
	B += rotl<uint32_t,  5>(C,  5);	B += (A ^ (D & (E ^ A)));	B += UINT32_C(0x5a827999);	B += W13;	D = rotl<uint32_t, 30>(D, 30);
	A += rotl<uint32_t,  5>(B,  5);	A += (E ^ (C & (D ^ E)));	A += UINT32_C(0x5a827999);	A += W14;	C = rotl<uint32_t, 30>(C, 30);
	E += rotl<uint32_t,  5>(A,  5);	E += (D ^ (B & (C ^ D)));	E += UINT32_C(0x5a827999);	E += W15;	B = rotl<uint32_t, 30>(B, 30);
	t = (W2 ^ W13 ^ W8);	D += UINT32_C(0x5a827999);	W0 ^= t;	W0 = rotl<uint32_t,  1>(W0,  1);	D += rotl<uint32_t,  5>(E,  5);	D += (C ^ (A & (B ^ C)));	D += W0;	A = rotl<uint32_t, 30>(A, 30);
	t = (W3 ^ W14 ^ W9);	C += UINT32_C(0x5a827999);	W1 ^= t;	W1 = rotl<uint32_t,  1>(W1,  1);	C += rotl<uint32_t,  5>(D,  5);	C += (B ^ (E & (A ^ B)));	C += W1;	E = rotl<uint32_t, 30>(E, 30);
	t = (W4 ^ W15 ^ W10);	B += UINT32_C(0x5a827999);	W2 ^= t;	W2 = rotl<uint32_t,  1>(W2,  1);	B += rotl<uint32_t,  5>(C,  5);	B += (A ^ (D & (E ^ A)));	B += W2;	D = rotl<uint32_t, 30>(D, 30);
	t = (W5 ^ W0 ^ W11);	A += UINT32_C(0x5a827999);	W3 ^= t;	W3 = rotl<uint32_t,  1>(W3,  1);	A += rotl<uint32_t,  5>(B,  5);	A += (E ^ (C & (D ^ E)));	A += W3;	C = rotl<uint32_t, 30>(C, 30);

	// Round 2                                                
	t = (W6  ^ W1  ^ W12);	E += UINT32_C(0x6ed9eba1);	W4  ^= t;	W4  = rotl<uint32_t,  1>(W4 ,  1);	E += rotl<uint32_t,  5>(A,  5);	E += (B ^ C ^ D);	E += W4;	B = rotl<uint32_t, 30>(B, 30);
	t = (W7  ^ W2  ^ W13);	D += UINT32_C(0x6ed9eba1);	W5  ^= t;	W5  = rotl<uint32_t,  1>(W5 ,  1);	D += rotl<uint32_t,  5>(E,  5);	D += (A ^ B ^ C);	D += W5;	A = rotl<uint32_t, 30>(A, 30);
	t = (W8  ^ W3  ^ W14);	C += UINT32_C(0x6ed9eba1);	W6  ^= t;	W6  = rotl<uint32_t,  1>(W6 ,  1);	C += rotl<uint32_t,  5>(D,  5);	C += (E ^ A ^ B);	C += W6;	E = rotl<uint32_t, 30>(E, 30);
	t = (W9  ^ W4  ^ W15);	B += UINT32_C(0x6ed9eba1);	W7  ^= t;	W7  = rotl<uint32_t,  1>(W7 ,  1);	B += rotl<uint32_t,  5>(C,  5);	B += (D ^ E ^ A);	B += W7;	D = rotl<uint32_t, 30>(D, 30);
	t = (W10 ^ W5  ^ W0 );	A += UINT32_C(0x6ed9eba1);	W8  ^= t;	W8  = rotl<uint32_t,  1>(W8 ,  1);	A += rotl<uint32_t,  5>(B,  5);	A += (C ^ D ^ E);	A += W8;	C = rotl<uint32_t, 30>(C, 30);
	t = (W11 ^ W6  ^ W1 );	E += UINT32_C(0x6ed9eba1);	W9  ^= t;	W9  = rotl<uint32_t,  1>(W9 ,  1);	E += rotl<uint32_t,  5>(A,  5);	E += (B ^ C ^ D);	E += W9;	B = rotl<uint32_t, 30>(B, 30);
	t = (W12 ^ W7  ^ W2 );	D += UINT32_C(0x6ed9eba1);	W10 ^= t;	W10 = rotl<uint32_t,  1>(W10,  1);	D += rotl<uint32_t,  5>(E,  5);	D += (A ^ B ^ C);	D += W10;	A = rotl<uint32_t, 30>(A, 30);
	t = (W13 ^ W8  ^ W3 );	C += UINT32_C(0x6ed9eba1);	W11 ^= t;	W11 = rotl<uint32_t,  1>(W11,  1);	C += rotl<uint32_t,  5>(D,  5);	C += (E ^ A ^ B);	C += W11;	E = rotl<uint32_t, 30>(E, 30);
	t = (W14 ^ W9  ^ W4 );	B += UINT32_C(0x6ed9eba1);	W12 ^= t;	W12 = rotl<uint32_t,  1>(W12,  1);	B += rotl<uint32_t,  5>(C,  5);	B += (D ^ E ^ A);	B += W12;	D = rotl<uint32_t, 30>(D, 30);
	t = (W15 ^ W10 ^ W5 );	A += UINT32_C(0x6ed9eba1);	W13 ^= t;	W13 = rotl<uint32_t,  1>(W13,  1);	A += rotl<uint32_t,  5>(B,  5);	A += (C ^ D ^ E);	A += W13;	C = rotl<uint32_t, 30>(C, 30);
	t = (W0  ^ W11 ^ W6 );	E += UINT32_C(0x6ed9eba1);	W14 ^= t;	W14 = rotl<uint32_t,  1>(W14,  1);	E += rotl<uint32_t,  5>(A,  5);	E += (B ^ C ^ D);	E += W14;	B = rotl<uint32_t, 30>(B, 30);
	t = (W1  ^ W12 ^ W7 );	D += UINT32_C(0x6ed9eba1);	W15 ^= t;	W15 = rotl<uint32_t,  1>(W15,  1);	D += rotl<uint32_t,  5>(E,  5);	D += (A ^ B ^ C);	D += W15;	A = rotl<uint32_t, 30>(A, 30);
	t = (W2  ^ W13 ^ W8 );	C += UINT32_C(0x6ed9eba1);	W0  ^= t;	W0  = rotl<uint32_t,  1>(W0 ,  1);	C += rotl<uint32_t,  5>(D,  5);	C += (E ^ A ^ B);	C += W0;	E = rotl<uint32_t, 30>(E, 30);
	t = (W3  ^ W14 ^ W9 );	B += UINT32_C(0x6ed9eba1);	W1  ^= t;	W1  = rotl<uint32_t,  1>(W1 ,  1);	B += rotl<uint32_t,  5>(C,  5);	B += (D ^ E ^ A);	B += W1;	D = rotl<uint32_t, 30>(D, 30);
	t = (W4  ^ W15 ^ W10);	A += UINT32_C(0x6ed9eba1);	W2  ^= t;	W2  = rotl<uint32_t,  1>(W2 ,  1);	A += rotl<uint32_t,  5>(B,  5);	A += (C ^ D ^ E);	A += W2;	C = rotl<uint32_t, 30>(C, 30);
	t = (W5  ^ W0  ^ W11);	E += UINT32_C(0x6ed9eba1);	W3  ^= t;	W3  = rotl<uint32_t,  1>(W3 ,  1);	E += rotl<uint32_t,  5>(A,  5);	E += (B ^ C ^ D);	E += W3;	B = rotl<uint32_t, 30>(B, 30);
	t = (W6  ^ W1  ^ W12);	D += UINT32_C(0x6ed9eba1);	W4  ^= t;	W4  = rotl<uint32_t,  1>(W4 ,  1);	D += rotl<uint32_t,  5>(E,  5);	D += (A ^ B ^ C);	D += W4;	A = rotl<uint32_t, 30>(A, 30);
	t = (W7  ^ W2  ^ W13);	C += UINT32_C(0x6ed9eba1);	W5  ^= t;	W5  = rotl<uint32_t,  1>(W5 ,  1);	C += rotl<uint32_t,  5>(D,  5);	C += (E ^ A ^ B);	C += W5;	E = rotl<uint32_t, 30>(E, 30);
	t = (W8  ^ W3  ^ W14);	B += UINT32_C(0x6ed9eba1);	W6  ^= t;	W6  = rotl<uint32_t,  1>(W6 ,  1);	B += rotl<uint32_t,  5>(C,  5);	B += (D ^ E ^ A);	B += W6;	D = rotl<uint32_t, 30>(D, 30);
	t = (W9  ^ W4  ^ W15);	A += UINT32_C(0x6ed9eba1);	W7  ^= t;	W7  = rotl<uint32_t,  1>(W7 ,  1);	A += rotl<uint32_t,  5>(B,  5);	A += (C ^ D ^ E);	A += W7;	C = rotl<uint32_t, 30>(C, 30);

	// Round 3                                                
	t = (W10 ^ W5  ^ W0 );	E += UINT32_C(0x8f1bbcdc);	W8  ^= t;	W8  = rotl<uint32_t,  1>(W8 ,  1);	E += rotl<uint32_t,  5>(A,  5);	E += ((D & C) ^ (B & (D ^ C)));	E += W8;	B = rotl<uint32_t, 30>(B, 30);
	t = (W11 ^ W6  ^ W1 );	D += UINT32_C(0x8f1bbcdc);	W9  ^= t;	W9  = rotl<uint32_t,  1>(W9 ,  1);	D += rotl<uint32_t,  5>(E,  5);	D += ((C & B) ^ (A & (C ^ B)));	D += W9;	A = rotl<uint32_t, 30>(A, 30);
	t = (W12 ^ W7  ^ W2 );	C += UINT32_C(0x8f1bbcdc);	W10 ^= t;	W10 = rotl<uint32_t,  1>(W10,  1);	C += rotl<uint32_t,  5>(D,  5);	C += ((B & A) ^ (E & (B ^ A)));	C += W10;	E = rotl<uint32_t, 30>(E, 30);
	t = (W13 ^ W8  ^ W3 );	B += UINT32_C(0x8f1bbcdc);	W11 ^= t;	W11 = rotl<uint32_t,  1>(W11,  1);	B += rotl<uint32_t,  5>(C,  5);	B += ((A & E) ^ (D & (A ^ E)));	B += W11;	D = rotl<uint32_t, 30>(D, 30);
	t = (W14 ^ W9  ^ W4 );	A += UINT32_C(0x8f1bbcdc);	W12 ^= t;	W12 = rotl<uint32_t,  1>(W12,  1);	A += rotl<uint32_t,  5>(B,  5);	A += ((E & D) ^ (C & (E ^ D)));	A += W12;	C = rotl<uint32_t, 30>(C, 30);
	t = (W15 ^ W10 ^ W5 );	E += UINT32_C(0x8f1bbcdc);	W13 ^= t;	W13 = rotl<uint32_t,  1>(W13,  1);	E += rotl<uint32_t,  5>(A,  5);	E += ((D & C) ^ (B & (D ^ C)));	E += W13;	B = rotl<uint32_t, 30>(B, 30);
	t = (W0  ^ W11 ^ W6 );	D += UINT32_C(0x8f1bbcdc);	W14 ^= t;	W14 = rotl<uint32_t,  1>(W14,  1);	D += rotl<uint32_t,  5>(E,  5);	D += ((C & B) ^ (A & (C ^ B)));	D += W14;	A = rotl<uint32_t, 30>(A, 30);
	t = (W1  ^ W12 ^ W7 );	C += UINT32_C(0x8f1bbcdc);	W15 ^= t;	W15 = rotl<uint32_t,  1>(W15,  1);	C += rotl<uint32_t,  5>(D,  5);	C += ((B & A) ^ (E & (B ^ A)));	C += W15;	E = rotl<uint32_t, 30>(E, 30);
	t = (W2  ^ W13 ^ W8 );	B += UINT32_C(0x8f1bbcdc);	W0  ^= t;	W0  = rotl<uint32_t,  1>(W0 ,  1);	B += rotl<uint32_t,  5>(C,  5);	B += ((A & E) ^ (D & (A ^ E)));	B += W0;	D = rotl<uint32_t, 30>(D, 30);
	t = (W3  ^ W14 ^ W9 );	A += UINT32_C(0x8f1bbcdc);	W1  ^= t;	W1  = rotl<uint32_t,  1>(W1 ,  1);	A += rotl<uint32_t,  5>(B,  5);	A += ((E & D) ^ (C & (E ^ D)));	A += W1;	C = rotl<uint32_t, 30>(C, 30);
	t = (W4  ^ W15 ^ W10);	E += UINT32_C(0x8f1bbcdc);	W2  ^= t;	W2  = rotl<uint32_t,  1>(W2 ,  1);	E += rotl<uint32_t,  5>(A,  5);	E += ((D & C) ^ (B & (D ^ C)));	E += W2;	B = rotl<uint32_t, 30>(B, 30);
	t = (W5  ^ W0  ^ W11);	D += UINT32_C(0x8f1bbcdc);	W3  ^= t;	W3  = rotl<uint32_t,  1>(W3 ,  1);	D += rotl<uint32_t,  5>(E,  5);	D += ((C & B) ^ (A & (C ^ B)));	D += W3;	A = rotl<uint32_t, 30>(A, 30);
	t = (W6  ^ W1  ^ W12);	C += UINT32_C(0x8f1bbcdc);	W4  ^= t;	W4  = rotl<uint32_t,  1>(W4 ,  1);	C += rotl<uint32_t,  5>(D,  5);	C += ((B & A) ^ (E & (B ^ A)));	C += W4;	E = rotl<uint32_t, 30>(E, 30);
	t = (W7  ^ W2  ^ W13);	B += UINT32_C(0x8f1bbcdc);	W5  ^= t;	W5  = rotl<uint32_t,  1>(W5 ,  1);	B += rotl<uint32_t,  5>(C,  5);	B += ((A & E) ^ (D & (A ^ E)));	B += W5;	D = rotl<uint32_t, 30>(D, 30);
	t = (W8  ^ W3  ^ W14);	A += UINT32_C(0x8f1bbcdc);	W6  ^= t;	W6  = rotl<uint32_t,  1>(W6 ,  1);	A += rotl<uint32_t,  5>(B,  5);	A += ((E & D) ^ (C & (E ^ D)));	A += W6;	C = rotl<uint32_t, 30>(C, 30);
	t = (W9  ^ W4  ^ W15);	E += UINT32_C(0x8f1bbcdc);	W7  ^= t;	W7  = rotl<uint32_t,  1>(W7 ,  1);	E += rotl<uint32_t,  5>(A,  5);	E += ((D & C) ^ (B & (D ^ C)));	E += W7;	B = rotl<uint32_t, 30>(B, 30);
	t = (W10 ^ W5  ^ W0 );	D += UINT32_C(0x8f1bbcdc);	W8  ^= t;	W8  = rotl<uint32_t,  1>(W8 ,  1);	D += rotl<uint32_t,  5>(E,  5);	D += ((C & B) ^ (A & (C ^ B)));	D += W8;	A = rotl<uint32_t, 30>(A, 30);
	t = (W11 ^ W6  ^ W1 );	C += UINT32_C(0x8f1bbcdc);	W9  ^= t;	W9  = rotl<uint32_t,  1>(W9 ,  1);	C += rotl<uint32_t,  5>(D,  5);	C += ((B & A) ^ (E & (B ^ A)));	C += W9;	E = rotl<uint32_t, 30>(E, 30);
	t = (W12 ^ W7  ^ W2 );	B += UINT32_C(0x8f1bbcdc);	W10 ^= t;	W10 = rotl<uint32_t,  1>(W10,  1);	B += rotl<uint32_t,  5>(C,  5);	B += ((A & E) ^ (D & (A ^ E)));	B += W10;	D = rotl<uint32_t, 30>(D, 30);
	t = (W13 ^ W8  ^ W3 );	A += UINT32_C(0x8f1bbcdc);	W11 ^= t;	W11 = rotl<uint32_t,  1>(W11,  1);	A += rotl<uint32_t,  5>(B,  5);	A += ((E & D) ^ (C & (E ^ D)));	A += W11;	C = rotl<uint32_t, 30>(C, 30);

	// Round 4                                                
	t = (W14 ^ W9  ^ W4 );	E += UINT32_C(0xca62c1d6);	W12 ^= t;	W12 = rotl<uint32_t,  1>(W12,  1);	E += rotl<uint32_t,  5>(A,  5);	E += (B ^ C ^ D);	E += W12;	B = rotl<uint32_t, 30>(B, 30);
	t = (W15 ^ W10 ^ W5 );	D += UINT32_C(0xca62c1d6);	W13 ^= t;	W13 = rotl<uint32_t,  1>(W13,  1);	D += rotl<uint32_t,  5>(E,  5);	D += (A ^ B ^ C);	D += W13;	A = rotl<uint32_t, 30>(A, 30);
	t = (W0  ^ W11 ^ W6 );	C += UINT32_C(0xca62c1d6);	W14 ^= t;	W14 = rotl<uint32_t,  1>(W14,  1);	C += rotl<uint32_t,  5>(D,  5);	C += (E ^ A ^ B);	C += W14;	E = rotl<uint32_t, 30>(E, 30);
	t = (W1  ^ W12 ^ W7 );	B += UINT32_C(0xca62c1d6);	W15 ^= t;	W15 = rotl<uint32_t,  1>(W15,  1);	B += rotl<uint32_t,  5>(C,  5);	B += (D ^ E ^ A);	B += W15;	D = rotl<uint32_t, 30>(D, 30);
	t = (W2  ^ W13 ^ W8 );	A += UINT32_C(0xca62c1d6);	W0  ^= t;	W0  = rotl<uint32_t,  1>(W0 ,  1);	A += rotl<uint32_t,  5>(B,  5);	A += (C ^ D ^ E);	A += W0;	C = rotl<uint32_t, 30>(C, 30);
	t = (W3  ^ W14 ^ W9 );	E += UINT32_C(0xca62c1d6);	W1  ^= t;	W1  = rotl<uint32_t,  1>(W1 ,  1);	E += rotl<uint32_t,  5>(A,  5);	E += (B ^ C ^ D);	E += W1;	B = rotl<uint32_t, 30>(B, 30);
	t = (W4  ^ W15 ^ W10);	D += UINT32_C(0xca62c1d6);	W2  ^= t;	W2  = rotl<uint32_t,  1>(W2 ,  1);	D += rotl<uint32_t,  5>(E,  5);	D += (A ^ B ^ C);	D += W2;	A = rotl<uint32_t, 30>(A, 30);
	t = (W5  ^ W0  ^ W11);	C += UINT32_C(0xca62c1d6);	W3  ^= t;	W3  = rotl<uint32_t,  1>(W3 ,  1);	C += rotl<uint32_t,  5>(D,  5);	C += (E ^ A ^ B);	C += W3;	E = rotl<uint32_t, 30>(E, 30);
	t = (W6  ^ W1  ^ W12);	B += UINT32_C(0xca62c1d6);	W4  ^= t;	W4  = rotl<uint32_t,  1>(W4 ,  1);	B += rotl<uint32_t,  5>(C,  5);	B += (D ^ E ^ A);	B += W4;	D = rotl<uint32_t, 30>(D, 30);
	t = (W7  ^ W2  ^ W13);	A += UINT32_C(0xca62c1d6);	W5  ^= t;	W5  = rotl<uint32_t,  1>(W5 ,  1);	A += rotl<uint32_t,  5>(B,  5);	A += (C ^ D ^ E);	A += W5;	C = rotl<uint32_t, 30>(C, 30);
	t = (W8  ^ W3  ^ W14);	E += UINT32_C(0xca62c1d6);	W6  ^= t;	W6  = rotl<uint32_t,  1>(W6 ,  1);	E += rotl<uint32_t,  5>(A,  5);	E += (B ^ C ^ D);	E += W6;	B = rotl<uint32_t, 30>(B, 30);
	t = (W9  ^ W4  ^ W15);	D += UINT32_C(0xca62c1d6);	W7  ^= t;	W7  = rotl<uint32_t,  1>(W7 ,  1);	D += rotl<uint32_t,  5>(E,  5);	D += (A ^ B ^ C);	D += W7;	A = rotl<uint32_t, 30>(A, 30);
	t = (W10 ^ W5  ^ W0 );	C += UINT32_C(0xca62c1d6);	W8  ^= t;	W8  = rotl<uint32_t,  1>(W8 ,  1);	C += rotl<uint32_t,  5>(D,  5);	C += (E ^ A ^ B);	C += W8;	E = rotl<uint32_t, 30>(E, 30);
	t = (W11 ^ W6  ^ W1 );	B += UINT32_C(0xca62c1d6);	W9  ^= t;	W9  = rotl<uint32_t,  1>(W9 ,  1);	B += rotl<uint32_t,  5>(C,  5);	B += (D ^ E ^ A);	B += W9;	D = rotl<uint32_t, 30>(D, 30);
	t = (W12 ^ W7  ^ W2 );	A += UINT32_C(0xca62c1d6);	W10 ^= t;	W10 = rotl<uint32_t,  1>(W10,  1);	A += rotl<uint32_t,  5>(B,  5);	A += (C ^ D ^ E);	A += W10;	C = rotl<uint32_t, 30>(C, 30);
	t = (W13 ^ W8  ^ W3 );	E += UINT32_C(0xca62c1d6);	W11 ^= t;	W11 = rotl<uint32_t,  1>(W11,  1);	E += rotl<uint32_t,  5>(A,  5);	E += (B ^ C ^ D);	E += W11;	B = rotl<uint32_t, 30>(B, 30);
	t = (W14 ^ W9  ^ W4 );	D += UINT32_C(0xca62c1d6);	W12 ^= t;	W12 = rotl<uint32_t,  1>(W12,  1);	D += rotl<uint32_t,  5>(E,  5);	D += (A ^ B ^ C);	D += W12;	A = rotl<uint32_t, 30>(A, 30);
	t = (W15 ^ W10 ^ W5 );	C += UINT32_C(0xca62c1d6);	W13 ^= t;	W13 = rotl<uint32_t,  1>(W13,  1);	C += rotl<uint32_t,  5>(D,  5);	C += (E ^ A ^ B);	C += W13;	E = rotl<uint32_t, 30>(E, 30);
	t = (W0  ^ W11 ^ W6 );	B += UINT32_C(0xca62c1d6);	W14 ^= t;	W14 = rotl<uint32_t,  1>(W14,  1);	B += rotl<uint32_t,  5>(C,  5);	B += (D ^ E ^ A);	B += W14;	D = rotl<uint32_t, 30>(D, 30);
	t = (W1  ^ W12 ^ W7 );	A += UINT32_C(0xca62c1d6);	W15 ^= t;	W15 = rotl<uint32_t,  1>(W15,  1);	A += rotl<uint32_t,  5>(B,  5);	A += (C ^ D ^ E);	A += W15;	C = rotl<uint32_t, 30>(C, 30);

	// Save state
	store(state +  4, load(state +  4) + E);
	store(state +  3, load(state +  3) + D);
	store(state +  2, load(state +  2) + C);
	store(state +  1, load(state +  1) + B);
	store(state +  0, load(state +  0) + A);
}

