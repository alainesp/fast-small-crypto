//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MD4 Message-Digest Algorithm
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library

#include <immintrin.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

//// <summary>
//// MD4 compress block
//// </summary>
//// <param name="state">The md4 state</param>
//// <param name="block">The message to compress</param>
void md4_block_PLAIN_C(uint32_t state[4], uint32_t block[16]);
void md4_block_AVX2_INTRINSICS(__m256i state[12], __m256i block[48]);

#ifdef __cplusplus
}
#endif
