/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file is part of 'Fast-Small-Crypto'
// 
// Copyright (c) 2024 by Alain Espinosa.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// AES supported sizes: 128, 192, 256
// 
// AES modes:
//		- CBC enables AES encryption in CBC-mode of operation.
//		- CTR enables encryption in counter-mode.
//		- ECB enables the basic ECB 16-byte block algorithm.
//
// [AES-WP]   https://www.intel.com/content/www/us/en/developer/articles/tool/intel-advanced-encryption-standard-aes-instructions-set.html
// [CLMUL-WP] https://www.intel.com/content/www/us/en/develop/download/intel-carry-less-multiplication-instruction-and-its-usage-for-computing-the-gcm-mode.html

#include <cstring>
#include <cassert>
#include "aes.h"

#define SimdScalarType uint8_t
#include "simd.hpp"
using namespace simd;

// The size of the expanded key
//#define AES128_keyExpSize 176
//#define AES192_keyExpSize 208
#define AES256_ROUNDKEY_VEC128 ((240 + 16) / sizeof(simd::Vec128u8)) // 16 more bytes to simplify key generation

// Key expansion, 192-bit case
static SIMD_INLINE void aesni_set_rk_192(simd::Vec128u8& state0, simd::Vec128u8& state1, simd::Vec128u8 xword, unsigned char* rk) noexcept
{
    /*
     * Finish generating the next 6 quarter-keys.
     *
     * On entry state0 is r3:r2:r1:r0, state1 is stuff:stuff:r5:r4
     * and xword is stuff:stuff:X:stuff with X = rot( sub( r3 ) ) ^ RCON
     * (obtained with AESKEYGENASSIST).
     *
     * On exit, state0 is r9:r8:r7:r6 and state1 is stuff:stuff:r11:r10
     * and those are written to the round key buffer.
     */
    xword = _mm_shuffle_epi32(xword, 0x55);   // X:X:X:X
    xword = _mm_xor_si128(xword, state0);    // X+r3:X+r2:X+r1:X+r0
    state0 = _mm_slli_si128(state0, 4);     // r2:r1:r0:0
    xword = _mm_xor_si128(xword, state0);    // X+r3+r2:X+r2+r1:X+r1+r0:X+r0
    state0 = _mm_slli_si128(state0, 4);     // r1:r0:0:0
    xword = _mm_xor_si128(xword, state0);    // X+r3+r2+r1:X+r2+r1+r0:X+r1+r0:X+r0
    state0 = _mm_slli_si128(state0, 4);     // r0:0:0:0
    xword = _mm_xor_si128(xword, state0);    // X+r3+r2+r1+r0:X+r2+r1+r0:X+r1+r0:X+r0
    state0 = xword;                          // = r9:r8:r7:r6

    xword = _mm_shuffle_epi32(xword, 0xff);   // r9:r9:r9:r9
    xword = _mm_xor_si128(xword, state1);    // stuff:stuff:r9+r5:r9+r4
    state1 = _mm_slli_si128(state1, 4);     // stuff:stuff:r4:0
    xword = _mm_xor_si128(xword, state1);    // stuff:stuff:r9+r5+r4:r9+r4
    state1 = xword;                          // = stuff:stuff:r11:r10

    /* Store state0 and the low half of state1 into rk, which is conceptually
     * an array of 24-byte elements. Since 24 is not a multiple of 16,
     * rk is not necessarily aligned so just `*rk = *state0` doesn't work. */
    simd::storeu((simd::Vec128u8*)rk, state0);
    simd::storeu((simd::Vec128u8*)(rk+16), state1); // NOTE: Only need to store 8 bytes instead of 16
}
static SIMD_INLINE void aesni_set_rk_256(simd::Vec128u8 state0, simd::Vec128u8 state1, simd::Vec128u8 xword, simd::Vec128u8& rk0, simd::Vec128u8& rk1) noexcept
{
    /*
     * Finish generating the next two round keys.
     *
     * On entry state0 is r3:r2:r1:r0, state1 is r7:r6:r5:r4 and
     * xword is X:stuff:stuff:stuff with X = rot( sub( r7 )) ^ RCON
     * (obtained with AESKEYGENASSIST).
     *
     * On exit, *rk0 is r11:r10:r9:r8 and *rk1 is r15:r14:r13:r12
     */
    xword = _mm_shuffle_epi32(xword, 0xff);
    xword = _mm_xor_si128(xword, state0);
    state0 = _mm_slli_si128(state0, 4);
    xword = _mm_xor_si128(xword, state0);
    state0 = _mm_slli_si128(state0, 4);
    xword = _mm_xor_si128(xword, state0);
    state0 = _mm_slli_si128(state0, 4);
    state0 = _mm_xor_si128(state0, xword);
    rk0 = state0;

    /* Set xword to stuff:Y:stuff:stuff with Y = subword( r11 )
     * and proceed to generate next round key from there */
    xword = _mm_aeskeygenassist_si128(state0, 0x00);
    xword = _mm_shuffle_epi32(xword, 0xaa);
    xword = _mm_xor_si128(xword, state1);
    state1 = _mm_slli_si128(state1, 4);
    xword = _mm_xor_si128(xword, state1);
    state1 = _mm_slli_si128(state1, 4);
    xword = _mm_xor_si128(xword, state1);
    state1 = _mm_slli_si128(state1, 4);
    state1 = _mm_xor_si128(state1, xword);
    rk1 = state1;
}

