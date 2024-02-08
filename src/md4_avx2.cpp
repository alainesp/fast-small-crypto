//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MD4 Message-Digest Algorithm
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#define SimdScalarType uint32_t
#include "simd.hpp"
using namespace simd;

//// <summary>
//// MD4 compress block
//// </summary>
//// <param name="state">The md4 state</param>
//// <param name="block">The message to compress</param>
extern "C" void md4_block_avx2_x3(simd::Vec256u32 state[12], const simd::Vec256u32 block[48]) noexcept
{
	simd::Vec256u32 a0, a1, a2, c0, c1, c2, d0, d1, d2, b0, b1, b2, t0, t1, t2, tt0, tt1, tt2;

	// Load state
	a0 = load(state +  0);	a1 = load(state +  1);	a2 = load(state +  2);
	c0 = load(state +  6);	c1 = load(state +  7);	c2 = load(state +  8);
	d0 = load(state +  9);	d1 = load(state + 10);	d2 = load(state + 11);
	b0 = load(state +  3);	b1 = load(state +  4);	b2 = load(state +  5);

	// Round 1
	for (int i = 0; i < 4; i++) {
		a0 += load(block +  0);		a1 += load(block +  1);		a2 += load(block +  2);		t0 = c0 ^ d0;		t1 = c1 ^ d1;		t2 = c2 ^ d2;		t0 &= b0;		t1 &= b1;		t2 &= b2;		t0 ^= d0;		t1 ^= d1;		t2 ^= d2;		a0 += t0;		a1 += t1;		a2 += t2;		t0 = a0 <<  3;		t1 = a1 <<  3;		t2 = a2 <<  3;		a0 >>= 29;		a1 >>= 29;		a2 >>= 29;		a0 |= t0;		a1 |= t1;		a2 |= t2;
		d0 += load(block +  3);		d1 += load(block +  4);		d2 += load(block +  5);		t0 = b0 ^ c0;		t1 = b1 ^ c1;		t2 = b2 ^ c2;		t0 &= a0;		t1 &= a1;		t2 &= a2;		t0 ^= c0;		t1 ^= c1;		t2 ^= c2;		d0 += t0;		d1 += t1;		d2 += t2;		t0 = d0 <<  7;		t1 = d1 <<  7;		t2 = d2 <<  7;		d0 >>= 25;		d1 >>= 25;		d2 >>= 25;		d0 |= t0;		d1 |= t1;		d2 |= t2;
		c0 += load(block +  6);		c1 += load(block +  7);		c2 += load(block +  8);		t0 = a0 ^ b0;		t1 = a1 ^ b1;		t2 = a2 ^ b2;		t0 &= d0;		t1 &= d1;		t2 &= d2;		t0 ^= b0;		t1 ^= b1;		t2 ^= b2;		c0 += t0;		c1 += t1;		c2 += t2;		t0 = c0 << 11;		t1 = c1 << 11;		t2 = c2 << 11;		c0 >>= 21;		c1 >>= 21;		c2 >>= 21;		c0 |= t0;		c1 |= t1;		c2 |= t2;
		b0 += load(block +  9);		b1 += load(block + 10);		b2 += load(block + 11);		t0 = d0 ^ a0;		t1 = d1 ^ a1;		t2 = d2 ^ a2;		t0 &= c0;		t1 &= c1;		t2 &= c2;		t0 ^= a0;		t1 ^= a1;		t2 ^= a2;		b0 += t0;		b1 += t1;		b2 += t2;		t0 = b0 << 19;		t1 = b1 << 19;		t2 = b2 << 19;		b0 >>= 13;		b1 >>= 13;		b2 >>= 13;		b0 |= t0;		b1 |= t1;		b2 |= t2;
		block += 12;
	}
	block -= 48;

	// Round 2
	for (int i = 0; i < 4; i++) {
		a0 += load(block +  0);		a1 += load(block +  1);		a2 += load(block +  2);		t0 = d0 | c0;		t1 = d1 | c1;		t2 = d2 | c2;		tt0 = c0 & d0;		tt1 = c1 & d1;		tt2 = c2 & d2;		a0 += UINT32_C(0x5a827999);		a1 += UINT32_C(0x5a827999);		a2 += UINT32_C(0x5a827999);		t0 &= b0;		t1 &= b1;		t2 &= b2;		t0 |= tt0;		t1 |= tt1;		t2 |= tt2;		a0 += t0;		a1 += t1;		a2 += t2;		t0 = a0 <<  3;		t1 = a1 <<  3;		t2 = a2 <<  3;		a0 >>= 29;		a1 >>= 29;		a2 >>= 29;		a0 |= t0;		a1 |= t1;		a2 |= t2;
		d0 += load(block + 12);		d1 += load(block + 13);		d2 += load(block + 14);		t0 = c0 | b0;		t1 = c1 | b1;		t2 = c2 | b2;		tt0 = b0 & c0;		tt1 = b1 & c1;		tt2 = b2 & c2;		d0 += UINT32_C(0x5a827999);		d1 += UINT32_C(0x5a827999);		d2 += UINT32_C(0x5a827999);		t0 &= a0;		t1 &= a1;		t2 &= a2;		t0 |= tt0;		t1 |= tt1;		t2 |= tt2;		d0 += t0;		d1 += t1;		d2 += t2;		t0 = d0 <<  5;		t1 = d1 <<  5;		t2 = d2 <<  5;		d0 >>= 27;		d1 >>= 27;		d2 >>= 27;		d0 |= t0;		d1 |= t1;		d2 |= t2;
		c0 += load(block + 24);		c1 += load(block + 25);		c2 += load(block + 26);		t0 = b0 | a0;		t1 = b1 | a1;		t2 = b2 | a2;		tt0 = a0 & b0;		tt1 = a1 & b1;		tt2 = a2 & b2;		c0 += UINT32_C(0x5a827999);		c1 += UINT32_C(0x5a827999);		c2 += UINT32_C(0x5a827999);		t0 &= d0;		t1 &= d1;		t2 &= d2;		t0 |= tt0;		t1 |= tt1;		t2 |= tt2;		c0 += t0;		c1 += t1;		c2 += t2;		t0 = c0 <<  9;		t1 = c1 <<  9;		t2 = c2 <<  9;		c0 >>= 23;		c1 >>= 23;		c2 >>= 23;		c0 |= t0;		c1 |= t1;		c2 |= t2;
		b0 += load(block + 36);		b1 += load(block + 37);		b2 += load(block + 38);		t0 = a0 | d0;		t1 = a1 | d1;		t2 = a2 | d2;		tt0 = d0 & a0;		tt1 = d1 & a1;		tt2 = d2 & a2;		b0 += UINT32_C(0x5a827999);		b1 += UINT32_C(0x5a827999);		b2 += UINT32_C(0x5a827999);		t0 &= c0;		t1 &= c1;		t2 &= c2;		t0 |= tt0;		t1 |= tt1;		t2 |= tt2;		b0 += t0;		b1 += t1;		b2 += t2;		t0 = b0 << 13;		t1 = b1 << 13;		t2 = b2 << 13;		b0 >>= 19;		b1 >>= 19;		b2 >>= 19;		b0 |= t0;		b1 |= t1;		b2 |= t2;
		block +=  3;
	}
	block -= 12;

	// Round 3
	a0 += load(block +  0);	a1 += load(block +  1);	a2 += load(block +  2);	t0 = d0 ^ c0;	t1 = d1 ^ c1;	t2 = d2 ^ c2;	a0 += UINT32_C(0x6ed9eba1);	a1 += UINT32_C(0x6ed9eba1);	a2 += UINT32_C(0x6ed9eba1);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  3;	t1 = a1 <<  3;	t2 = a2 <<  3;	a0 >>= 29;	a1 >>= 29;	a2 >>= 29;	a0 |= t0;	a1 |= t1;	a2 |= t2;
	d0 += load(block + 24);	d1 += load(block + 25);	d2 += load(block + 26);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	d0 += UINT32_C(0x6ed9eba1);	d1 += UINT32_C(0x6ed9eba1);	d2 += UINT32_C(0x6ed9eba1);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 <<  9;	t1 = d1 <<  9;	t2 = d2 <<  9;	d0 >>= 23;	d1 >>= 23;	d2 >>= 23;	d0 |= t0;	d1 |= t1;	d2 |= t2;
	c0 += load(block + 12);	c1 += load(block + 13);	c2 += load(block + 14);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	c0 += UINT32_C(0x6ed9eba1);	c1 += UINT32_C(0x6ed9eba1);	c2 += UINT32_C(0x6ed9eba1);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 11;	t1 = c1 << 11;	t2 = c2 << 11;	c0 >>= 21;	c1 >>= 21;	c2 >>= 21;	c0 |= t0;	c1 |= t1;	c2 |= t2;
	b0 += load(block + 36);	b1 += load(block + 37);	b2 += load(block + 38);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	b0 += UINT32_C(0x6ed9eba1);	b1 += UINT32_C(0x6ed9eba1);	b2 += UINT32_C(0x6ed9eba1);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 15;	t1 = b1 << 15;	t2 = b2 << 15;	b0 >>= 17;	b1 >>= 17;	b2 >>= 17;	b0 |= t0;	b1 |= t1;	b2 |= t2;
	a0 += load(block +  6);	a1 += load(block +  7);	a2 += load(block +  8);	t0 = d0 ^ c0;	t1 = d1 ^ c1;	t2 = d2 ^ c2;	a0 += UINT32_C(0x6ed9eba1);	a1 += UINT32_C(0x6ed9eba1);	a2 += UINT32_C(0x6ed9eba1);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  3;	t1 = a1 <<  3;	t2 = a2 <<  3;	a0 >>= 29;	a1 >>= 29;	a2 >>= 29;	a0 |= t0;	a1 |= t1;	a2 |= t2;
	d0 += load(block + 30);	d1 += load(block + 31);	d2 += load(block + 32);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	d0 += UINT32_C(0x6ed9eba1);	d1 += UINT32_C(0x6ed9eba1);	d2 += UINT32_C(0x6ed9eba1);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 <<  9;	t1 = d1 <<  9;	t2 = d2 <<  9;	d0 >>= 23;	d1 >>= 23;	d2 >>= 23;	d0 |= t0;	d1 |= t1;	d2 |= t2;
	c0 += load(block + 18);	c1 += load(block + 19);	c2 += load(block + 20);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	c0 += UINT32_C(0x6ed9eba1);	c1 += UINT32_C(0x6ed9eba1);	c2 += UINT32_C(0x6ed9eba1);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 11;	t1 = c1 << 11;	t2 = c2 << 11;	c0 >>= 21;	c1 >>= 21;	c2 >>= 21;	c0 |= t0;	c1 |= t1;	c2 |= t2;
	b0 += load(block + 42);	b1 += load(block + 43);	b2 += load(block + 44);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	b0 += UINT32_C(0x6ed9eba1);	b1 += UINT32_C(0x6ed9eba1);	b2 += UINT32_C(0x6ed9eba1);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 15;	t1 = b1 << 15;	t2 = b2 << 15;	b0 >>= 17;	b1 >>= 17;	b2 >>= 17;	b0 |= t0;	b1 |= t1;	b2 |= t2;
	a0 += load(block +  3);	a1 += load(block +  4);	a2 += load(block +  5);	t0 = d0 ^ c0;	t1 = d1 ^ c1;	t2 = d2 ^ c2;	a0 += UINT32_C(0x6ed9eba1);	a1 += UINT32_C(0x6ed9eba1);	a2 += UINT32_C(0x6ed9eba1);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  3;	t1 = a1 <<  3;	t2 = a2 <<  3;	a0 >>= 29;	a1 >>= 29;	a2 >>= 29;	a0 |= t0;	a1 |= t1;	a2 |= t2;
	d0 += load(block + 27);	d1 += load(block + 28);	d2 += load(block + 29);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	d0 += UINT32_C(0x6ed9eba1);	d1 += UINT32_C(0x6ed9eba1);	d2 += UINT32_C(0x6ed9eba1);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 <<  9;	t1 = d1 <<  9;	t2 = d2 <<  9;	d0 >>= 23;	d1 >>= 23;	d2 >>= 23;	d0 |= t0;	d1 |= t1;	d2 |= t2;
	c0 += load(block + 15);	c1 += load(block + 16);	c2 += load(block + 17);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	c0 += UINT32_C(0x6ed9eba1);	c1 += UINT32_C(0x6ed9eba1);	c2 += UINT32_C(0x6ed9eba1);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 11;	t1 = c1 << 11;	t2 = c2 << 11;	c0 >>= 21;	c1 >>= 21;	c2 >>= 21;	c0 |= t0;	c1 |= t1;	c2 |= t2;
	b0 += load(block + 39);	b1 += load(block + 40);	b2 += load(block + 41);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	b0 += UINT32_C(0x6ed9eba1);	b1 += UINT32_C(0x6ed9eba1);	b2 += UINT32_C(0x6ed9eba1);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 15;	t1 = b1 << 15;	t2 = b2 << 15;	b0 >>= 17;	b1 >>= 17;	b2 >>= 17;	b0 |= t0;	b1 |= t1;	b2 |= t2;
	a0 += load(block +  9);	a1 += load(block + 10);	a2 += load(block + 11);	t0 = d0 ^ c0;	t1 = d1 ^ c1;	t2 = d2 ^ c2;	a0 += UINT32_C(0x6ed9eba1);	a1 += UINT32_C(0x6ed9eba1);	a2 += UINT32_C(0x6ed9eba1);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  3;	t1 = a1 <<  3;	t2 = a2 <<  3;	a0 >>= 29;	a1 >>= 29;	a2 >>= 29;	a0 |= t0;	a1 |= t1;	a2 |= t2;
	d0 += load(block + 33);	d1 += load(block + 34);	d2 += load(block + 35);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	d0 += UINT32_C(0x6ed9eba1);	d1 += UINT32_C(0x6ed9eba1);	d2 += UINT32_C(0x6ed9eba1);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 <<  9;	t1 = d1 <<  9;	t2 = d2 <<  9;	d0 >>= 23;	d1 >>= 23;	d2 >>= 23;	d0 |= t0;	d1 |= t1;	d2 |= t2;
	c0 += load(block + 21);	c1 += load(block + 22);	c2 += load(block + 23);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	c0 += UINT32_C(0x6ed9eba1);	c1 += UINT32_C(0x6ed9eba1);	c2 += UINT32_C(0x6ed9eba1);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 11;	t1 = c1 << 11;	t2 = c2 << 11;	c0 >>= 21;	c1 >>= 21;	c2 >>= 21;	c0 |= t0;	c1 |= t1;	c2 |= t2;
	b0 += load(block + 45);	b1 += load(block + 46);	b2 += load(block + 47);	t0 = a0 ^ d0;	t1 = a1 ^ d1;	t2 = a2 ^ d2;	b0 += UINT32_C(0x6ed9eba1);	b1 += UINT32_C(0x6ed9eba1);	b2 += UINT32_C(0x6ed9eba1);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 15;	t1 = b1 << 15;	t2 = b2 << 15;	b0 >>= 17;	b1 >>= 17;	b2 >>= 17;	b0 |= t0;	b1 |= t1;	b2 |= t2;

	// Save state
	store(state +  0, load(state +  0) + a0);	store(state +  1, load(state +  1) + a1);	store(state +  2, load(state +  2) + a2);
	store(state +  9, load(state +  9) + d0);	store(state + 10, load(state + 10) + d1);	store(state + 11, load(state + 11) + d2);
	store(state +  6, load(state +  6) + c0);	store(state +  7, load(state +  7) + c1);	store(state +  8, load(state +  8) + c2);
	store(state +  3, load(state +  3) + b0);	store(state +  4, load(state +  4) + b1);	store(state +  5, load(state +  5) + b2);
}

