//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MD4 Message-Digest Algorithm
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#pragma once

#include "simd.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

/// <summary>
/// MD4 compress block
/// </summary>
/// <param name="state">The md4 state</param>
/// <param name="block">The message to compress</param>
void md4_block_plain_c(uint32_t state[4], const uint32_t block[16]) noexcept;

/// <summary>
/// MD4 compress block
/// </summary>
/// <param name="state">The md4 state</param>
/// <param name="block">The message to compress</param>
void md4_block_sse2_x3(simd::Vec128u32 state[12], const simd::Vec128u32 block[48]) noexcept;

/// <summary>
/// MD4 compress block
/// </summary>
/// <param name="state">The md4 state</param>
/// <param name="block">The message to compress</param>
void md4_block_avx_x3(simd::Vec128u32 state[12], const simd::Vec128u32 block[48]) noexcept;

/// <summary>
/// MD4 compress block
/// </summary>
/// <param name="state">The md4 state</param>
/// <param name="block">The message to compress</param>
void md4_block_avx2_x3(simd::Vec256u32 state[12], const simd::Vec256u32 block[48]) noexcept;

/// <summary>
/// MD4 compress block
/// </summary>
/// <param name="state">The md4 state</param>
/// <param name="block">The message to compress</param>
void md4_block_avx512_x4(simd::Vec512u32 state[16], const simd::Vec512u32 block[64]) noexcept;


#ifdef __cplusplus
}
#endif
