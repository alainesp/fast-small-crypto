/////////////////////////////////////////////////////////////////////////////////
// This file is part of 'Fast-Small-Crypto'
// 
// Copyright (c) 2024 by Alain Espinosa.
/////////////////////////////////////////////////////////////////////////////////
// 
// AES supported sizes: 128, 192, 256
// 
// AES modes:
//		- CBC enables AES encryption in CBC-mode of operation.
//		- CTR enables encryption in counter-mode.
//		- ECB enables the basic ECB 16-byte block algorithm.

#include <cstring>
#include <cassert>
#include "aes.h"

// state - array holding the intermediate results during decryption.
typedef uint8_t state_t[4][4];

// The lookup-tables are marked const so they can be placed in read-only storage instead of RAM
// The numbers below can be computed dynamically trading ROM for RAM - 
// This can be useful in (embedded) bootloader applications, where ROM is often limited.
static const uint8_t sbox[256] = {
    //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};
static const uint8_t rsbox[256] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

// The round constant word array, Rcon[i], contains the values given by 
// x to the power (i-1) being powers of x (x is denoted as {02}) in the field GF(2^8)
static const uint8_t Rcon[11] = { 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };
/*
 * Jordan Goulder points out in PR #12 (https://github.com/kokke/tiny-AES-C/pull/12),
 * that you can remove most of the elements in the Rcon array, because they are unused.
 *
 * From Wikipedia's article on the Rijndael key schedule @ https://en.wikipedia.org/wiki/Rijndael_key_schedule#Rcon
 *
 * "Only the first some of these constants are actually used � up to rcon[10] for AES-128 (as 11 round keys are needed),
 *  up to rcon[8] for AES-192, up to rcon[7] for AES-256. rcon[0] is not used in AES algorithm."
 */

// This function produces 4*(Nr+1) round keys. The round keys are used in each round to decrypt the states. 
static void KeyExpansion(uint8_t* RoundKey, const uint8_t* Key, unsigned Nk, unsigned Nr) noexcept
{
    uint8_t tempa[4]; // Used for the column/row operations

    // The first round key is the key itself.
    for (unsigned i = 0; i < Nk; ++i)
    {
        RoundKey[(i * 4) + 0] = Key[(i * 4) + 0];
        RoundKey[(i * 4) + 1] = Key[(i * 4) + 1];
        RoundKey[(i * 4) + 2] = Key[(i * 4) + 2];
        RoundKey[(i * 4) + 3] = Key[(i * 4) + 3];
    }

    // All other round keys are found from the previous round keys.
    for (unsigned i = Nk; i < 4 * (Nr + 1); ++i)
    {
        {
            unsigned k = (i - 1) * 4;
            tempa[0] = RoundKey[k + 0];
            tempa[1] = RoundKey[k + 1];
            tempa[2] = RoundKey[k + 2];
            tempa[3] = RoundKey[k + 3];
        }

        if (i % Nk == 0)
        {
            // This function shifts the 4 bytes in a word to the left once.
            // [a0,a1,a2,a3] becomes [a1,a2,a3,a0]
            // Function RotWord()
            {
                const uint8_t u8tmp = tempa[0];
                tempa[0] = tempa[1];
                tempa[1] = tempa[2];
                tempa[2] = tempa[3];
                tempa[3] = u8tmp;
            }

            // SubWord() is a function that takes a four-byte input word and 
            // applies the S-box to each of the four bytes to produce an output word.

            // Function Subword()
            {
                tempa[0] = sbox[tempa[0]];
                tempa[1] = sbox[tempa[1]];
                tempa[2] = sbox[tempa[2]];
                tempa[3] = sbox[tempa[3]];
            }

            tempa[0] = tempa[0] ^ Rcon[i / Nk];
        }
//#if defined(AES256) && (AES256 == 1)
        if (Nk == 8 && i % Nk == 4)
        {
            // Function Subword()
            {
                tempa[0] = sbox[tempa[0]];
                tempa[1] = sbox[tempa[1]];
                tempa[2] = sbox[tempa[2]];
                tempa[3] = sbox[tempa[3]];
            }
        }
//#endif
        unsigned j = i * 4;
        unsigned k = (i - Nk) * 4;
        RoundKey[j + 0] = RoundKey[k + 0] ^ tempa[0];
        RoundKey[j + 1] = RoundKey[k + 1] ^ tempa[1];
        RoundKey[j + 2] = RoundKey[k + 2] ^ tempa[2];
        RoundKey[j + 3] = RoundKey[k + 3] ^ tempa[3];
    }
}

/////////////////////////////////////////////////////////////////////////////////
// AES main algorithm
/////////////////////////////////////////////////////////////////////////////////
static uint8_t xtime(uint8_t x) noexcept
{
    return ((x << 1) ^ (((x >> 7) & 1) * 0x1b));
}

// Cipher is the main function that encrypts the PlainText.
static void Cipher(state_t* state, const uint8_t* RoundKey, const uint8_t Nr) noexcept
{
    // Add the First round key to the state before starting the rounds.
    for (uint8_t i = 0; i < AES_BLOCKLEN; ++i)
        ((uint8_t*)state)[i] ^= RoundKey[i];

    // There will be Nr rounds.
    // The first Nr-1 rounds are identical.
    // These Nr rounds are executed in the loop below.
    // Last one without MixColumns()
    for (uint8_t round = 1; ; ++round)
    {
        // SubBytes substitutes the values in the state matrix with values in an S-box.
        for (uint8_t i = 0; i < AES_BLOCKLEN; ++i)
            ((uint8_t*)state)[i] = sbox[((uint8_t*)state)[i]];

        // ShiftRows() shifts the rows in the state to the left.
        // Each row is shifted with different offset.
        // Offset = Row number. So the first row is not shifted.
        {
            // Rotate first row 1 columns to left  
            uint8_t temp   = (*state)[0][1];
            (*state)[0][1] = (*state)[1][1];
            (*state)[1][1] = (*state)[2][1];
            (*state)[2][1] = (*state)[3][1];
            (*state)[3][1] = temp;

            // Rotate second row 2 columns to left  
            temp           = (*state)[0][2];
            (*state)[0][2] = (*state)[2][2];
            (*state)[2][2] = temp;

            temp           = (*state)[1][2];
            (*state)[1][2] = (*state)[3][2];
            (*state)[3][2] = temp;

            // Rotate third row 3 columns to left
            temp           = (*state)[0][3];
            (*state)[0][3] = (*state)[3][3];
            (*state)[3][3] = (*state)[2][3];
            (*state)[2][3] = (*state)[1][3];
            (*state)[1][3] = temp;
        }
        if (round == Nr)
            break;

        // MixColumns function mixes the columns of the state matrix
        {
            uint8_t Tmp, Tm, t;
            for (uint8_t i = 0; i < 4; ++i)
            {
                t   = (*state)[i][0];
                Tmp = (*state)[i][0] ^ (*state)[i][1] ^ (*state)[i][2] ^ (*state)[i][3];
                Tm  = (*state)[i][0] ^ (*state)[i][1]; Tm = xtime(Tm);  (*state)[i][0] ^= Tm ^ Tmp;
                Tm  = (*state)[i][1] ^ (*state)[i][2]; Tm = xtime(Tm);  (*state)[i][1] ^= Tm ^ Tmp;
                Tm  = (*state)[i][2] ^ (*state)[i][3]; Tm = xtime(Tm);  (*state)[i][2] ^= Tm ^ Tmp;
                Tm  = (*state)[i][3] ^ t;              Tm = xtime(Tm);  (*state)[i][3] ^= Tm ^ Tmp;
            }
        }
        for (uint8_t i = 0; i < AES_BLOCKLEN; ++i)
            ((uint8_t*)state)[i] ^= RoundKey[round * 16 + i];
    }
    // Add round key to last round
    for (uint8_t i = 0; i < AES_BLOCKLEN; ++i)
        ((uint8_t*)state)[i] ^= RoundKey[Nr * 16 + i];
}


// Multiply is used to multiply numbers in the field GF(2^8)
// Note: The last call to xtime() is unneeded, but often ends up generating a smaller binary
//       The compiler seems to be able to vectorize the operation better this way.
//       See https://github.com/kokke/tiny-AES-c/pull/34
#if MULTIPLY_AS_A_FUNCTION
static uint8_t Multiply(uint8_t x, uint8_t y) noexcept
{
    return (((y & 1) * x) ^
        ((y >> 1 & 1) * xtime(x)) ^
        ((y >> 2 & 1) * xtime(xtime(x))) ^
        ((y >> 3 & 1) * xtime(xtime(xtime(x)))) ^
        ((y >> 4 & 1) * xtime(xtime(xtime(xtime(x)))))); /* this last call to xtime() can be omitted */
}
#else
#define Multiply(x, y)                                \
      (  ((y & 1) * x) ^                              \
      ((y>>1 & 1) * xtime(x)) ^                       \
      ((y>>2 & 1) * xtime(xtime(x))) ^                \
      ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^         \
      ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))   \

