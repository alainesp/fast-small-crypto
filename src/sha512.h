//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA512 - Secure Hash Algorithm 2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#pragma once

#include "simd.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

/// <summary>
/// SHA512 compress block
/// </summary>
/// <param name="state">The SHA512 state</param>
/// <param name="block">The message to compress</param>
void sha512_block_plain_c(uint64_t state[8], const uint64_t W[16]) noexcept;

/// <summary>
/// SHA512 compress block
/// </summary>
/// <param name="state">The SHA512 state</param>
/// <param name="block">The message to compress</param>
void sha512_block_sse2(simd::Vec128u64 state[8], const simd::Vec128u64 W[16]) noexcept;

/// <summary>
/// SHA512 compress block
/// </summary>
/// <param name="state">The SHA512 state</param>
/// <param name="block">The message to compress</param>
void sha512_block_avx(simd::Vec128u64 state[8], const simd::Vec128u64 W[16]) noexcept;

/// <summary>
/// SHA512 compress block
/// </summary>
/// <param name="state">The SHA512 state</param>
/// <param name="block">The message to compress</param>
void sha512_block_avx2(simd::Vec256u64 state[8], const simd::Vec256u64 W[16]) noexcept;

/// <summary>
/// SHA512 compress block
/// </summary>
/// <param name="state">The SHA512 state</param>
/// <param name="block">The message to compress</param>
void sha512_block_avx512(simd::Vec512u64 state[8], const simd::Vec512u64 W[16]) noexcept;


#ifdef __cplusplus
}
#endif