// This function produces 4*(Nr+1) round keys. The round keys are used in each round to decrypt the states. 
static void key_expansion_encryption(simd::Vec128u8* RK, const uint8_t* key, const unsigned num_rounds) noexcept
{
    simd::Vec128u8 RKv, RKv0, RKv1;

    switch (num_rounds) {
    case 10:// AES128
        RKv = simd::loadu((const simd::Vec128u8*)key);                                                                                                     simd::store(RK +  0, RKv);
        RKv ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv, 0x01), 0xff) ^ _mm_slli_si128(RKv, 4) ^ _mm_slli_si128(RKv, 8) ^ _mm_slli_si128(RKv, 12);  simd::store(RK +  1, RKv);
        RKv ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv, 0x02), 0xff) ^ _mm_slli_si128(RKv, 4) ^ _mm_slli_si128(RKv, 8) ^ _mm_slli_si128(RKv, 12);  simd::store(RK +  2, RKv);
        RKv ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv, 0x04), 0xff) ^ _mm_slli_si128(RKv, 4) ^ _mm_slli_si128(RKv, 8) ^ _mm_slli_si128(RKv, 12);  simd::store(RK +  3, RKv);
        RKv ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv, 0x08), 0xff) ^ _mm_slli_si128(RKv, 4) ^ _mm_slli_si128(RKv, 8) ^ _mm_slli_si128(RKv, 12);  simd::store(RK +  4, RKv);
        RKv ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv, 0x10), 0xff) ^ _mm_slli_si128(RKv, 4) ^ _mm_slli_si128(RKv, 8) ^ _mm_slli_si128(RKv, 12);  simd::store(RK +  5, RKv);
        RKv ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv, 0x20), 0xff) ^ _mm_slli_si128(RKv, 4) ^ _mm_slli_si128(RKv, 8) ^ _mm_slli_si128(RKv, 12);  simd::store(RK +  6, RKv);
        RKv ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv, 0x40), 0xff) ^ _mm_slli_si128(RKv, 4) ^ _mm_slli_si128(RKv, 8) ^ _mm_slli_si128(RKv, 12);  simd::store(RK +  7, RKv);
        RKv ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv, 0x80), 0xff) ^ _mm_slli_si128(RKv, 4) ^ _mm_slli_si128(RKv, 8) ^ _mm_slli_si128(RKv, 12);  simd::store(RK +  8, RKv);
        RKv ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv, 0x1B), 0xff) ^ _mm_slli_si128(RKv, 4) ^ _mm_slli_si128(RKv, 8) ^ _mm_slli_si128(RKv, 12);  simd::store(RK +  9, RKv);
        RKv ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv, 0x36), 0xff) ^ _mm_slli_si128(RKv, 4) ^ _mm_slli_si128(RKv, 8) ^ _mm_slli_si128(RKv, 12);  simd::store(RK + 10, RKv);
        break;
    case 12:// AES192
        memcpy(RK, key, 24);
        RKv0 = simd::load(RK);
        RKv1 = (simd::Vec128u8)_mm_loadl_epi64((const __m128i*)RK + 1);

        aesni_set_rk_192(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x01), ((uint8_t*)RK) + 24 * 1);
        aesni_set_rk_192(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x02), ((uint8_t*)RK) + 24 * 2);
        aesni_set_rk_192(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x04), ((uint8_t*)RK) + 24 * 3);
        aesni_set_rk_192(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x08), ((uint8_t*)RK) + 24 * 4);
        aesni_set_rk_192(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x10), ((uint8_t*)RK) + 24 * 5);
        aesni_set_rk_192(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x20), ((uint8_t*)RK) + 24 * 6);
        aesni_set_rk_192(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x40), ((uint8_t*)RK) + 24 * 7);
        aesni_set_rk_192(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x80), ((uint8_t*)RK) + 24 * 8);
        break;
    case 14:// AES256
        RKv0 = simd::loadu((const simd::Vec128u8*)key);
        RKv1 = simd::loadu((const simd::Vec128u8*)(key + 16));
        simd::store(RK + 0, RKv0); simd::store(RK + 1, RKv1);

        aesni_set_rk_256(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x01), RKv0, RKv1);   simd::store(RK +  2, RKv0); simd::store(RK +  3, RKv1);
        aesni_set_rk_256(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x02), RKv0, RKv1);   simd::store(RK +  4, RKv0); simd::store(RK +  5, RKv1);
        aesni_set_rk_256(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x04), RKv0, RKv1);   simd::store(RK +  6, RKv0); simd::store(RK +  7, RKv1);
        aesni_set_rk_256(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x08), RKv0, RKv1);   simd::store(RK +  8, RKv0); simd::store(RK +  9, RKv1);
        aesni_set_rk_256(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x10), RKv0, RKv1);   simd::store(RK + 10, RKv0); simd::store(RK + 11, RKv1);
        aesni_set_rk_256(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x20), RKv0, RKv1);   simd::store(RK + 12, RKv0); simd::store(RK + 13, RKv1);
        aesni_set_rk_256(RKv0, RKv1, _mm_aeskeygenassist_si128(RKv1, 0x40), RKv0, RKv1);   simd::store(RK + 14, RKv0); simd::store(RK + 15, RKv1);
        break;
    }
}
static void key_expansion_decryption(simd::Vec128u8* RK, const uint8_t* key, const unsigned num_rounds) noexcept
{
    key_expansion_encryption(RK, key, num_rounds);

    // Reverse data on RK
    simd::Vec128u8* rk_tail = RK + num_rounds;
    for (uint32_t i = 0; i < (num_rounds + 1) / 2; i++, rk_tail--)
    {
        simd::Vec128u8 tmp = simd::load(RK + i);
        simd::store(RK + i, simd::load(rk_tail));
        simd::store(rk_tail, tmp);
    }
    RK++;

    for (uint32_t i = 0; i < num_rounds - 1; i++, RK++)
        simd::store(RK, _mm_aesimc_si128(simd::load(RK)));
}