#endif

static void InvCipher(state_t* state, const uint8_t* RoundKey, unsigned Nr) noexcept
{
    // Add the First round key to the state before starting the rounds.
    for (uint8_t i = 0; i < AES_BLOCKLEN; ++i)
        ((uint8_t*)state)[i] ^= RoundKey[Nr * 16 + i];

    // There will be Nr rounds.
    // The first Nr-1 rounds are identical.
    // These Nr rounds are executed in the loop below.
    // Last one without InvMixColumn()
    for (uint8_t round = (Nr - 1); ; --round)
    {
        //InvShiftRows(state);
        {
            // Rotate first row 1 columns to right  
            uint8_t temp   = (*state)[3][1];
            (*state)[3][1] = (*state)[2][1];
            (*state)[2][1] = (*state)[1][1];
            (*state)[1][1] = (*state)[0][1];
            (*state)[0][1] = temp;

            // Rotate second row 2 columns to right 
            temp           = (*state)[0][2];
            (*state)[0][2] = (*state)[2][2];
            (*state)[2][2] = temp;

            temp           = (*state)[1][2];
            (*state)[1][2] = (*state)[3][2];
            (*state)[3][2] = temp;

            // Rotate third row 3 columns to right
            temp           = (*state)[0][3];
            (*state)[0][3] = (*state)[1][3];
            (*state)[1][3] = (*state)[2][3];
            (*state)[2][3] = (*state)[3][3];
            (*state)[3][3] = temp;
        }

        // SubBytes() + AddRoundKey() substitutes the values in the state matrix with values in an S-box.
        for (uint8_t i = 0; i < AES_BLOCKLEN; ++i)
            ((uint8_t*)state)[i] = rsbox[((uint8_t*)state)[i]] ^ RoundKey[round * 16 + i];
        if (round == 0)
            break;

        // MixColumns() mixes the columns of the state matrix.
        // The method used to multiply may be difficult to understand for the inexperienced.
        // Please use the references to gain more information.
        for (int i = 0; i < 4; ++i)
        {
            uint8_t a = (*state)[i][0];
            uint8_t b = (*state)[i][1];
            uint8_t c = (*state)[i][2];
            uint8_t d = (*state)[i][3];

            (*state)[i][0] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
            (*state)[i][1] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
            (*state)[i][2] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
            (*state)[i][3] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
        }
    }
}


