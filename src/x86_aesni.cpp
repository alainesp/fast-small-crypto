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
//		- [NOT IMPLEMENTED] CTR enables encryption in counter-mode.
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

// Key expansion, 256-bit case
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
template<uint8_t AES_KEY_LENGTH> static SIMD_INLINE void key_expansion_encryption(simd::Vec128u8* RK, const uint8_t* key) noexcept
{
    simd::Vec128u8 RKv0, RKv1, t;

    if constexpr (AES_KEY_LENGTH == AES128_KEY_LENGTH)
    {
        RKv0 = simd::loadu((const simd::Vec128u8*)key);                                                                                                                 simd::store(RK +  0, RKv0);
        t = _mm_aeskeygenassist_si128(RKv0, 0x01); RKv0 ^= _mm_slli_si128(RKv0, 4) ^ _mm_shuffle_epi32(t, 0xff)  ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);  simd::store(RK +  1, RKv0);
        t = _mm_aeskeygenassist_si128(RKv0, 0x02); RKv0 ^= _mm_slli_si128(RKv0, 4) ^ _mm_shuffle_epi32(t, 0xff)  ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);  simd::store(RK +  2, RKv0);
        t = _mm_aeskeygenassist_si128(RKv0, 0x04); RKv0 ^= _mm_slli_si128(RKv0, 4) ^ _mm_shuffle_epi32(t, 0xff)  ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);  simd::store(RK +  3, RKv0);
        t = _mm_aeskeygenassist_si128(RKv0, 0x08); RKv0 ^= _mm_slli_si128(RKv0, 4) ^ _mm_shuffle_epi32(t, 0xff)  ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);  simd::store(RK +  4, RKv0);
        t = _mm_aeskeygenassist_si128(RKv0, 0x10); RKv0 ^= _mm_slli_si128(RKv0, 4) ^ _mm_shuffle_epi32(t, 0xff)  ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);  simd::store(RK +  5, RKv0);
        t = _mm_aeskeygenassist_si128(RKv0, 0x20); RKv0 ^= _mm_slli_si128(RKv0, 4) ^ _mm_shuffle_epi32(t, 0xff)  ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);  simd::store(RK +  6, RKv0);
        t = _mm_aeskeygenassist_si128(RKv0, 0x40); RKv0 ^= _mm_slli_si128(RKv0, 4) ^ _mm_shuffle_epi32(t, 0xff)  ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);  simd::store(RK +  7, RKv0);
        t = _mm_aeskeygenassist_si128(RKv0, 0x80); RKv0 ^= _mm_slli_si128(RKv0, 4) ^ _mm_shuffle_epi32(t, 0xff)  ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);  simd::store(RK +  8, RKv0);
        t = _mm_aeskeygenassist_si128(RKv0, 0x1B); RKv0 ^= _mm_slli_si128(RKv0, 4) ^ _mm_shuffle_epi32(t, 0xff)  ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);  simd::store(RK +  9, RKv0);
        t = _mm_aeskeygenassist_si128(RKv0, 0x36); RKv0 ^= _mm_slli_si128(RKv0, 4) ^ _mm_shuffle_epi32(t, 0xff)  ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);  simd::store(RK + 10, RKv0);
     }
    if constexpr (AES_KEY_LENGTH == AES192_KEY_LENGTH)
    {
        memcpy(RK, key, 24);
        RKv0 = simd::load(RK);
        RKv1 = (simd::Vec128u8)_mm_loadl_epi64((const __m128i*)RK + 1);

        RKv0 ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv1, 0x01), 0x55) ^ _mm_slli_si128(RKv0, 4) ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);   RKv1 ^= _mm_shuffle_epi32(RKv0, 0xff) ^ _mm_slli_si128(RKv1, 4);   simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 1), RKv0); simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 1 + 16), RKv1); // NOTE: Only need to store 8 bytes instead of 16 
        RKv0 ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv1, 0x02), 0x55) ^ _mm_slli_si128(RKv0, 4) ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);   RKv1 ^= _mm_shuffle_epi32(RKv0, 0xff) ^ _mm_slli_si128(RKv1, 4);   simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 2), RKv0); simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 2 + 16), RKv1);
        RKv0 ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv1, 0x04), 0x55) ^ _mm_slli_si128(RKv0, 4) ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);   RKv1 ^= _mm_shuffle_epi32(RKv0, 0xff) ^ _mm_slli_si128(RKv1, 4);   simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 3), RKv0); simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 3 + 16), RKv1);
        RKv0 ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv1, 0x08), 0x55) ^ _mm_slli_si128(RKv0, 4) ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);   RKv1 ^= _mm_shuffle_epi32(RKv0, 0xff) ^ _mm_slli_si128(RKv1, 4);   simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 4), RKv0); simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 4 + 16), RKv1);
        RKv0 ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv1, 0x10), 0x55) ^ _mm_slli_si128(RKv0, 4) ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);   RKv1 ^= _mm_shuffle_epi32(RKv0, 0xff) ^ _mm_slli_si128(RKv1, 4);   simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 5), RKv0); simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 5 + 16), RKv1);
        RKv0 ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv1, 0x20), 0x55) ^ _mm_slli_si128(RKv0, 4) ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);   RKv1 ^= _mm_shuffle_epi32(RKv0, 0xff) ^ _mm_slli_si128(RKv1, 4);   simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 6), RKv0); simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 6 + 16), RKv1);
        RKv0 ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv1, 0x40), 0x55) ^ _mm_slli_si128(RKv0, 4) ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);   RKv1 ^= _mm_shuffle_epi32(RKv0, 0xff) ^ _mm_slli_si128(RKv1, 4);   simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 7), RKv0); simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 7 + 16), RKv1);
        RKv0 ^= _mm_shuffle_epi32(_mm_aeskeygenassist_si128(RKv1, 0x80), 0x55) ^ _mm_slli_si128(RKv0, 4) ^ _mm_slli_si128(RKv0, 8) ^ _mm_slli_si128(RKv0, 12);   RKv1 ^= _mm_shuffle_epi32(RKv0, 0xff) ^ _mm_slli_si128(RKv1, 4);   simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 8), RKv0); simd::storeu((simd::Vec128u8*)(((uint8_t*)RK) + 24 * 8 + 16), RKv1);
    }
    if constexpr (AES_KEY_LENGTH == AES256_KEY_LENGTH)
    {
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
    }
}
template<uint8_t AES_KEY_LENGTH> static SIMD_INLINE void key_expansion_decryption(simd::Vec128u8* RK, const uint8_t* key) noexcept
{
    key_expansion_encryption<AES_KEY_LENGTH>(RK, key);
    constexpr unsigned num_rounds = AES_KEY_LENGTH / sizeof(uint32_t) + 6; // The number of rounds in AES Cipher.

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


static SIMD_INLINE void encrypt_block(uint8_t input[AES_BLOCKLEN], const simd::Vec128u8* RK, const unsigned num_rounds) noexcept
{
    simd::Vec128u8 state = simd::loadu((const Vec128u8*)input);
    state ^= simd::load(RK);
    RK++;

    for (unsigned i = 0; i < num_rounds - 1; i++, RK++)
        state = _mm_aesenc_si128(state, simd::load(RK));
    state = _mm_aesenclast_si128(state, simd::load(RK));

    simd::storeu((Vec128u8*)input, state);
}
static SIMD_INLINE void decrypt_block(uint8_t input[AES_BLOCKLEN], const simd::Vec128u8* RK, const unsigned num_rounds) noexcept
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

    simd::Vec128u8 round_key[AES256_ROUNDKEY_VEC128];
    switch (key_length)
    {
    case AES128_KEY_LENGTH: key_expansion_encryption<AES128_KEY_LENGTH>(round_key, key); break;
    case AES192_KEY_LENGTH: key_expansion_encryption<AES192_KEY_LENGTH>(round_key, key); break;
    case AES256_KEY_LENGTH: key_expansion_encryption<AES256_KEY_LENGTH>(round_key, key); break;
    }

    unsigned num_rounds = key_length / sizeof(uint32_t) + 6; // The number of rounds in AES Cipher.
    for (size_t i = 0; i < data_length; i += AES_BLOCKLEN)
        encrypt_block(data + i, round_key, num_rounds);
}
void AESNI_ECB_decrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length) noexcept
{
    assert(key_length == AES128_KEY_LENGTH || key_length == AES192_KEY_LENGTH || key_length == AES256_KEY_LENGTH);
    assert(data_length % AES_BLOCKLEN == 0);

    simd::Vec128u8 round_key[AES256_ROUNDKEY_VEC128];
    switch (key_length)
    {
    case AES128_KEY_LENGTH: key_expansion_decryption<AES128_KEY_LENGTH>(round_key, key); break;
    case AES192_KEY_LENGTH: key_expansion_decryption<AES192_KEY_LENGTH>(round_key, key); break;
    case AES256_KEY_LENGTH: key_expansion_decryption<AES256_KEY_LENGTH>(round_key, key); break;
    }

    unsigned num_rounds = key_length / sizeof(uint32_t) + 6; // The number of rounds in AES Cipher.
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

    simd::Vec128u8 round_key[AES256_ROUNDKEY_VEC128];
    switch (key_length)
    {
    case AES128_KEY_LENGTH: key_expansion_encryption<AES128_KEY_LENGTH>(round_key, key); break;
    case AES192_KEY_LENGTH: key_expansion_encryption<AES192_KEY_LENGTH>(round_key, key); break;
    case AES256_KEY_LENGTH: key_expansion_encryption<AES256_KEY_LENGTH>(round_key, key); break;
    }

    simd::Vec128u8 current_iv = simd::loadu((const Vec128u8*)iv);
    unsigned num_rounds = key_length / sizeof(uint32_t) + 6; // The number of rounds in AES Cipher.
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
  
    simd::Vec128u8 round_key[AES256_ROUNDKEY_VEC128];
    switch (key_length)
    {
    case AES128_KEY_LENGTH: key_expansion_decryption<AES128_KEY_LENGTH>(round_key, key); break;
    case AES192_KEY_LENGTH: key_expansion_decryption<AES192_KEY_LENGTH>(round_key, key); break;
    case AES256_KEY_LENGTH: key_expansion_decryption<AES256_KEY_LENGTH>(round_key, key); break;
    }

    simd::Vec128u8 ctx_iv = simd::loadu((const Vec128u8*)iv);
    unsigned num_rounds = key_length / sizeof(uint32_t) + 6; // The number of rounds in AES Cipher.
    for (size_t i = 0; i < data_length; i += AES_BLOCKLEN, data += AES_BLOCKLEN)
    {
        simd::Vec128u8 tmp_iv = simd::loadu((const Vec128u8*)data);
        decrypt_block(data, round_key, num_rounds);
        simd::storeu((Vec128u8*)data, simd::loadu((const Vec128u8*)data) ^ ctx_iv);
        ctx_iv = tmp_iv;
    }
}