static void encrypt_block(uint8_t input[AES_BLOCKLEN], const simd::Vec128u8* RK, const unsigned num_rounds) noexcept
{
    simd::Vec128u8 state = simd::loadu((const Vec128u8*)input);
    state ^= simd::load(RK);
    RK++;

    for (unsigned i = 0; i < num_rounds - 1; i++, RK++)
        state = _mm_aesenc_si128(state, simd::load(RK));
    state = _mm_aesenclast_si128(state, simd::load(RK));

    simd::storeu((Vec128u8*)input, state);
}
static void decrypt_block(uint8_t input[AES_BLOCKLEN], const simd::Vec128u8* RK, const unsigned num_rounds) noexcept
{
    simd::Vec128u8 state = simd::loadu((const simd::Vec128u8*)input);
    state ^= simd::load(RK);
    RK++;

    for (unsigned i = 0; i < num_rounds - 1; i++, RK++)
        state = _mm_aesdec_si128(state, simd::load(RK));
    state = _mm_aesdeclast_si128(state, simd::load(RK));

    simd::storeu((simd::Vec128u8*)input, state);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ECB
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTE: ECB is considered insecure for most uses
void AESNI_ECB_encrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length) noexcept
{
    assert(key_length == AES128_KEY_LENGTH || key_length == AES192_KEY_LENGTH || key_length == AES256_KEY_LENGTH);
    assert(data_length % AES_BLOCKLEN == 0);

    unsigned num_rounds = key_length / sizeof(uint32_t) + 6; // The number of rounds in AES Cipher.

    simd::Vec128u8 round_key[AES256_ROUNDKEY_VEC128];
    key_expansion_encryption(round_key, key, num_rounds);
    for (size_t i = 0; i < data_length; i += AES_BLOCKLEN)
        encrypt_block(data + i, round_key, num_rounds);
}
void AESNI_ECB_decrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length) noexcept
{
    assert(key_length == AES128_KEY_LENGTH || key_length == AES192_KEY_LENGTH || key_length == AES256_KEY_LENGTH);
    assert(data_length % AES_BLOCKLEN == 0);

    unsigned num_rounds = key_length / sizeof(uint32_t) + 6; // The number of rounds in AES Cipher.

    simd::Vec128u8 round_key[AES256_ROUNDKEY_VEC128];
    key_expansion_decryption(round_key, key, num_rounds);
    for (size_t i = 0; i < data_length; i += AES_BLOCKLEN)
        decrypt_block(data + i, round_key, num_rounds);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CBC
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Suggest https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
// NOTES: no IV should ever be reused with the same key 
void AESNI_CBC_encrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length, const uint8_t iv[AES_BLOCKLEN]) noexcept
{
    assert(key_length == AES128_KEY_LENGTH || key_length == AES192_KEY_LENGTH || key_length == AES256_KEY_LENGTH);
    assert(data_length % AES_BLOCKLEN == 0);

    unsigned num_rounds = key_length / sizeof(uint32_t) + 6; // The number of rounds in AES Cipher.

    simd::Vec128u8 round_key[AES256_ROUNDKEY_VEC128];
    key_expansion_encryption(round_key, key, num_rounds);

    simd::Vec128u8 current_iv = simd::loadu((const Vec128u8*)iv);
    for (size_t i = 0; i < data_length; i += AES_BLOCKLEN, data += AES_BLOCKLEN)
    {
        simd::storeu((Vec128u8*)data, simd::loadu((const Vec128u8*)data) ^ current_iv);
        encrypt_block(data, round_key, num_rounds);
        current_iv = simd::loadu((const Vec128u8*)data);
    }
}
void AESNI_CBC_decrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length, const uint8_t iv[AES_BLOCKLEN]) noexcept
{
    assert(key_length == AES128_KEY_LENGTH || key_length == AES192_KEY_LENGTH || key_length == AES256_KEY_LENGTH);
    assert(data_length % AES_BLOCKLEN == 0);

    unsigned num_rounds = key_length / sizeof(uint32_t) + 6; // The number of rounds in AES Cipher.

    simd::Vec128u8 round_key[AES256_ROUNDKEY_VEC128];
    key_expansion_decryption(round_key, key, num_rounds);
    simd::Vec128u8 ctx_iv = simd::loadu((const Vec128u8*)iv);

    for (size_t i = 0; i < data_length; i += AES_BLOCKLEN, data += AES_BLOCKLEN)
    {
        simd::Vec128u8 tmp_iv = simd::loadu((const Vec128u8*)data);
        decrypt_block(data, round_key, num_rounds);
        simd::storeu((Vec128u8*)data, simd::loadu((const Vec128u8*)data) ^ ctx_iv);
        ctx_iv = tmp_iv;
    }
}
