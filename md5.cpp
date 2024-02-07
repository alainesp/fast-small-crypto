//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MD5 Message-Digest Algorithm
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#define SimdScalarType uint32_t
#include "simd.hpp"
using namespace simd;

/// <summary>
/// MD5 compress block
/// </summary>
/// <param name="state">The md5 state</param>
/// <param name="block">The message to compress</param>
extern "C" void md5_block_plain_c(uint32_t state[4], const uint32_t block[16]) noexcept
{
	uint32_t a, c, d, b, t;

	// Load state
	a = state[0];
	c = state[2];
	d = state[3];
	b = state[1];

	// Round 1
	a += block[0];	t = c ^ d;	t &= b;	a += UINT32_C(0xd76aa478);	t ^= d;	a += t;	a = rotl(a,  7);	a += b;
	d += block[1];	t = b ^ c;	t &= a;	d += UINT32_C(0xe8c7b756);	t ^= c;	d += t;	d = rotl(d, 12);	d += a;
	c += block[2];	t = a ^ b;	t &= d;	c += UINT32_C(0x242070db);	t ^= b;	c += t;	c = rotl(c, 17);	c += d;
	b += block[3];	t = d ^ a;	t &= c;	b += UINT32_C(0xc1bdceee);	t ^= a;	b += t;	b = rotl(b, 22);	b += c;
	a += block[4];	t = c ^ d;	t &= b;	a += UINT32_C(0xf57c0faf);	t ^= d;	a += t;	a = rotl(a,  7);	a += b;
	d += block[5];	t = b ^ c;	t &= a;	d += UINT32_C(0x4787c62a);	t ^= c;	d += t;	d = rotl(d, 12);	d += a;
	c += block[6];	t = a ^ b;	t &= d;	c += UINT32_C(0xa8304613);	t ^= b;	c += t;	c = rotl(c, 17);	c += d;
	b += block[7];	t = d ^ a;	t &= c;	b += UINT32_C(0xfd469501);	t ^= a;	b += t;	b = rotl(b, 22);	b += c;
	a += block[8];	t = c ^ d;	t &= b;	a += UINT32_C(0x698098d8);	t ^= d;	a += t;	a = rotl(a,  7);	a += b;
	d += block[9];	t = b ^ c;	t &= a;	d += UINT32_C(0x8b44f7af);	t ^= c;	d += t;	d = rotl(d, 12);	d += a;
	c += block[10];	t = a ^ b;	t &= d;	c += UINT32_C(0xffff5bb1);	t ^= b;	c += t;	c = rotl(c, 17);	c += d;
	b += block[11];	t = d ^ a;	t &= c;	b += UINT32_C(0x895cd7be);	t ^= a;	b += t;	b = rotl(b, 22);	b += c;
	a += block[12];	t = c ^ d;	t &= b;	a += UINT32_C(0x6b901122);	t ^= d;	a += t;	a = rotl(a,  7);	a += b;
	d += block[13];	t = b ^ c;	t &= a;	d += UINT32_C(0xfd987193);	t ^= c;	d += t;	d = rotl(d, 12);	d += a;
	c += block[14];	t = a ^ b;	t &= d;	c += UINT32_C(0xa679438e);	t ^= b;	c += t;	c = rotl(c, 17);	c += d;
	b += block[15];	t = d ^ a;	t &= c;	b += UINT32_C(0x49b40821);	t ^= a;	b += t;	b = rotl(b, 22);	b += c;

	// Round 2
	a += block[1];	t = b ^ c;	t &= d;	a += UINT32_C(0xf61e2562);	t ^= c;	a += t;	a = rotl(a,  5);	a += b;
	d += block[6];	t = a ^ b;	t &= c;	d += UINT32_C(0xc040b340);	t ^= b;	d += t;	d = rotl(d,  9);	d += a;
	c += block[11];	t = d ^ a;	t &= b;	c += UINT32_C(0x265e5a51);	t ^= a;	c += t;	c = rotl(c, 14);	c += d;
	b += block[0];	t = c ^ d;	t &= a;	b += UINT32_C(0xe9b6c7aa);	t ^= d;	b += t;	b = rotl(b, 20);	b += c;
	a += block[5];	t = b ^ c;	t &= d;	a += UINT32_C(0xd62f105d);	t ^= c;	a += t;	a = rotl(a,  5);	a += b;
	d += block[10];	t = a ^ b;	t &= c;	d += UINT32_C(0x2441453);	t ^= b;	d += t;	d = rotl(d,  9);	d += a;
	c += block[15];	t = d ^ a;	t &= b;	c += UINT32_C(0xd8a1e681);	t ^= a;	c += t;	c = rotl(c, 14);	c += d;
	b += block[4];	t = c ^ d;	t &= a;	b += UINT32_C(0xe7d3fbc8);	t ^= d;	b += t;	b = rotl(b, 20);	b += c;
	a += block[9];	t = b ^ c;	t &= d;	a += UINT32_C(0x21e1cde6);	t ^= c;	a += t;	a = rotl(a,  5);	a += b;
	d += block[14];	t = a ^ b;	t &= c;	d += UINT32_C(0xc33707d6);	t ^= b;	d += t;	d = rotl(d,  9);	d += a;
	c += block[3];	t = d ^ a;	t &= b;	c += UINT32_C(0xf4d50d87);	t ^= a;	c += t;	c = rotl(c, 14);	c += d;
	b += block[8];	t = c ^ d;	t &= a;	b += UINT32_C(0x455a14ed);	t ^= d;	b += t;	b = rotl(b, 20);	b += c;
	a += block[13];	t = b ^ c;	t &= d;	a += UINT32_C(0xa9e3e905);	t ^= c;	a += t;	a = rotl(a,  5);	a += b;
	d += block[2];	t = a ^ b;	t &= c;	d += UINT32_C(0xfcefa3f8);	t ^= b;	d += t;	d = rotl(d,  9);	d += a;
	c += block[7];	t = d ^ a;	t &= b;	c += UINT32_C(0x676f02d9);	t ^= a;	c += t;	c = rotl(c, 14);	c += d;
	b += block[12];	t = c ^ d;	t &= a;	b += UINT32_C(0x8d2a4c8a);	t ^= d;	b += t;	b = rotl(b, 20);	b += c;

	// Round 3
	a += block[5];	t = c ^ d;	a += UINT32_C(0xfffa3942);	t ^= b;	a += t;	a = rotl(a,  4);	a += b;
	d += block[8];	t = b ^ c;	d += UINT32_C(0x8771f681);	t ^= a;	d += t;	d = rotl(d, 11);	d += a;
	c += block[11];	t = a ^ b;	c += UINT32_C(0x6d9d6122);	t ^= d;	c += t;	c = rotl(c, 16);	c += d;
	b += block[14];	t = d ^ a;	b += UINT32_C(0xfde5380c);	t ^= c;	b += t;	b = rotl(b, 23);	b += c;
	a += block[1];	t = c ^ d;	a += UINT32_C(0xa4beea44);	t ^= b;	a += t;	a = rotl(a,  4);	a += b;
	d += block[4];	t = b ^ c;	d += UINT32_C(0x4bdecfa9);	t ^= a;	d += t;	d = rotl(d, 11);	d += a;
	c += block[7];	t = a ^ b;	c += UINT32_C(0xf6bb4b60);	t ^= d;	c += t;	c = rotl(c, 16);	c += d;
	b += block[10];	t = d ^ a;	b += UINT32_C(0xbebfbc70);	t ^= c;	b += t;	b = rotl(b, 23);	b += c;
	a += block[13];	t = c ^ d;	a += UINT32_C(0x289b7ec6);	t ^= b;	a += t;	a = rotl(a,  4);	a += b;
	d += block[0];	t = b ^ c;	d += UINT32_C(0xeaa127fa);	t ^= a;	d += t;	d = rotl(d, 11);	d += a;
	c += block[3];	t = a ^ b;	c += UINT32_C(0xd4ef3085);	t ^= d;	c += t;	c = rotl(c, 16);	c += d;
	b += block[6];	t = d ^ a;	b += UINT32_C(0x4881d05);	t ^= c;	b += t;	b = rotl(b, 23);	b += c;
	a += block[9];	t = c ^ d;	a += UINT32_C(0xd9d4d039);	t ^= b;	a += t;	a = rotl(a,  4);	a += b;
	d += block[12];	t = b ^ c;	d += UINT32_C(0xe6db99e5);	t ^= a;	d += t;	d = rotl(d, 11);	d += a;
	c += block[15];	t = a ^ b;	c += UINT32_C(0x1fa27cf8);	t ^= d;	c += t;	c = rotl(c, 16);	c += d;
	b += block[2];	t = d ^ a;	b += UINT32_C(0xc4ac5665);	t ^= c;	b += t;	b = rotl(b, 23);	b += c;

	// Round 4
	a += block[0];	t = ~(d);	a += UINT32_C(0xf4292244);	t |= b;	t ^= c;	a += t;	a = rotl(a,  6);	a += b;
	d += block[7];	t = ~(c);	d += UINT32_C(0x432aff97);	t |= a;	t ^= b;	d += t;	d = rotl(d, 10);	d += a;
	c += block[14];	t = ~(b);	c += UINT32_C(0xab9423a7);	t |= d;	t ^= a;	c += t;	c = rotl(c, 15);	c += d;
	b += block[5];	t = ~(a);	b += UINT32_C(0xfc93a039);	t |= c;	t ^= d;	b += t;	b = rotl(b, 21);	b += c;
	a += block[12];	t = ~(d);	a += UINT32_C(0x655b59c3);	t |= b;	t ^= c;	a += t;	a = rotl(a,  6);	a += b;
	d += block[3];	t = ~(c);	d += UINT32_C(0x8f0ccc92);	t |= a;	t ^= b;	d += t;	d = rotl(d, 10);	d += a;
	c += block[10];	t = ~(b);	c += UINT32_C(0xffeff47d);	t |= d;	t ^= a;	c += t;	c = rotl(c, 15);	c += d;
	b += block[1];	t = ~(a);	b += UINT32_C(0x85845dd1);	t |= c;	t ^= d;	b += t;	b = rotl(b, 21);	b += c;
	a += block[8];	t = ~(d);	a += UINT32_C(0x6fa87e4f);	t |= b;	t ^= c;	a += t;	a = rotl(a,  6);	a += b;
	d += block[15];	t = ~(c);	d += UINT32_C(0xfe2ce6e0);	t |= a;	t ^= b;	d += t;	d = rotl(d, 10);	d += a;
	c += block[6];	t = ~(b);	c += UINT32_C(0xa3014314);	t |= d;	t ^= a;	c += t;	c = rotl(c, 15);	c += d;
	b += block[13];	t = ~(a);	b += UINT32_C(0x4e0811a1);	t |= c;	t ^= d;	b += t;	b = rotl(b, 21);	b += c;
	a += block[4];	t = ~(d);	a += UINT32_C(0xf7537e82);	t |= b;	t ^= c;	a += t;	a = rotl(a,  6);	a += b;
	d += block[11];	t = ~(c);	d += UINT32_C(0xbd3af235);	t |= a;	t ^= b;	d += t;	d = rotl(d, 10);	d += a;
	c += block[2];	t = ~(b);	c += UINT32_C(0x2ad7d2bb);	t |= d;	t ^= a;	c += t;	c = rotl(c, 15);	c += d;
	b += block[9];	t = ~(a);	b += UINT32_C(0xeb86d391);	t |= c;	t ^= d;	b += t;	b = rotl(b, 21);	b += c;

	// Save state
	state[0] += a;
	state[3] += d;
	state[2] += c;
	state[1] += b;
}

