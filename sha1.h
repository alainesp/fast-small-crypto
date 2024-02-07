//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA1 - Secure Hash Algorithm 1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#pragma once

#include "simd.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

/// <summary>
/// SHA1 compress block
/// </summary>
/// <param name="state">The SHA1 state</param>
/// <param name="block">The message to compress</param>
void sha1_block_plain_c(uint32_t state[5], const uint32_t W[16]) noexcept;


/// <summary>
/// SHA1 compress block
/// </summary>
/// <param name="state">The SHA1 state</param>
/// <param name="block">The message to compress</param>
void sha1_block_shani(uint32_t state[5], const uint32_t W[16]) noexcept;
/// <summary>
/// SHA1 compress block
/// </summary>
/// <param name="state">The SHA1 state</param>
/// <param name="block">The message to compress</param>
void sha1_block_shani_x2(uint32_t state[10], const uint32_t W[32]) noexcept;
/// <summary>
/// SHA1 compress block
/// </summary>
/// <param name="state">The SHA1 state</param>
/// <param name="block">The message to compress</param>
void sha1_block_shani_x3(uint32_t state[15], const uint32_t W[48]) noexcept;


/// <summary>
/// SHA1 compress block
/// </summary>
/// <param name="state">The SHA1 state</param>
/// <param name="block">The message to compress</param>
void sha1_block_sse2(simd::Vec128u32 state[5], const simd::Vec128u32 W[16]) noexcept;

/// <summary>
/// SHA1 compress block
/// </summary>
/// <param name="state">The SHA1 state</param>
/// <param name="block">The message to compress</param>
void sha1_block_avx(simd::Vec128u32 state[5], const simd::Vec128u32 W[16]) noexcept;

/// <summary>
/// SHA1 compress block
/// </summary>
/// <param name="state">The SHA1 state</param>
/// <param name="block">The message to compress</param>
void sha1_block_avx2(simd::Vec256u32 state[5], const simd::Vec256u32 W[16]) noexcept;

/// <summary>
/// SHA1 compress block
/// </summary>
/// <param name="state">The SHA1 state</param>
/// <param name="block">The message to compress</param>
void sha1_block_avx512(simd::Vec512u32 state[5], const simd::Vec512u32 W[16]) noexcept;


#ifdef __cplusplus
}
#endif