#define AES128_keyExpSize 176
#define AES192_keyExpSize 208
#define AES256_keyExpSize 240
/////////////////////////////////////////////////////////////////////////////////
// ECB
/////////////////////////////////////////////////////////////////////////////////
// buffer size is exactly AES_BLOCKLEN bytes; 
// you need only AES_init_ctx as IV is not used in ECB 
// NOTE: ECB is considered insecure for most uses
void AES_ECB_encrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length) noexcept
{
    assert(key_length == AES128_KEY_LENGTH || key_length == AES192_KEY_LENGTH || key_length == AES256_KEY_LENGTH);
    assert(data_length % AES_BLOCKLEN == 0);

    unsigned Nk = key_length / sizeof(uint32_t); // The number of 32 bit words in a key.
    unsigned Nr = Nk + 6;                        // The number of rounds in AES Cipher.

    uint8_t round_key[AES256_keyExpSize];
    KeyExpansion(round_key, key, Nk, Nr);
    for (size_t i = 0; i < data_length; i += AES_BLOCKLEN)
        Cipher((state_t*)(data + i), round_key, Nr);
}
void AES_ECB_decrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length) noexcept
{
    assert(key_length == AES128_KEY_LENGTH || key_length == AES192_KEY_LENGTH || key_length == AES256_KEY_LENGTH);
    assert(data_length % AES_BLOCKLEN == 0);

    unsigned Nk = key_length / sizeof(uint32_t); // The number of 32 bit words in a key.
    unsigned Nr = Nk + 6;                        // The number of rounds in AES Cipher.

    uint8_t round_key[AES256_keyExpSize];
    KeyExpansion(round_key, key, Nk, Nr);
    for (size_t i = 0; i < data_length; i += AES_BLOCKLEN)
        InvCipher((state_t*)(data + i), round_key, Nr);
}