/// <summary>
/// MD5 compress block
/// </summary>
/// <param name="state">The md5 state</param>
/// <param name="block">The message to compress</param>
extern "C" void md5_block_sse2_x3(simd::Vec128u32 state[12], const simd::Vec128u32 block[48]) noexcept
{
	simd::Vec128u32 a0, a1, a2, c0, c1, c2, d0, d1, d2, b0, b1, b2, t0, t1, t2;

	// Load state
	a0 = load(state +  0);	a1 = load(state +  1);	a2 = load(state +  2);
	c0 = load(state +  6);	c1 = load(state +  7);	c2 = load(state +  8);
	d0 = load(state +  9);	d1 = load(state + 10);	d2 = load(state + 11);
	b0 = load(state +  3);	b1 = load(state +  4);	b2 = load(state +  5);

	// Round 1
	a0 += load(block +  0);	a1 += load(block +  1);	a2 += load(block +  2);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	t0 &= b0;	t1 &= b1;	t2 &= b2;	a0 += UINT32_C(0xd76aa478);	a1 += UINT32_C(0xd76aa478);	a2 += UINT32_C(0xd76aa478);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  7;	t1 = a1 <<  7;	t2 = a2 <<  7;	a0 >>= 25;	a1 >>= 25;	a2 >>= 25;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block +  3);	d1 += load(block +  4);	d2 += load(block +  5);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t0 &= a0;	t1 &= a1;	t2 &= a2;	d0 += UINT32_C(0xe8c7b756);	d1 += UINT32_C(0xe8c7b756);	d2 += UINT32_C(0xe8c7b756);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 12;	t1 = d1 << 12;	t2 = d2 << 12;	d0 >>= 20;	d1 >>= 20;	d2 >>= 20;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block +  6);	c1 += load(block +  7);	c2 += load(block +  8);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	t0 &= d0;	t1 &= d1;	t2 &= d2;	c0 += UINT32_C(0x242070db);	c1 += UINT32_C(0x242070db);	c2 += UINT32_C(0x242070db);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 17;	t1 = c1 << 17;	t2 = c2 << 17;	c0 >>= 15;	c1 >>= 15;	c2 >>= 15;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block +  9);	b1 += load(block + 10);	b2 += load(block + 11);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	t0 &= c0;	t1 &= c1;	t2 &= c2;	b0 += UINT32_C(0xc1bdceee);	b1 += UINT32_C(0xc1bdceee);	b2 += UINT32_C(0xc1bdceee);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 22;	t1 = b1 << 22;	t2 = b2 << 22;	b0 >>= 10;	b1 >>= 10;	b2 >>= 10;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block + 12);	a1 += load(block + 13);	a2 += load(block + 14);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	t0 &= b0;	t1 &= b1;	t2 &= b2;	a0 += UINT32_C(0xf57c0faf);	a1 += UINT32_C(0xf57c0faf);	a2 += UINT32_C(0xf57c0faf);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  7;	t1 = a1 <<  7;	t2 = a2 <<  7;	a0 >>= 25;	a1 >>= 25;	a2 >>= 25;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 15);	d1 += load(block + 16);	d2 += load(block + 17);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t0 &= a0;	t1 &= a1;	t2 &= a2;	d0 += UINT32_C(0x4787c62a);	d1 += UINT32_C(0x4787c62a);	d2 += UINT32_C(0x4787c62a);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 12;	t1 = d1 << 12;	t2 = d2 << 12;	d0 >>= 20;	d1 >>= 20;	d2 >>= 20;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 18);	c1 += load(block + 19);	c2 += load(block + 20);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	t0 &= d0;	t1 &= d1;	t2 &= d2;	c0 += UINT32_C(0xa8304613);	c1 += UINT32_C(0xa8304613);	c2 += UINT32_C(0xa8304613);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 17;	t1 = c1 << 17;	t2 = c2 << 17;	c0 >>= 15;	c1 >>= 15;	c2 >>= 15;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 21);	b1 += load(block + 22);	b2 += load(block + 23);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	t0 &= c0;	t1 &= c1;	t2 &= c2;	b0 += UINT32_C(0xfd469501);	b1 += UINT32_C(0xfd469501);	b2 += UINT32_C(0xfd469501);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 22;	t1 = b1 << 22;	t2 = b2 << 22;	b0 >>= 10;	b1 >>= 10;	b2 >>= 10;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block + 24);	a1 += load(block + 25);	a2 += load(block + 26);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	t0 &= b0;	t1 &= b1;	t2 &= b2;	a0 += UINT32_C(0x698098d8);	a1 += UINT32_C(0x698098d8);	a2 += UINT32_C(0x698098d8);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  7;	t1 = a1 <<  7;	t2 = a2 <<  7;	a0 >>= 25;	a1 >>= 25;	a2 >>= 25;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 27);	d1 += load(block + 28);	d2 += load(block + 29);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t0 &= a0;	t1 &= a1;	t2 &= a2;	d0 += UINT32_C(0x8b44f7af);	d1 += UINT32_C(0x8b44f7af);	d2 += UINT32_C(0x8b44f7af);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 12;	t1 = d1 << 12;	t2 = d2 << 12;	d0 >>= 20;	d1 >>= 20;	d2 >>= 20;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 30);	c1 += load(block + 31);	c2 += load(block + 32);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	t0 &= d0;	t1 &= d1;	t2 &= d2;	c0 += UINT32_C(0xffff5bb1);	c1 += UINT32_C(0xffff5bb1);	c2 += UINT32_C(0xffff5bb1);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 17;	t1 = c1 << 17;	t2 = c2 << 17;	c0 >>= 15;	c1 >>= 15;	c2 >>= 15;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 33);	b1 += load(block + 34);	b2 += load(block + 35);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	t0 &= c0;	t1 &= c1;	t2 &= c2;	b0 += UINT32_C(0x895cd7be);	b1 += UINT32_C(0x895cd7be);	b2 += UINT32_C(0x895cd7be);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 22;	t1 = b1 << 22;	t2 = b2 << 22;	b0 >>= 10;	b1 >>= 10;	b2 >>= 10;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block + 36);	a1 += load(block + 37);	a2 += load(block + 38);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	t0 &= b0;	t1 &= b1;	t2 &= b2;	a0 += UINT32_C(0x6b901122);	a1 += UINT32_C(0x6b901122);	a2 += UINT32_C(0x6b901122);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  7;	t1 = a1 <<  7;	t2 = a2 <<  7;	a0 >>= 25;	a1 >>= 25;	a2 >>= 25;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 39);	d1 += load(block + 40);	d2 += load(block + 41);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t0 &= a0;	t1 &= a1;	t2 &= a2;	d0 += UINT32_C(0xfd987193);	d1 += UINT32_C(0xfd987193);	d2 += UINT32_C(0xfd987193);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 12;	t1 = d1 << 12;	t2 = d2 << 12;	d0 >>= 20;	d1 >>= 20;	d2 >>= 20;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 42);	c1 += load(block + 43);	c2 += load(block + 44);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	t0 &= d0;	t1 &= d1;	t2 &= d2;	c0 += UINT32_C(0xa679438e);	c1 += UINT32_C(0xa679438e);	c2 += UINT32_C(0xa679438e);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 17;	t1 = c1 << 17;	t2 = c2 << 17;	c0 >>= 15;	c1 >>= 15;	c2 >>= 15;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 45);	b1 += load(block + 46);	b2 += load(block + 47);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	t0 &= c0;	t1 &= c1;	t2 &= c2;	b0 += UINT32_C(0x49b40821);	b1 += UINT32_C(0x49b40821);	b2 += UINT32_C(0x49b40821);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 22;	t1 = b1 << 22;	t2 = b2 << 22;	b0 >>= 10;	b1 >>= 10;	b2 >>= 10;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;

	// Round 2
	a0 += load(block +  3);	a1 += load(block +  4);	a2 += load(block +  5);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t0 &= d0;	t1 &= d1;	t2 &= d2;	a0 += UINT32_C(0xf61e2562);	a1 += UINT32_C(0xf61e2562);	a2 += UINT32_C(0xf61e2562);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  5;	t1 = a1 <<  5;	t2 = a2 <<  5;	a0 >>= 27;	a1 >>= 27;	a2 >>= 27;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 18);	d1 += load(block + 19);	d2 += load(block + 20);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	t0 &= c0;	t1 &= c1;	t2 &= c2;	d0 += UINT32_C(0xc040b340);	d1 += UINT32_C(0xc040b340);	d2 += UINT32_C(0xc040b340);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 <<  9;	t1 = d1 <<  9;	t2 = d2 <<  9;	d0 >>= 23;	d1 >>= 23;	d2 >>= 23;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 33);	c1 += load(block + 34);	c2 += load(block + 35);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	t0 &= b0;	t1 &= b1;	t2 &= b2;	c0 += UINT32_C(0x265e5a51);	c1 += UINT32_C(0x265e5a51);	c2 += UINT32_C(0x265e5a51);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 14;	t1 = c1 << 14;	t2 = c2 << 14;	c0 >>= 18;	c1 >>= 18;	c2 >>= 18;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block +  0);	b1 += load(block +  1);	b2 += load(block +  2);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	t0 &= a0;	t1 &= a1;	t2 &= a2;	b0 += UINT32_C(0xe9b6c7aa);	b1 += UINT32_C(0xe9b6c7aa);	b2 += UINT32_C(0xe9b6c7aa);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 20;	t1 = b1 << 20;	t2 = b2 << 20;	b0 >>= 12;	b1 >>= 12;	b2 >>= 12;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block + 15);	a1 += load(block + 16);	a2 += load(block + 17);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t0 &= d0;	t1 &= d1;	t2 &= d2;	a0 += UINT32_C(0xd62f105d);	a1 += UINT32_C(0xd62f105d);	a2 += UINT32_C(0xd62f105d);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  5;	t1 = a1 <<  5;	t2 = a2 <<  5;	a0 >>= 27;	a1 >>= 27;	a2 >>= 27;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 30);	d1 += load(block + 31);	d2 += load(block + 32);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	t0 &= c0;	t1 &= c1;	t2 &= c2;	d0 += UINT32_C(0x2441453);	d1 += UINT32_C(0x2441453);	d2 += UINT32_C(0x2441453);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 <<  9;	t1 = d1 <<  9;	t2 = d2 <<  9;	d0 >>= 23;	d1 >>= 23;	d2 >>= 23;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 45);	c1 += load(block + 46);	c2 += load(block + 47);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	t0 &= b0;	t1 &= b1;	t2 &= b2;	c0 += UINT32_C(0xd8a1e681);	c1 += UINT32_C(0xd8a1e681);	c2 += UINT32_C(0xd8a1e681);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 14;	t1 = c1 << 14;	t2 = c2 << 14;	c0 >>= 18;	c1 >>= 18;	c2 >>= 18;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 12);	b1 += load(block + 13);	b2 += load(block + 14);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	t0 &= a0;	t1 &= a1;	t2 &= a2;	b0 += UINT32_C(0xe7d3fbc8);	b1 += UINT32_C(0xe7d3fbc8);	b2 += UINT32_C(0xe7d3fbc8);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 20;	t1 = b1 << 20;	t2 = b2 << 20;	b0 >>= 12;	b1 >>= 12;	b2 >>= 12;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block + 27);	a1 += load(block + 28);	a2 += load(block + 29);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t0 &= d0;	t1 &= d1;	t2 &= d2;	a0 += UINT32_C(0x21e1cde6);	a1 += UINT32_C(0x21e1cde6);	a2 += UINT32_C(0x21e1cde6);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  5;	t1 = a1 <<  5;	t2 = a2 <<  5;	a0 >>= 27;	a1 >>= 27;	a2 >>= 27;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 42);	d1 += load(block + 43);	d2 += load(block + 44);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	t0 &= c0;	t1 &= c1;	t2 &= c2;	d0 += UINT32_C(0xc33707d6);	d1 += UINT32_C(0xc33707d6);	d2 += UINT32_C(0xc33707d6);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 <<  9;	t1 = d1 <<  9;	t2 = d2 <<  9;	d0 >>= 23;	d1 >>= 23;	d2 >>= 23;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block +  9);	c1 += load(block + 10);	c2 += load(block + 11);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	t0 &= b0;	t1 &= b1;	t2 &= b2;	c0 += UINT32_C(0xf4d50d87);	c1 += UINT32_C(0xf4d50d87);	c2 += UINT32_C(0xf4d50d87);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 14;	t1 = c1 << 14;	t2 = c2 << 14;	c0 >>= 18;	c1 >>= 18;	c2 >>= 18;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 24);	b1 += load(block + 25);	b2 += load(block + 26);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	t0 &= a0;	t1 &= a1;	t2 &= a2;	b0 += UINT32_C(0x455a14ed);	b1 += UINT32_C(0x455a14ed);	b2 += UINT32_C(0x455a14ed);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 20;	t1 = b1 << 20;	t2 = b2 << 20;	b0 >>= 12;	b1 >>= 12;	b2 >>= 12;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block + 39);	a1 += load(block + 40);	a2 += load(block + 41);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	t0 &= d0;	t1 &= d1;	t2 &= d2;	a0 += UINT32_C(0xa9e3e905);	a1 += UINT32_C(0xa9e3e905);	a2 += UINT32_C(0xa9e3e905);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  5;	t1 = a1 <<  5;	t2 = a2 <<  5;	a0 >>= 27;	a1 >>= 27;	a2 >>= 27;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block +  6);	d1 += load(block +  7);	d2 += load(block +  8);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	t0 &= c0;	t1 &= c1;	t2 &= c2;	d0 += UINT32_C(0xfcefa3f8);	d1 += UINT32_C(0xfcefa3f8);	d2 += UINT32_C(0xfcefa3f8);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 <<  9;	t1 = d1 <<  9;	t2 = d2 <<  9;	d0 >>= 23;	d1 >>= 23;	d2 >>= 23;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 21);	c1 += load(block + 22);	c2 += load(block + 23);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	t0 &= b0;	t1 &= b1;	t2 &= b2;	c0 += UINT32_C(0x676f02d9);	c1 += UINT32_C(0x676f02d9);	c2 += UINT32_C(0x676f02d9);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 14;	t1 = c1 << 14;	t2 = c2 << 14;	c0 >>= 18;	c1 >>= 18;	c2 >>= 18;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 36);	b1 += load(block + 37);	b2 += load(block + 38);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	t0 &= a0;	t1 &= a1;	t2 &= a2;	b0 += UINT32_C(0x8d2a4c8a);	b1 += UINT32_C(0x8d2a4c8a);	b2 += UINT32_C(0x8d2a4c8a);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 20;	t1 = b1 << 20;	t2 = b2 << 20;	b0 >>= 12;	b1 >>= 12;	b2 >>= 12;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;

	// Round 3
	a0 += load(block + 15);	a1 += load(block + 16);	a2 += load(block + 17);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	a0 += UINT32_C(0xfffa3942);	a1 += UINT32_C(0xfffa3942);	a2 += UINT32_C(0xfffa3942);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  4;	t1 = a1 <<  4;	t2 = a2 <<  4;	a0 >>= 28;	a1 >>= 28;	a2 >>= 28;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 24);	d1 += load(block + 25);	d2 += load(block + 26);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	d0 += UINT32_C(0x8771f681);	d1 += UINT32_C(0x8771f681);	d2 += UINT32_C(0x8771f681);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 11;	t1 = d1 << 11;	t2 = d2 << 11;	d0 >>= 21;	d1 >>= 21;	d2 >>= 21;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 33);	c1 += load(block + 34);	c2 += load(block + 35);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	c0 += UINT32_C(0x6d9d6122);	c1 += UINT32_C(0x6d9d6122);	c2 += UINT32_C(0x6d9d6122);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 16;	t1 = c1 << 16;	t2 = c2 << 16;	c0 >>= 16;	c1 >>= 16;	c2 >>= 16;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 42);	b1 += load(block + 43);	b2 += load(block + 44);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	b0 += UINT32_C(0xfde5380c);	b1 += UINT32_C(0xfde5380c);	b2 += UINT32_C(0xfde5380c);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 23;	t1 = b1 << 23;	t2 = b2 << 23;	b0 >>=  9;	b1 >>=  9;	b2 >>=  9;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block +  3);	a1 += load(block +  4);	a2 += load(block +  5);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	a0 += UINT32_C(0xa4beea44);	a1 += UINT32_C(0xa4beea44);	a2 += UINT32_C(0xa4beea44);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  4;	t1 = a1 <<  4;	t2 = a2 <<  4;	a0 >>= 28;	a1 >>= 28;	a2 >>= 28;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 12);	d1 += load(block + 13);	d2 += load(block + 14);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	d0 += UINT32_C(0x4bdecfa9);	d1 += UINT32_C(0x4bdecfa9);	d2 += UINT32_C(0x4bdecfa9);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 11;	t1 = d1 << 11;	t2 = d2 << 11;	d0 >>= 21;	d1 >>= 21;	d2 >>= 21;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 21);	c1 += load(block + 22);	c2 += load(block + 23);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	c0 += UINT32_C(0xf6bb4b60);	c1 += UINT32_C(0xf6bb4b60);	c2 += UINT32_C(0xf6bb4b60);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 16;	t1 = c1 << 16;	t2 = c2 << 16;	c0 >>= 16;	c1 >>= 16;	c2 >>= 16;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 30);	b1 += load(block + 31);	b2 += load(block + 32);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	b0 += UINT32_C(0xbebfbc70);	b1 += UINT32_C(0xbebfbc70);	b2 += UINT32_C(0xbebfbc70);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 23;	t1 = b1 << 23;	t2 = b2 << 23;	b0 >>=  9;	b1 >>=  9;	b2 >>=  9;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block + 39);	a1 += load(block + 40);	a2 += load(block + 41);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	a0 += UINT32_C(0x289b7ec6);	a1 += UINT32_C(0x289b7ec6);	a2 += UINT32_C(0x289b7ec6);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  4;	t1 = a1 <<  4;	t2 = a2 <<  4;	a0 >>= 28;	a1 >>= 28;	a2 >>= 28;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block +  0);	d1 += load(block +  1);	d2 += load(block +  2);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	d0 += UINT32_C(0xeaa127fa);	d1 += UINT32_C(0xeaa127fa);	d2 += UINT32_C(0xeaa127fa);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 11;	t1 = d1 << 11;	t2 = d2 << 11;	d0 >>= 21;	d1 >>= 21;	d2 >>= 21;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block +  9);	c1 += load(block + 10);	c2 += load(block + 11);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	c0 += UINT32_C(0xd4ef3085);	c1 += UINT32_C(0xd4ef3085);	c2 += UINT32_C(0xd4ef3085);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 16;	t1 = c1 << 16;	t2 = c2 << 16;	c0 >>= 16;	c1 >>= 16;	c2 >>= 16;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 18);	b1 += load(block + 19);	b2 += load(block + 20);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	b0 += UINT32_C(0x4881d05);	b1 += UINT32_C(0x4881d05);	b2 += UINT32_C(0x4881d05);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 23;	t1 = b1 << 23;	t2 = b2 << 23;	b0 >>=  9;	b1 >>=  9;	b2 >>=  9;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block + 27);	a1 += load(block + 28);	a2 += load(block + 29);	t0 = c0 ^ d0;	t1 = c1 ^ d1;	t2 = c2 ^ d2;	a0 += UINT32_C(0xd9d4d039);	a1 += UINT32_C(0xd9d4d039);	a2 += UINT32_C(0xd9d4d039);	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  4;	t1 = a1 <<  4;	t2 = a2 <<  4;	a0 >>= 28;	a1 >>= 28;	a2 >>= 28;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 36);	d1 += load(block + 37);	d2 += load(block + 38);	t0 = b0 ^ c0;	t1 = b1 ^ c1;	t2 = b2 ^ c2;	d0 += UINT32_C(0xe6db99e5);	d1 += UINT32_C(0xe6db99e5);	d2 += UINT32_C(0xe6db99e5);	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 11;	t1 = d1 << 11;	t2 = d2 << 11;	d0 >>= 21;	d1 >>= 21;	d2 >>= 21;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 45);	c1 += load(block + 46);	c2 += load(block + 47);	t0 = a0 ^ b0;	t1 = a1 ^ b1;	t2 = a2 ^ b2;	c0 += UINT32_C(0x1fa27cf8);	c1 += UINT32_C(0x1fa27cf8);	c2 += UINT32_C(0x1fa27cf8);	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 16;	t1 = c1 << 16;	t2 = c2 << 16;	c0 >>= 16;	c1 >>= 16;	c2 >>= 16;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block +  6);	b1 += load(block +  7);	b2 += load(block +  8);	t0 = d0 ^ a0;	t1 = d1 ^ a1;	t2 = d2 ^ a2;	b0 += UINT32_C(0xc4ac5665);	b1 += UINT32_C(0xc4ac5665);	b2 += UINT32_C(0xc4ac5665);	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 23;	t1 = b1 << 23;	t2 = b2 << 23;	b0 >>=  9;	b1 >>=  9;	b2 >>=  9;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;

	// Round 4
	a0 += load(block +  0);	a1 += load(block +  1);	a2 += load(block +  2);	t0 = ~(d0);	t1 = ~(d1);	t2 = ~(d2);	a0 += UINT32_C(0xf4292244);	a1 += UINT32_C(0xf4292244);	a2 += UINT32_C(0xf4292244);	t0 |= b0;	t1 |= b1;	t2 |= b2;	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  6;	t1 = a1 <<  6;	t2 = a2 <<  6;	a0 >>= 26;	a1 >>= 26;	a2 >>= 26;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 21);	d1 += load(block + 22);	d2 += load(block + 23);	t0 = ~(c0);	t1 = ~(c1);	t2 = ~(c2);	d0 += UINT32_C(0x432aff97);	d1 += UINT32_C(0x432aff97);	d2 += UINT32_C(0x432aff97);	t0 |= a0;	t1 |= a1;	t2 |= a2;	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 10;	t1 = d1 << 10;	t2 = d2 << 10;	d0 >>= 22;	d1 >>= 22;	d2 >>= 22;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 42);	c1 += load(block + 43);	c2 += load(block + 44);	t0 = ~(b0);	t1 = ~(b1);	t2 = ~(b2);	c0 += UINT32_C(0xab9423a7);	c1 += UINT32_C(0xab9423a7);	c2 += UINT32_C(0xab9423a7);	t0 |= d0;	t1 |= d1;	t2 |= d2;	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 15;	t1 = c1 << 15;	t2 = c2 << 15;	c0 >>= 17;	c1 >>= 17;	c2 >>= 17;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 15);	b1 += load(block + 16);	b2 += load(block + 17);	t0 = ~(a0);	t1 = ~(a1);	t2 = ~(a2);	b0 += UINT32_C(0xfc93a039);	b1 += UINT32_C(0xfc93a039);	b2 += UINT32_C(0xfc93a039);	t0 |= c0;	t1 |= c1;	t2 |= c2;	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 21;	t1 = b1 << 21;	t2 = b2 << 21;	b0 >>= 11;	b1 >>= 11;	b2 >>= 11;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block + 36);	a1 += load(block + 37);	a2 += load(block + 38);	t0 = ~(d0);	t1 = ~(d1);	t2 = ~(d2);	a0 += UINT32_C(0x655b59c3);	a1 += UINT32_C(0x655b59c3);	a2 += UINT32_C(0x655b59c3);	t0 |= b0;	t1 |= b1;	t2 |= b2;	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  6;	t1 = a1 <<  6;	t2 = a2 <<  6;	a0 >>= 26;	a1 >>= 26;	a2 >>= 26;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block +  9);	d1 += load(block + 10);	d2 += load(block + 11);	t0 = ~(c0);	t1 = ~(c1);	t2 = ~(c2);	d0 += UINT32_C(0x8f0ccc92);	d1 += UINT32_C(0x8f0ccc92);	d2 += UINT32_C(0x8f0ccc92);	t0 |= a0;	t1 |= a1;	t2 |= a2;	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 10;	t1 = d1 << 10;	t2 = d2 << 10;	d0 >>= 22;	d1 >>= 22;	d2 >>= 22;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 30);	c1 += load(block + 31);	c2 += load(block + 32);	t0 = ~(b0);	t1 = ~(b1);	t2 = ~(b2);	c0 += UINT32_C(0xffeff47d);	c1 += UINT32_C(0xffeff47d);	c2 += UINT32_C(0xffeff47d);	t0 |= d0;	t1 |= d1;	t2 |= d2;	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 15;	t1 = c1 << 15;	t2 = c2 << 15;	c0 >>= 17;	c1 >>= 17;	c2 >>= 17;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block +  3);	b1 += load(block +  4);	b2 += load(block +  5);	t0 = ~(a0);	t1 = ~(a1);	t2 = ~(a2);	b0 += UINT32_C(0x85845dd1);	b1 += UINT32_C(0x85845dd1);	b2 += UINT32_C(0x85845dd1);	t0 |= c0;	t1 |= c1;	t2 |= c2;	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 21;	t1 = b1 << 21;	t2 = b2 << 21;	b0 >>= 11;	b1 >>= 11;	b2 >>= 11;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block + 24);	a1 += load(block + 25);	a2 += load(block + 26);	t0 = ~(d0);	t1 = ~(d1);	t2 = ~(d2);	a0 += UINT32_C(0x6fa87e4f);	a1 += UINT32_C(0x6fa87e4f);	a2 += UINT32_C(0x6fa87e4f);	t0 |= b0;	t1 |= b1;	t2 |= b2;	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  6;	t1 = a1 <<  6;	t2 = a2 <<  6;	a0 >>= 26;	a1 >>= 26;	a2 >>= 26;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 45);	d1 += load(block + 46);	d2 += load(block + 47);	t0 = ~(c0);	t1 = ~(c1);	t2 = ~(c2);	d0 += UINT32_C(0xfe2ce6e0);	d1 += UINT32_C(0xfe2ce6e0);	d2 += UINT32_C(0xfe2ce6e0);	t0 |= a0;	t1 |= a1;	t2 |= a2;	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 10;	t1 = d1 << 10;	t2 = d2 << 10;	d0 >>= 22;	d1 >>= 22;	d2 >>= 22;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block + 18);	c1 += load(block + 19);	c2 += load(block + 20);	t0 = ~(b0);	t1 = ~(b1);	t2 = ~(b2);	c0 += UINT32_C(0xa3014314);	c1 += UINT32_C(0xa3014314);	c2 += UINT32_C(0xa3014314);	t0 |= d0;	t1 |= d1;	t2 |= d2;	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 15;	t1 = c1 << 15;	t2 = c2 << 15;	c0 >>= 17;	c1 >>= 17;	c2 >>= 17;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 39);	b1 += load(block + 40);	b2 += load(block + 41);	t0 = ~(a0);	t1 = ~(a1);	t2 = ~(a2);	b0 += UINT32_C(0x4e0811a1);	b1 += UINT32_C(0x4e0811a1);	b2 += UINT32_C(0x4e0811a1);	t0 |= c0;	t1 |= c1;	t2 |= c2;	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 21;	t1 = b1 << 21;	t2 = b2 << 21;	b0 >>= 11;	b1 >>= 11;	b2 >>= 11;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;
	a0 += load(block + 12);	a1 += load(block + 13);	a2 += load(block + 14);	t0 = ~(d0);	t1 = ~(d1);	t2 = ~(d2);	a0 += UINT32_C(0xf7537e82);	a1 += UINT32_C(0xf7537e82);	a2 += UINT32_C(0xf7537e82);	t0 |= b0;	t1 |= b1;	t2 |= b2;	t0 ^= c0;	t1 ^= c1;	t2 ^= c2;	a0 += t0;	a1 += t1;	a2 += t2;	t0 = a0 <<  6;	t1 = a1 <<  6;	t2 = a2 <<  6;	a0 >>= 26;	a1 >>= 26;	a2 >>= 26;	a0 |= t0;	a1 |= t1;	a2 |= t2;	a0 += b0;	a1 += b1;	a2 += b2;
	d0 += load(block + 33);	d1 += load(block + 34);	d2 += load(block + 35);	t0 = ~(c0);	t1 = ~(c1);	t2 = ~(c2);	d0 += UINT32_C(0xbd3af235);	d1 += UINT32_C(0xbd3af235);	d2 += UINT32_C(0xbd3af235);	t0 |= a0;	t1 |= a1;	t2 |= a2;	t0 ^= b0;	t1 ^= b1;	t2 ^= b2;	d0 += t0;	d1 += t1;	d2 += t2;	t0 = d0 << 10;	t1 = d1 << 10;	t2 = d2 << 10;	d0 >>= 22;	d1 >>= 22;	d2 >>= 22;	d0 |= t0;	d1 |= t1;	d2 |= t2;	d0 += a0;	d1 += a1;	d2 += a2;
	c0 += load(block +  6);	c1 += load(block +  7);	c2 += load(block +  8);	t0 = ~(b0);	t1 = ~(b1);	t2 = ~(b2);	c0 += UINT32_C(0x2ad7d2bb);	c1 += UINT32_C(0x2ad7d2bb);	c2 += UINT32_C(0x2ad7d2bb);	t0 |= d0;	t1 |= d1;	t2 |= d2;	t0 ^= a0;	t1 ^= a1;	t2 ^= a2;	c0 += t0;	c1 += t1;	c2 += t2;	t0 = c0 << 15;	t1 = c1 << 15;	t2 = c2 << 15;	c0 >>= 17;	c1 >>= 17;	c2 >>= 17;	c0 |= t0;	c1 |= t1;	c2 |= t2;	c0 += d0;	c1 += d1;	c2 += d2;
	b0 += load(block + 27);	b1 += load(block + 28);	b2 += load(block + 29);	t0 = ~(a0);	t1 = ~(a1);	t2 = ~(a2);	b0 += UINT32_C(0xeb86d391);	b1 += UINT32_C(0xeb86d391);	b2 += UINT32_C(0xeb86d391);	t0 |= c0;	t1 |= c1;	t2 |= c2;	t0 ^= d0;	t1 ^= d1;	t2 ^= d2;	b0 += t0;	b1 += t1;	b2 += t2;	t0 = b0 << 21;	t1 = b1 << 21;	t2 = b2 << 21;	b0 >>= 11;	b1 >>= 11;	b2 >>= 11;	b0 |= t0;	b1 |= t1;	b2 |= t2;	b0 += c0;	b1 += c1;	b2 += c2;

	// Save state
	store(state +  0, load(state +  0) + a0);	store(state +  1, load(state +  1) + a1);	store(state +  2, load(state +  2) + a2);
	store(state +  9, load(state +  9) + d0);	store(state + 10, load(state + 10) + d1);	store(state + 11, load(state + 11) + d2);
	store(state +  6, load(state +  6) + c0);	store(state +  7, load(state +  7) + c1);	store(state +  8, load(state +  8) + c2);
	store(state +  3, load(state +  3) + b0);	store(state +  4, load(state +  4) + b1);	store(state +  5, load(state +  5) + b2);
}

