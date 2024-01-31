//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MD4 Message-Digest Algorithm
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#define SimdScalarType uint32_t
#include "simd.hpp"
using namespace simd;

#ifdef __clang__
#include <bit>
#define _rotl std::rotl
#endif

//// <summary>
//// MD4 compress block
//// </summary>
//// <param name="state">The md4 state</param>
//// <param name="block">The message to compress</param>
extern "C" void md4_block_plain_c(uint32_t state[4], const uint32_t block[16]) noexcept
{
	uint32_t a, b, c, d, t, tt;

	// Load state
	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];

	// Round 1
	for (int i = 0; i < 4; i++) {
		a += block[0];		t = c ^ d;		t &= b;		a += (d ^ t);		a = _rotl(a, 3);
		d += block[1];		t = b ^ c;		t &= a;		d += (c ^ t);		d = _rotl(d, 7);
		c += block[2];		t = a ^ b;		t &= d;		c += (b ^ t);		c = _rotl(c, 11);
		b += block[3];		t = d ^ a;		t &= c;		b += (a ^ t);		b = _rotl(b, 19);
		block += 4;
	}
	block -= 16;

	// Round 2
	for (int i = 0; i < 4; i++) {
		a += block[0];		t = d | c;		tt = c & d;		a += 1518500249;		t &= b;		a += (t | tt);		a = _rotl(a, 3);
		d += block[4];		t = c | b;		tt = b & c;		d += 1518500249;		t &= a;		d += (t | tt);		d = _rotl(d, 5);
		c += block[8];		t = b | a;		tt = a & b;		c += 1518500249;		t &= d;		c += (t | tt);		c = _rotl(c, 9);
		b += block[12];		t = a | d;		tt = d & a;		b += 1518500249;		t &= c;		b += (t | tt);		b = _rotl(b, 13);
		block += 1;
	}
	block -= 4;

	// Round 3

	a += block[0];	t = b ^ c;	a += 1859775393;	a += (t ^ d);	a = _rotl(a, 3);
	d += block[8];	d += 1859775393;	d += (t ^ a);	d = _rotl(d, 9);
	c += block[4];	t = a ^ d;	c += 1859775393;	c += (t ^ b);	c = _rotl(c, 11);
	b += block[12];	b += 1859775393;	b += (t ^ c);	b = _rotl(b, 15);
	a += block[2];	t = b ^ c;	a += 1859775393;	a += (t ^ d);	a = _rotl(a, 3);
	d += block[10];	d += 1859775393;	d += (t ^ a);	d = _rotl(d, 9);
	c += block[6];	t = a ^ d;	c += 1859775393;	c += (t ^ b);	c = _rotl(c, 11);
	b += block[14];	b += 1859775393;	b += (t ^ c);	b = _rotl(b, 15);
	a += block[1];	t = b ^ c;	a += 1859775393;	a += (t ^ d);	a = _rotl(a, 3);
	d += block[9];	d += 1859775393;	d += (t ^ a);	d = _rotl(d, 9);
	c += block[5];	t = a ^ d;	c += 1859775393;	c += (t ^ b);	c = _rotl(c, 11);
	b += block[13];	b += 1859775393;	b += (t ^ c);	b = _rotl(b, 15);
	a += block[3];	t = b ^ c;	a += 1859775393;	a += (t ^ d);	a = _rotl(a, 3);
	d += block[11];	d += 1859775393;	d += (t ^ a);	d = _rotl(d, 9);
	c += block[7];	t = a ^ d;	c += 1859775393;	c += (t ^ b);	c = _rotl(c, 11);
	b += block[15];	b += 1859775393;	b += (t ^ c);	b = _rotl(b, 15);

	// Save state
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}