/////////////////////////////////////////////////////////////////////////////////
// CBC
/////////////////////////////////////////////////////////////////////////////////
static void XorWithIv(uint8_t* buf, const uint8_t* Iv) noexcept
{
    for (uint8_t i = 0; i < AES_BLOCKLEN; ++i) // The block in AES is always 128bit no matter the key size
        buf[i] ^= Iv[i];
}
// data size MUST be multiple of AES_BLOCKLEN;
// Suggest https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
// NOTES: no IV should ever be reused with the same key 
void AES_CBC_encrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length, const uint8_t iv[AES_BLOCKLEN]) noexcept
{
    assert(key_length == AES128_KEY_LENGTH || key_length == AES192_KEY_LENGTH || key_length == AES256_KEY_LENGTH);
    assert(data_length % AES_BLOCKLEN == 0);

    unsigned Nk = key_length / sizeof(uint32_t); // The number of 32 bit words in a key.
    unsigned Nr = Nk + 6;                        // The number of rounds in AES Cipher.

    uint8_t round_key[AES256_keyExpSize];
    KeyExpansion(round_key, key, Nk, Nr);

    const uint8_t* current_iv = iv;
    for (size_t i = 0; i < data_length; i += AES_BLOCKLEN)
    {
        XorWithIv(data, current_iv);
        Cipher((state_t*)data, round_key, Nr);
        current_iv = data;
        data += AES_BLOCKLEN;
    }
    /* store Iv in ctx for next call */
    //memcpy(ctx_iv, current_iv, AES_BLOCKLEN);
}
void AES_CBC_decrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length, const uint8_t iv[AES_BLOCKLEN]) noexcept
{
    assert(key_length == AES128_KEY_LENGTH || key_length == AES192_KEY_LENGTH || key_length == AES256_KEY_LENGTH);
    assert(data_length % AES_BLOCKLEN == 0);

    unsigned Nk = key_length / sizeof(uint32_t); // The number of 32 bit words in a key.
    unsigned Nr = Nk + 6;                        // The number of rounds in AES Cipher.

    uint8_t round_key[AES256_keyExpSize];
    uint8_t ctx_iv[AES_BLOCKLEN];
    KeyExpansion(round_key, key, Nk, Nr);
    memcpy(ctx_iv, iv, AES_BLOCKLEN);

    uint8_t storeNextIv[AES_BLOCKLEN];
    for (size_t i = 0; i < data_length; i += AES_BLOCKLEN)
    {
        memcpy(storeNextIv, data, AES_BLOCKLEN);
        InvCipher((state_t*)data, round_key, Nr);
        XorWithIv(data, ctx_iv);
        memcpy(ctx_iv, storeNextIv, AES_BLOCKLEN);
        data += AES_BLOCKLEN;
    }
}

/////////////////////////////////////////////////////////////////////////////////
// CTR
/////////////////////////////////////////////////////////////////////////////////
// Same function for encrypting as for decrypting. 
// IV is incremented for every block, and used after encryption as XOR-compliment for output
// Suggesting https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
// NOTES: no IV should ever be reused with the same key 
void AES_CTR_xcrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length, const uint8_t iv[AES_BLOCKLEN]) noexcept
{
    assert(key_length == AES128_KEY_LENGTH || key_length == AES192_KEY_LENGTH || key_length == AES256_KEY_LENGTH);
    assert(data_length % AES_BLOCKLEN == 0);

    unsigned Nk = key_length / sizeof(uint32_t); // The number of 32 bit words in a key.
    unsigned Nr = Nk + 6;                        // The number of rounds in AES Cipher.

    uint8_t round_key[AES256_keyExpSize];
    uint8_t ctx_iv[AES_BLOCKLEN];
    KeyExpansion(round_key, key, Nk, Nr);
    memcpy(ctx_iv, iv, AES_BLOCKLEN);


    uint8_t buffer[AES_BLOCKLEN];

    size_t i;
    int bi;
    for (i = 0, bi = AES_BLOCKLEN; i < data_length; ++i, ++bi)
    {
        if (bi == AES_BLOCKLEN) /* we need to regen xor compliment in buffer */
        {
            memcpy(buffer, ctx_iv, AES_BLOCKLEN);
            Cipher((state_t*)buffer, round_key, Nr);

            /* Increment Iv and handle overflow */
            for (bi = (AES_BLOCKLEN - 1); bi >= 0; --bi)
            {
                /* inc will overflow */
                if (ctx_iv[bi] == 255)
                {
                    ctx_iv[bi] = 0;
                    continue;
                }
                ctx_iv[bi] += 1;
                break;
            }
            bi = 0;
        }

        data[i] = (data[i] ^ buffer[bi]);
    }
}
