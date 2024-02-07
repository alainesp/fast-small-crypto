//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA256 - Secure Hash Algorithm 2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#pragma once

#include "simd.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

/// <summary>
/// SHA256 compress block
/// </summary>
/// <param name="state">The SHA256 state</param>
/// <param name="block">The message to compress</param>
void sha256_block_plain_c(uint32_t state[8], const uint32_t W[16]) noexcept;

/// <summary>
/// SHA256 compress block
/// </summary>
/// <param name="state">The SHA256 state</param>
/// <param name="block">The message to compress</param>
void sha256_block_sse2(simd::Vec128u32 state[8], const simd::Vec128u32 W[16]) noexcept;

/// <summary>
/// SHA256 compress block
/// </summary>
/// <param name="state">The SHA256 state</param>
/// <param name="block">The message to compress</param>
void sha256_block_avx(simd::Vec128u32 state[8], const simd::Vec128u32 W[16]) noexcept;

/// <summary>
/// SHA256 compress block
/// </summary>
/// <param name="state">The SHA256 state</param>
/// <param name="block">The message to compress</param>
void sha256_block_avx2(simd::Vec256u32 state[8], const simd::Vec256u32 W[16]) noexcept;

/// <summary>
/// SHA256 compress block
/// </summary>
/// <param name="state">The SHA256 state</param>
/// <param name="block">The message to compress</param>
void sha256_block_avx512(simd::Vec512u32 state[8], const simd::Vec512u32 W[16]) noexcept;


#ifdef __cplusplus
}
#endif