extern "C" void md4_block_sse2_x1(simd::Vec128u32 state[4], const simd::Vec128u32 block[16]) noexcept
{
	simd::Vec128u32 a, b, c, d, t, tt;

	// Load state
	a = load(state + 0);
	b = load(state + 1);
	c = load(state + 2);
	d = load(state + 3);

	// Round 1
	for (int i = 0; i < 4; i++) {
		a += load(block + 0);		t = c ^ d;		t &= b;		a += (d ^ t);		a = (a << 3) | (a >> 29);
		d += load(block + 1);		t = b ^ c;		t &= a;		d += (c ^ t);		d = (d << 7) | (d >> 25);
		c += load(block + 2);		t = a ^ b;		t &= d;		c += (b ^ t);		c = (c << 11) | (c >> 21);
		b += load(block + 3);		t = d ^ a;		t &= c;		b += (a ^ t);		b = (b << 19) | (b >> 13);
		block += 4;
	}
	block -= 16;

	// Round 2
	for (int i = 0; i < 4; i++) {
		a += load(block + 0);		t = d | c;		tt = c & d;		a += 1518500249;		t &= b;		a += (t | tt);		a = (a << 3) | (a >> 29);
		d += load(block + 4);		t = c | b;		tt = b & c;		d += 1518500249;		t &= a;		d += (t | tt);		d = (d << 5) | (d >> 27);
		c += load(block + 8);		t = b | a;		tt = a & b;		c += 1518500249;		t &= d;		c += (t | tt);		c = (c << 9) | (c >> 23);
		b += load(block + 12);		t = a | d;		tt = d & a;		b += 1518500249;		t &= c;		b += (t | tt);		b = (b << 13) | (b >> 19);
		block += 1;
	}
	block -= 4;

	// Round 3

	a += load(block + 0);	t = b ^ c;	a += 1859775393;	a += (t ^ d);	a = (a << 3) | (a >> 29);
	d += load(block + 8);	d += 1859775393;	d += (t ^ a);	d = (d << 9) | (d >> 23);
	c += load(block + 4);	t = a ^ d;	c += 1859775393;	c += (t ^ b);	c = (c << 11) | (c >> 21);
	b += load(block + 12);	b += 1859775393;	b += (t ^ c);	b = (b << 15) | (b >> 17);
	a += load(block + 2);	t = b ^ c;	a += 1859775393;	a += (t ^ d);	a = (a << 3) | (a >> 29);
	d += load(block + 10);	d += 1859775393;	d += (t ^ a);	d = (d << 9) | (d >> 23);
	c += load(block + 6);	t = a ^ d;	c += 1859775393;	c += (t ^ b);	c = (c << 11) | (c >> 21);
	b += load(block + 14);	b += 1859775393;	b += (t ^ c);	b = (b << 15) | (b >> 17);
	a += load(block + 1);	t = b ^ c;	a += 1859775393;	a += (t ^ d);	a = (a << 3) | (a >> 29);
	d += load(block + 9);	d += 1859775393;	d += (t ^ a);	d = (d << 9) | (d >> 23);
	c += load(block + 5);	t = a ^ d;	c += 1859775393;	c += (t ^ b);	c = (c << 11) | (c >> 21);
	b += load(block + 13);	b += 1859775393;	b += (t ^ c);	b = (b << 15) | (b >> 17);
	a += load(block + 3);	t = b ^ c;	a += 1859775393;	a += (t ^ d);	a = (a << 3) | (a >> 29);
	d += load(block + 11);	d += 1859775393;	d += (t ^ a);	d = (d << 9) | (d >> 23);
	c += load(block + 7);	t = a ^ d;	c += 1859775393;	c += (t ^ b);	c = (c << 11) | (c >> 21);
	b += load(block + 15);	b += 1859775393;	b += (t ^ c);	b = (b << 15) | (b >> 17);

	// Save state
	store(state + 0, (load(state + 0) + a));
	store(state + 1, (load(state + 1) + b));
	store(state + 2, (load(state + 2) + c));
	store(state + 3, (load(state + 3) + d));
}
extern "C" void md4_block_sse2_x2(simd::Vec128u32 state[8], const simd::Vec128u32 block[32]) noexcept
{
	simd::Vec128u32 a0, a1, b0, b1, c0, c1, d0, d1, t0, t1, tt0, tt1;

	// Load state
	a0 = load(state + 0);	a1 = load(state + 1);
	b0 = load(state + 2);	b1 = load(state + 3);
	c0 = load(state + 4);	c1 = load(state + 5);
	d0 = load(state + 6);	d1 = load(state + 7);

	// Round 1
	for (int i = 0; i < 4; i++) {
		a0 += load(block + 0);		a1 += load(block + 1);		t0 = c0 ^ d0;		t1 = c1 ^ d1;		t0 &= b0;		t1 &= b1;		a0 += (d0 ^ t0);		a1 += (d1 ^ t1);		a0 = (a0 << 3) | (a0 >> 29);		a1 = (a1 << 3) | (a1 >> 29);
		d0 += load(block + 2);		d1 += load(block + 3);		t0 = b0 ^ c0;		t1 = b1 ^ c1;		t0 &= a0;		t1 &= a1;		d0 += (c0 ^ t0);		d1 += (c1 ^ t1);		d0 = (d0 << 7) | (d0 >> 25);		d1 = (d1 << 7) | (d1 >> 25);
		c0 += load(block + 4);		c1 += load(block + 5);		t0 = a0 ^ b0;		t1 = a1 ^ b1;		t0 &= d0;		t1 &= d1;		c0 += (b0 ^ t0);		c1 += (b1 ^ t1);		c0 = (c0 << 11) | (c0 >> 21);		c1 = (c1 << 11) | (c1 >> 21);
		b0 += load(block + 6);		b1 += load(block + 7);		t0 = d0 ^ a0;		t1 = d1 ^ a1;		t0 &= c0;		t1 &= c1;		b0 += (a0 ^ t0);		b1 += (a1 ^ t1);		b0 = (b0 << 19) | (b0 >> 13);		b1 = (b1 << 19) | (b1 >> 13);
		block += 8;
	}
	block -= 32;

	// Round 2
	for (int i = 0; i < 4; i++) {
		a0 += load(block + 0);		a1 += load(block + 1);		t0 = d0 | c0;		t1 = d1 | c1;		tt0 = c0 & d0;		tt1 = c1 & d1;		a0 += 1518500249;		a1 += 1518500249;		t0 &= b0;		t1 &= b1;		a0 += (t0 | tt0);		a1 += (t1 | tt1);		a0 = (a0 << 3) | (a0 >> 29);		a1 = (a1 << 3) | (a1 >> 29);
		d0 += load(block + 8);		d1 += load(block + 9);		t0 = c0 | b0;		t1 = c1 | b1;		tt0 = b0 & c0;		tt1 = b1 & c1;		d0 += 1518500249;		d1 += 1518500249;		t0 &= a0;		t1 &= a1;		d0 += (t0 | tt0);		d1 += (t1 | tt1);		d0 = (d0 << 5) | (d0 >> 27);		d1 = (d1 << 5) | (d1 >> 27);
		c0 += load(block + 16);		c1 += load(block + 17);		t0 = b0 | a0;		t1 = b1 | a1;		tt0 = a0 & b0;		tt1 = a1 & b1;		c0 += 1518500249;		c1 += 1518500249;		t0 &= d0;		t1 &= d1;		c0 += (t0 | tt0);		c1 += (t1 | tt1);		c0 = (c0 << 9) | (c0 >> 23);		c1 = (c1 << 9) | (c1 >> 23);
		b0 += load(block + 24);		b1 += load(block + 25);		t0 = a0 | d0;		t1 = a1 | d1;		tt0 = d0 & a0;		tt1 = d1 & a1;		b0 += 1518500249;		b1 += 1518500249;		t0 &= c0;		t1 &= c1;		b0 += (t0 | tt0);		b1 += (t1 | tt1);		b0 = (b0 << 13) | (b0 >> 19);		b1 = (b1 << 13) | (b1 >> 19);
		block += 2;
	}
	block -= 8;

	// Round 3

	a0 += load(block + 0);	a1 += load(block + 1);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	a0 += 1859775393;	a1 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);
	d0 += load(block + 16);	d1 += load(block + 17);	d0 += 1859775393;	d1 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);
	c0 += load(block + 8);	c1 += load(block + 9);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	c0 += 1859775393;	c1 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);
	b0 += load(block + 24);	b1 += load(block + 25);	b0 += 1859775393;	b1 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);
	a0 += load(block + 4);	a1 += load(block + 5);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	a0 += 1859775393;	a1 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);
	d0 += load(block + 20);	d1 += load(block + 21);	d0 += 1859775393;	d1 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);
	c0 += load(block + 12);	c1 += load(block + 13);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	c0 += 1859775393;	c1 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);
	b0 += load(block + 28);	b1 += load(block + 29);	b0 += 1859775393;	b1 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);
	a0 += load(block + 2);	a1 += load(block + 3);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	a0 += 1859775393;	a1 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);
	d0 += load(block + 18);	d1 += load(block + 19);	d0 += 1859775393;	d1 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);
	c0 += load(block + 10);	c1 += load(block + 11);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	c0 += 1859775393;	c1 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);
	b0 += load(block + 26);	b1 += load(block + 27);	b0 += 1859775393;	b1 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);
	a0 += load(block + 6);	a1 += load(block + 7);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	a0 += 1859775393;	a1 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);
	d0 += load(block + 22);	d1 += load(block + 23);	d0 += 1859775393;	d1 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);
	c0 += load(block + 14);	c1 += load(block + 15);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	c0 += 1859775393;	c1 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);
	b0 += load(block + 30);	b1 += load(block + 31);	b0 += 1859775393;	b1 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);

	// Save state
	store(state + 0, (load(state + 0) + a0));	store(state + 1, (load(state + 1) + a1));
	store(state + 2, (load(state + 2) + b0));	store(state + 3, (load(state + 3) + b1));
	store(state + 4, (load(state + 4) + c0));	store(state + 5, (load(state + 5) + c1));
	store(state + 6, (load(state + 6) + d0));	store(state + 7, (load(state + 7) + d1));
}
extern "C" void md4_block_sse2_x3(simd::Vec128u32 state[12], const simd::Vec128u32 block[48]) noexcept
{
	simd::Vec128u32 a0, a1, a2, b0, b1, b2, c0, c1, c2, d0, d1, d2, t0, t1, t2, tt0, tt1, tt2;

	// Load state
	a0 = load(state + 0);	a1 = load(state + 1);	a2 = load(state + 2);
	b0 = load(state + 3);	b1 = load(state + 4);	b2 = load(state + 5);
	c0 = load(state + 6);	c1 = load(state + 7);	c2 = load(state + 8);
	d0 = load(state + 9);	d1 = load(state + 10);	d2 = load(state + 11);

	// Round 1
	for (int i = 0; i < 4; i++) {
		a0 += load(block + 0);		a1 += load(block + 1);		a2 += load(block + 2);		t0 = c0 ^ d0;		t1 = c1 ^ d1;		t2 = c2 ^ d2;		t0 &= b0;		t1 &= b1;		t2 &= b2;		a0 += (d0 ^ t0);		a1 += (d1 ^ t1);		a2 += (d2 ^ t2);		a0 = (a0 << 3) | (a0 >> 29);		a1 = (a1 << 3) | (a1 >> 29);		a2 = (a2 << 3) | (a2 >> 29);
		d0 += load(block + 3);		d1 += load(block + 4);		d2 += load(block + 5);		t0 = b0 ^ c0;		t1 = b1 ^ c1;		t2 = b2 ^ c2;		t0 &= a0;		t1 &= a1;		t2 &= a2;		d0 += (c0 ^ t0);		d1 += (c1 ^ t1);		d2 += (c2 ^ t2);		d0 = (d0 << 7) | (d0 >> 25);		d1 = (d1 << 7) | (d1 >> 25);		d2 = (d2 << 7) | (d2 >> 25);
		c0 += load(block + 6);		c1 += load(block + 7);		c2 += load(block + 8);		t0 = a0 ^ b0;		t1 = a1 ^ b1;		t2 = a2 ^ b2;		t0 &= d0;		t1 &= d1;		t2 &= d2;		c0 += (b0 ^ t0);		c1 += (b1 ^ t1);		c2 += (b2 ^ t2);		c0 = (c0 << 11) | (c0 >> 21);		c1 = (c1 << 11) | (c1 >> 21);		c2 = (c2 << 11) | (c2 >> 21);
		b0 += load(block + 9);		b1 += load(block + 10);		b2 += load(block + 11);		t0 = d0 ^ a0;		t1 = d1 ^ a1;		t2 = d2 ^ a2;		t0 &= c0;		t1 &= c1;		t2 &= c2;		b0 += (a0 ^ t0);		b1 += (a1 ^ t1);		b2 += (a2 ^ t2);		b0 = (b0 << 19) | (b0 >> 13);		b1 = (b1 << 19) | (b1 >> 13);		b2 = (b2 << 19) | (b2 >> 13);
		block += 12;
	}
	block -= 48;

	// Round 2
	for (int i = 0; i < 4; i++) {
		a0 += load(block + 0);		a1 += load(block + 1);		a2 += load(block + 2);		t0 = d0 | c0;		t1 = d1 | c1;		t2 = d2 | c2;		tt0 = c0 & d0;		tt1 = c1 & d1;		tt2 = c2 & d2;		a0 += 1518500249;		a1 += 1518500249;		a2 += 1518500249;		t0 &= b0;		t1 &= b1;		t2 &= b2;		a0 += (t0 | tt0);		a1 += (t1 | tt1);		a2 += (t2 | tt2);		a0 = (a0 << 3) | (a0 >> 29);		a1 = (a1 << 3) | (a1 >> 29);		a2 = (a2 << 3) | (a2 >> 29);
		d0 += load(block + 12);		d1 += load(block + 13);		d2 += load(block + 14);		t0 = c0 | b0;		t1 = c1 | b1;		t2 = c2 | b2;		tt0 = b0 & c0;		tt1 = b1 & c1;		tt2 = b2 & c2;		d0 += 1518500249;		d1 += 1518500249;		d2 += 1518500249;		t0 &= a0;		t1 &= a1;		t2 &= a2;		d0 += (t0 | tt0);		d1 += (t1 | tt1);		d2 += (t2 | tt2);		d0 = (d0 << 5) | (d0 >> 27);		d1 = (d1 << 5) | (d1 >> 27);		d2 = (d2 << 5) | (d2 >> 27);
		c0 += load(block + 24);		c1 += load(block + 25);		c2 += load(block + 26);		t0 = b0 | a0;		t1 = b1 | a1;		t2 = b2 | a2;		tt0 = a0 & b0;		tt1 = a1 & b1;		tt2 = a2 & b2;		c0 += 1518500249;		c1 += 1518500249;		c2 += 1518500249;		t0 &= d0;		t1 &= d1;		t2 &= d2;		c0 += (t0 | tt0);		c1 += (t1 | tt1);		c2 += (t2 | tt2);		c0 = (c0 << 9) | (c0 >> 23);		c1 = (c1 << 9) | (c1 >> 23);		c2 = (c2 << 9) | (c2 >> 23);
		b0 += load(block + 36);		b1 += load(block + 37);		b2 += load(block + 38);		t0 = a0 | d0;		t1 = a1 | d1;		t2 = a2 | d2;		tt0 = d0 & a0;		tt1 = d1 & a1;		tt2 = d2 & a2;		b0 += 1518500249;		b1 += 1518500249;		b2 += 1518500249;		t0 &= c0;		t1 &= c1;		t2 &= c2;		b0 += (t0 | tt0);		b1 += (t1 | tt1);		b2 += (t2 | tt2);		b0 = (b0 << 13) | (b0 >> 19);		b1 = (b1 << 13) | (b1 >> 19);		b2 = (b2 << 13) | (b2 >> 19);
		block += 3;
	}
	block -= 12;

	// Round 3

	a0 += load(block + 0);	a1 += load(block + 1);	a2 += load(block + 2);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	a0 += 1859775393;	a1 += 1859775393;	a2 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a2 += (t2 ^ d2);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);	a2 = (a2 << 3) | (a2 >> 29);
	d0 += load(block + 24);	d1 += load(block + 25);	d2 += load(block + 26);	d0 += 1859775393;	d1 += 1859775393;	d2 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d2 += (t2 ^ a2);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);	d2 = (d2 << 9) | (d2 >> 23);
	c0 += load(block + 12);	c1 += load(block + 13);	c2 += load(block + 14);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	c0 += 1859775393;	c1 += 1859775393;	c2 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c2 += (t2 ^ b2);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);	c2 = (c2 << 11) | (c2 >> 21);
	b0 += load(block + 36);	b1 += load(block + 37);	b2 += load(block + 38);	b0 += 1859775393;	b1 += 1859775393;	b2 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b2 += (t2 ^ c2);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);	b2 = (b2 << 15) | (b2 >> 17);
	a0 += load(block + 6);	a1 += load(block + 7);	a2 += load(block + 8);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	a0 += 1859775393;	a1 += 1859775393;	a2 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a2 += (t2 ^ d2);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);	a2 = (a2 << 3) | (a2 >> 29);
	d0 += load(block + 30);	d1 += load(block + 31);	d2 += load(block + 32);	d0 += 1859775393;	d1 += 1859775393;	d2 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d2 += (t2 ^ a2);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);	d2 = (d2 << 9) | (d2 >> 23);
	c0 += load(block + 18);	c1 += load(block + 19);	c2 += load(block + 20);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	c0 += 1859775393;	c1 += 1859775393;	c2 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c2 += (t2 ^ b2);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);	c2 = (c2 << 11) | (c2 >> 21);
	b0 += load(block + 42);	b1 += load(block + 43);	b2 += load(block + 44);	b0 += 1859775393;	b1 += 1859775393;	b2 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b2 += (t2 ^ c2);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);	b2 = (b2 << 15) | (b2 >> 17);
	a0 += load(block + 3);	a1 += load(block + 4);	a2 += load(block + 5);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	a0 += 1859775393;	a1 += 1859775393;	a2 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a2 += (t2 ^ d2);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);	a2 = (a2 << 3) | (a2 >> 29);
	d0 += load(block + 27);	d1 += load(block + 28);	d2 += load(block + 29);	d0 += 1859775393;	d1 += 1859775393;	d2 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d2 += (t2 ^ a2);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);	d2 = (d2 << 9) | (d2 >> 23);
	c0 += load(block + 15);	c1 += load(block + 16);	c2 += load(block + 17);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	c0 += 1859775393;	c1 += 1859775393;	c2 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c2 += (t2 ^ b2);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);	c2 = (c2 << 11) | (c2 >> 21);
	b0 += load(block + 39);	b1 += load(block + 40);	b2 += load(block + 41);	b0 += 1859775393;	b1 += 1859775393;	b2 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b2 += (t2 ^ c2);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);	b2 = (b2 << 15) | (b2 >> 17);
	a0 += load(block + 9);	a1 += load(block + 10);	a2 += load(block + 11);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	a0 += 1859775393;	a1 += 1859775393;	a2 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a2 += (t2 ^ d2);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);	a2 = (a2 << 3) | (a2 >> 29);
	d0 += load(block + 33);	d1 += load(block + 34);	d2 += load(block + 35);	d0 += 1859775393;	d1 += 1859775393;	d2 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d2 += (t2 ^ a2);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);	d2 = (d2 << 9) | (d2 >> 23);
	c0 += load(block + 21);	c1 += load(block + 22);	c2 += load(block + 23);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	c0 += 1859775393;	c1 += 1859775393;	c2 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c2 += (t2 ^ b2);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);	c2 = (c2 << 11) | (c2 >> 21);
	b0 += load(block + 45);	b1 += load(block + 46);	b2 += load(block + 47);	b0 += 1859775393;	b1 += 1859775393;	b2 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b2 += (t2 ^ c2);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);	b2 = (b2 << 15) | (b2 >> 17);

	// Save state
	store(state + 0, (load(state + 0) + a0));	store(state + 1, (load(state + 1) + a1));	store(state + 2, (load(state + 2) + a2));
	store(state + 3, (load(state + 3) + b0));	store(state + 4, (load(state + 4) + b1));	store(state + 5, (load(state + 5) + b2));
	store(state + 6, (load(state + 6) + c0));	store(state + 7, (load(state + 7) + c1));	store(state + 8, (load(state + 8) + c2));
	store(state + 9, (load(state + 9) + d0));	store(state + 10, (load(state + 10) + d1));	store(state + 11, (load(state + 11) + d2));
}
extern "C" void md4_block_sse2_x4(simd::Vec128u32 state[16], const simd::Vec128u32 block[64]) noexcept
{
	simd::Vec128u32 a0, a1, a2, a3, b0, b1, b2, b3, c0, c1, c2, c3, d0, d1, d2, d3, t0, t1, t2, t3, tt0, tt1, tt2, tt3;

	// Load state
	a0 = load(state + 0);	a1 = load(state + 1);	a2 = load(state + 2);	a3 = load(state + 3);
	b0 = load(state + 4);	b1 = load(state + 5);	b2 = load(state + 6);	b3 = load(state + 7);
	c0 = load(state + 8);	c1 = load(state + 9);	c2 = load(state + 10);	c3 = load(state + 11);
	d0 = load(state + 12);	d1 = load(state + 13);	d2 = load(state + 14);	d3 = load(state + 15);

	// Round 1
	for (int i = 0; i < 4; i++) {
		a0 += load(block + 0);		a1 += load(block + 1);		a2 += load(block + 2);		a3 += load(block + 3);		t0 = c0 ^ d0;		t1 = c1 ^ d1;		t2 = c2 ^ d2;		t3 = c3 ^ d3;		t0 &= b0;		t1 &= b1;		t2 &= b2;		t3 &= b3;		a0 += (d0 ^ t0);		a1 += (d1 ^ t1);		a2 += (d2 ^ t2);		a3 += (d3 ^ t3);		a0 = (a0 << 3) | (a0 >> 29);		a1 = (a1 << 3) | (a1 >> 29);		a2 = (a2 << 3) | (a2 >> 29);		a3 = (a3 << 3) | (a3 >> 29);
		d0 += load(block + 4);		d1 += load(block + 5);		d2 += load(block + 6);		d3 += load(block + 7);		t0 = b0 ^ c0;		t1 = b1 ^ c1;		t2 = b2 ^ c2;		t3 = b3 ^ c3;		t0 &= a0;		t1 &= a1;		t2 &= a2;		t3 &= a3;		d0 += (c0 ^ t0);		d1 += (c1 ^ t1);		d2 += (c2 ^ t2);		d3 += (c3 ^ t3);		d0 = (d0 << 7) | (d0 >> 25);		d1 = (d1 << 7) | (d1 >> 25);		d2 = (d2 << 7) | (d2 >> 25);		d3 = (d3 << 7) | (d3 >> 25);
		c0 += load(block + 8);		c1 += load(block + 9);		c2 += load(block + 10);		c3 += load(block + 11);		t0 = a0 ^ b0;		t1 = a1 ^ b1;		t2 = a2 ^ b2;		t3 = a3 ^ b3;		t0 &= d0;		t1 &= d1;		t2 &= d2;		t3 &= d3;		c0 += (b0 ^ t0);		c1 += (b1 ^ t1);		c2 += (b2 ^ t2);		c3 += (b3 ^ t3);		c0 = (c0 << 11) | (c0 >> 21);		c1 = (c1 << 11) | (c1 >> 21);		c2 = (c2 << 11) | (c2 >> 21);		c3 = (c3 << 11) | (c3 >> 21);
		b0 += load(block + 12);		b1 += load(block + 13);		b2 += load(block + 14);		b3 += load(block + 15);		t0 = d0 ^ a0;		t1 = d1 ^ a1;		t2 = d2 ^ a2;		t3 = d3 ^ a3;		t0 &= c0;		t1 &= c1;		t2 &= c2;		t3 &= c3;		b0 += (a0 ^ t0);		b1 += (a1 ^ t1);		b2 += (a2 ^ t2);		b3 += (a3 ^ t3);		b0 = (b0 << 19) | (b0 >> 13);		b1 = (b1 << 19) | (b1 >> 13);		b2 = (b2 << 19) | (b2 >> 13);		b3 = (b3 << 19) | (b3 >> 13);
		block += 16;
	}
	block -= 64;

	// Round 2
	for (int i = 0; i < 4; i++) {
		a0 += load(block + 0);		a1 += load(block + 1);		a2 += load(block + 2);		a3 += load(block + 3);		t0 = d0 | c0;		t1 = d1 | c1;		t2 = d2 | c2;		t3 = d3 | c3;		tt0 = c0 & d0;		tt1 = c1 & d1;		tt2 = c2 & d2;		tt3 = c3 & d3;		a0 += 1518500249;		a1 += 1518500249;		a2 += 1518500249;		a3 += 1518500249;		t0 &= b0;		t1 &= b1;		t2 &= b2;		t3 &= b3;		a0 += (t0 | tt0);		a1 += (t1 | tt1);		a2 += (t2 | tt2);		a3 += (t3 | tt3);		a0 = (a0 << 3) | (a0 >> 29);		a1 = (a1 << 3) | (a1 >> 29);		a2 = (a2 << 3) | (a2 >> 29);		a3 = (a3 << 3) | (a3 >> 29);
		d0 += load(block + 16);		d1 += load(block + 17);		d2 += load(block + 18);		d3 += load(block + 19);		t0 = c0 | b0;		t1 = c1 | b1;		t2 = c2 | b2;		t3 = c3 | b3;		tt0 = b0 & c0;		tt1 = b1 & c1;		tt2 = b2 & c2;		tt3 = b3 & c3;		d0 += 1518500249;		d1 += 1518500249;		d2 += 1518500249;		d3 += 1518500249;		t0 &= a0;		t1 &= a1;		t2 &= a2;		t3 &= a3;		d0 += (t0 | tt0);		d1 += (t1 | tt1);		d2 += (t2 | tt2);		d3 += (t3 | tt3);		d0 = (d0 << 5) | (d0 >> 27);		d1 = (d1 << 5) | (d1 >> 27);		d2 = (d2 << 5) | (d2 >> 27);		d3 = (d3 << 5) | (d3 >> 27);
		c0 += load(block + 32);		c1 += load(block + 33);		c2 += load(block + 34);		c3 += load(block + 35);		t0 = b0 | a0;		t1 = b1 | a1;		t2 = b2 | a2;		t3 = b3 | a3;		tt0 = a0 & b0;		tt1 = a1 & b1;		tt2 = a2 & b2;		tt3 = a3 & b3;		c0 += 1518500249;		c1 += 1518500249;		c2 += 1518500249;		c3 += 1518500249;		t0 &= d0;		t1 &= d1;		t2 &= d2;		t3 &= d3;		c0 += (t0 | tt0);		c1 += (t1 | tt1);		c2 += (t2 | tt2);		c3 += (t3 | tt3);		c0 = (c0 << 9) | (c0 >> 23);		c1 = (c1 << 9) | (c1 >> 23);		c2 = (c2 << 9) | (c2 >> 23);		c3 = (c3 << 9) | (c3 >> 23);
		b0 += load(block + 48);		b1 += load(block + 49);		b2 += load(block + 50);		b3 += load(block + 51);		t0 = a0 | d0;		t1 = a1 | d1;		t2 = a2 | d2;		t3 = a3 | d3;		tt0 = d0 & a0;		tt1 = d1 & a1;		tt2 = d2 & a2;		tt3 = d3 & a3;		b0 += 1518500249;		b1 += 1518500249;		b2 += 1518500249;		b3 += 1518500249;		t0 &= c0;		t1 &= c1;		t2 &= c2;		t3 &= c3;		b0 += (t0 | tt0);		b1 += (t1 | tt1);		b2 += (t2 | tt2);		b3 += (t3 | tt3);		b0 = (b0 << 13) | (b0 >> 19);		b1 = (b1 << 13) | (b1 >> 19);		b2 = (b2 << 13) | (b2 >> 19);		b3 = (b3 << 13) | (b3 >> 19);
		block += 4;
	}
	block -= 16;

	// Round 3

	a0 += load(block + 0);	a1 += load(block + 1);	a2 += load(block + 2);	a3 += load(block + 3);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t3 = b3 ^ c3;	a0 += 1859775393;	a1 += 1859775393;	a2 += 1859775393;	a3 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a2 += (t2 ^ d2);	a3 += (t3 ^ d3);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);	a2 = (a2 << 3) | (a2 >> 29);	a3 = (a3 << 3) | (a3 >> 29);
	d0 += load(block + 32);	d1 += load(block + 33);	d2 += load(block + 34);	d3 += load(block + 35);	d0 += 1859775393;	d1 += 1859775393;	d2 += 1859775393;	d3 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d2 += (t2 ^ a2);	d3 += (t3 ^ a3);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);	d2 = (d2 << 9) | (d2 >> 23);	d3 = (d3 << 9) | (d3 >> 23);
	c0 += load(block + 16);	c1 += load(block + 17);	c2 += load(block + 18);	c3 += load(block + 19);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	t3 = a3 ^ d3;	c0 += 1859775393;	c1 += 1859775393;	c2 += 1859775393;	c3 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c2 += (t2 ^ b2);	c3 += (t3 ^ b3);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);	c2 = (c2 << 11) | (c2 >> 21);	c3 = (c3 << 11) | (c3 >> 21);
	b0 += load(block + 48);	b1 += load(block + 49);	b2 += load(block + 50);	b3 += load(block + 51);	b0 += 1859775393;	b1 += 1859775393;	b2 += 1859775393;	b3 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b2 += (t2 ^ c2);	b3 += (t3 ^ c3);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);	b2 = (b2 << 15) | (b2 >> 17);	b3 = (b3 << 15) | (b3 >> 17);
	a0 += load(block + 8);	a1 += load(block + 9);	a2 += load(block + 10);	a3 += load(block + 11);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t3 = b3 ^ c3;	a0 += 1859775393;	a1 += 1859775393;	a2 += 1859775393;	a3 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a2 += (t2 ^ d2);	a3 += (t3 ^ d3);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);	a2 = (a2 << 3) | (a2 >> 29);	a3 = (a3 << 3) | (a3 >> 29);
	d0 += load(block + 40);	d1 += load(block + 41);	d2 += load(block + 42);	d3 += load(block + 43);	d0 += 1859775393;	d1 += 1859775393;	d2 += 1859775393;	d3 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d2 += (t2 ^ a2);	d3 += (t3 ^ a3);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);	d2 = (d2 << 9) | (d2 >> 23);	d3 = (d3 << 9) | (d3 >> 23);
	c0 += load(block + 24);	c1 += load(block + 25);	c2 += load(block + 26);	c3 += load(block + 27);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	t3 = a3 ^ d3;	c0 += 1859775393;	c1 += 1859775393;	c2 += 1859775393;	c3 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c2 += (t2 ^ b2);	c3 += (t3 ^ b3);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);	c2 = (c2 << 11) | (c2 >> 21);	c3 = (c3 << 11) | (c3 >> 21);
	b0 += load(block + 56);	b1 += load(block + 57);	b2 += load(block + 58);	b3 += load(block + 59);	b0 += 1859775393;	b1 += 1859775393;	b2 += 1859775393;	b3 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b2 += (t2 ^ c2);	b3 += (t3 ^ c3);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);	b2 = (b2 << 15) | (b2 >> 17);	b3 = (b3 << 15) | (b3 >> 17);
	a0 += load(block + 4);	a1 += load(block + 5);	a2 += load(block + 6);	a3 += load(block + 7);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t3 = b3 ^ c3;	a0 += 1859775393;	a1 += 1859775393;	a2 += 1859775393;	a3 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a2 += (t2 ^ d2);	a3 += (t3 ^ d3);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);	a2 = (a2 << 3) | (a2 >> 29);	a3 = (a3 << 3) | (a3 >> 29);
	d0 += load(block + 36);	d1 += load(block + 37);	d2 += load(block + 38);	d3 += load(block + 39);	d0 += 1859775393;	d1 += 1859775393;	d2 += 1859775393;	d3 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d2 += (t2 ^ a2);	d3 += (t3 ^ a3);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);	d2 = (d2 << 9) | (d2 >> 23);	d3 = (d3 << 9) | (d3 >> 23);
	c0 += load(block + 20);	c1 += load(block + 21);	c2 += load(block + 22);	c3 += load(block + 23);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	t3 = a3 ^ d3;	c0 += 1859775393;	c1 += 1859775393;	c2 += 1859775393;	c3 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c2 += (t2 ^ b2);	c3 += (t3 ^ b3);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);	c2 = (c2 << 11) | (c2 >> 21);	c3 = (c3 << 11) | (c3 >> 21);
	b0 += load(block + 52);	b1 += load(block + 53);	b2 += load(block + 54);	b3 += load(block + 55);	b0 += 1859775393;	b1 += 1859775393;	b2 += 1859775393;	b3 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b2 += (t2 ^ c2);	b3 += (t3 ^ c3);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);	b2 = (b2 << 15) | (b2 >> 17);	b3 = (b3 << 15) | (b3 >> 17);
	a0 += load(block + 12);	a1 += load(block + 13);	a2 += load(block + 14);	a3 += load(block + 15);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t3 = b3 ^ c3;	a0 += 1859775393;	a1 += 1859775393;	a2 += 1859775393;	a3 += 1859775393;	a0 += (t0 ^ d0);	a1 += (t1 ^ d1);	a2 += (t2 ^ d2);	a3 += (t3 ^ d3);	a0 = (a0 << 3) | (a0 >> 29);	a1 = (a1 << 3) | (a1 >> 29);	a2 = (a2 << 3) | (a2 >> 29);	a3 = (a3 << 3) | (a3 >> 29);
	d0 += load(block + 44);	d1 += load(block + 45);	d2 += load(block + 46);	d3 += load(block + 47);	d0 += 1859775393;	d1 += 1859775393;	d2 += 1859775393;	d3 += 1859775393;	d0 += (t0 ^ a0);	d1 += (t1 ^ a1);	d2 += (t2 ^ a2);	d3 += (t3 ^ a3);	d0 = (d0 << 9) | (d0 >> 23);	d1 = (d1 << 9) | (d1 >> 23);	d2 = (d2 << 9) | (d2 >> 23);	d3 = (d3 << 9) | (d3 >> 23);
	c0 += load(block + 28);	c1 += load(block + 29);	c2 += load(block + 30);	c3 += load(block + 31);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	t3 = a3 ^ d3;	c0 += 1859775393;	c1 += 1859775393;	c2 += 1859775393;	c3 += 1859775393;	c0 += (t0 ^ b0);	c1 += (t1 ^ b1);	c2 += (t2 ^ b2);	c3 += (t3 ^ b3);	c0 = (c0 << 11) | (c0 >> 21);	c1 = (c1 << 11) | (c1 >> 21);	c2 = (c2 << 11) | (c2 >> 21);	c3 = (c3 << 11) | (c3 >> 21);
	b0 += load(block + 60);	b1 += load(block + 61);	b2 += load(block + 62);	b3 += load(block + 63);	b0 += 1859775393;	b1 += 1859775393;	b2 += 1859775393;	b3 += 1859775393;	b0 += (t0 ^ c0);	b1 += (t1 ^ c1);	b2 += (t2 ^ c2);	b3 += (t3 ^ c3);	b0 = (b0 << 15) | (b0 >> 17);	b1 = (b1 << 15) | (b1 >> 17);	b2 = (b2 << 15) | (b2 >> 17);	b3 = (b3 << 15) | (b3 >> 17);

	// Save state
	store(state + 0, (load(state + 0) + a0));	store(state + 1, (load(state + 1) + a1));	store(state + 2, (load(state + 2) + a2));	store(state + 3, (load(state + 3) + a3));
	store(state + 4, (load(state + 4) + b0));	store(state + 5, (load(state + 5) + b1));	store(state + 6, (load(state + 6) + b2));	store(state + 7, (load(state + 7) + b3));
	store(state + 8, (load(state + 8) + c0));	store(state + 9, (load(state + 9) + c1));	store(state + 10, (load(state + 10) + c2));	store(state + 11, (load(state + 11) + c3));
	store(state + 12, (load(state + 12) + d0));	store(state + 13, (load(state + 13) + d1));	store(state + 14, (load(state + 14) + d2));	store(state + 15, (load(state + 15) + d3));
}
