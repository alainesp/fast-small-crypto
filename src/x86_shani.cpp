//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA-NI - Secure Hash Algorithm using CPU instruction
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SimdScalarType uint32_t
#include "simd.hpp"
using namespace simd;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA1 sha-ni implementation
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// SHA1 compress block
/// </summary>
/// <param name="state">The SHA1 state</param>
/// <param name="block">The message to compress</param>
extern "C" void sha1_block_shani(uint32_t state[5], const uint32_t W[16]) noexcept
{
    simd::Vec128u32 ABCD, ABCD_SAVE, E0, E1;
    simd::Vec128u32 MSG0, MSG1, MSG2, MSG3;
    uint32_t E0_SAVE;

    // Load initial values
    ABCD = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(state));
    ABCD_SAVE = ABCD = _mm_shuffle_epi32(ABCD, 0x1B);
    E0_SAVE = state[4];
    E0 = _mm_set_epi32(E0_SAVE, 0, 0, 0);

    // Load message
    MSG0 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 0));
    MSG0 = _mm_shuffle_epi32(MSG0, 0x1B);
    MSG1 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 4));
    MSG1 = _mm_shuffle_epi32(MSG1, 0x1B);
    MSG2 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 8));
    MSG2 = _mm_shuffle_epi32(MSG2, 0x1B);
    MSG3 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 12));
    MSG3 = _mm_shuffle_epi32(MSG3, 0x1B);

    // Rounds 0-3
    E0 += MSG0;
    E1 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);

    // Rounds 4-7
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 0);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);

    // Rounds 8-11
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 12-15
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 0);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 16-19
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 20-23
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 ^= MSG1;

    // Rounds 24-27
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 1);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 28-31
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 32-35
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 1);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 36-39
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 ^= MSG1;

    // Rounds 40-43
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 44-47
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 2);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 48-51
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 52-55
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 2);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 ^= MSG1;

    // Rounds 56-59
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 60-63
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 64-67
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 3);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 68-71
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);
    MSG3 ^= MSG1;

    // Rounds 72-75
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 3);

    // Rounds 76-79
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);

    // Combine state
    E0 = _mm_sha1nexte_epu32(E0, _mm_set_epi32(E0_SAVE, 0, 0, 0));
    ABCD += ABCD_SAVE;

    // Save state
    ABCD = _mm_shuffle_epi32(ABCD, 0x1B);
    simd::storeu(reinterpret_cast<simd::Vec128u32* SIMD_RESTRICT>(state), ABCD);
    state[4] = _mm_extract_epi32(E0, 3);
}

/// <summary>
/// SHA1 compress block
/// </summary>
/// <param name="state">The SHA1 state</param>
/// <param name="block">The message to compress</param>
extern "C" void sha1_block_shani_x2(uint32_t state[10], const uint32_t W[32]) noexcept
{
    simd::Vec128u32 ABCD, ABCD_SAVE, E0, E1;
    simd::Vec128u32 MSG0, MSG1, MSG2, MSG3;
    uint32_t E0_SAVE;

    // Load initial values
    ABCD = simd::loadu(reinterpret_cast<const simd::Vec128u32 * SIMD_RESTRICT>(state));
    ABCD_SAVE = ABCD = _mm_shuffle_epi32(ABCD, 0x1B);
    E0_SAVE = state[4];
    E0 = _mm_set_epi32(E0_SAVE, 0, 0, 0);

    // Load message
    MSG0 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 0));
    MSG0 = _mm_shuffle_epi32(MSG0, 0x1B);
    MSG1 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 4));
    MSG1 = _mm_shuffle_epi32(MSG1, 0x1B);
    MSG2 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 8));
    MSG2 = _mm_shuffle_epi32(MSG2, 0x1B);
    MSG3 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 12));
    MSG3 = _mm_shuffle_epi32(MSG3, 0x1B);

    // Rounds 0-3
    E0 += MSG0;
    E1 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);

    // Rounds 4-7
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 0);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);

    // Rounds 8-11
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 12-15
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 0);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 16-19
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 20-23
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 ^= MSG1;

    // Rounds 24-27
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 1);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 28-31
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 32-35
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 1);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 36-39
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 ^= MSG1;

    // Rounds 40-43
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 44-47
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 2);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 48-51
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 52-55
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 2);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 ^= MSG1;

    // Rounds 56-59
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 60-63
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 64-67
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 3);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 68-71
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);
    MSG3 ^= MSG1;

    // Rounds 72-75
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 3);

    // Rounds 76-79
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);

    // Combine state
    E0 = _mm_sha1nexte_epu32(E0, _mm_set_epi32(E0_SAVE, 0, 0, 0));
    ABCD += ABCD_SAVE;

    // Save state
    ABCD = _mm_shuffle_epi32(ABCD, 0x1B);
    simd::storeu(reinterpret_cast<simd::Vec128u32 * SIMD_RESTRICT>(state), ABCD);
    state[4] = _mm_extract_epi32(E0, 3);




    // Load initial values
    ABCD = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(state + 5));
    ABCD_SAVE = ABCD = _mm_shuffle_epi32(ABCD, 0x1B);
    E0_SAVE = state[9];
    E0 = _mm_set_epi32(E0_SAVE, 0, 0, 0);

    // Load message
    MSG0 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 16 + 0));
    MSG0 = _mm_shuffle_epi32(MSG0, 0x1B);
    MSG1 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 16 + 4));
    MSG1 = _mm_shuffle_epi32(MSG1, 0x1B);
    MSG2 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 16 + 8));
    MSG2 = _mm_shuffle_epi32(MSG2, 0x1B);
    MSG3 = simd::loadu(reinterpret_cast<const simd::Vec128u32* SIMD_RESTRICT>(W + 16 + 12));
    MSG3 = _mm_shuffle_epi32(MSG3, 0x1B);

    // Rounds 0-3
    E0 += MSG0;
    E1 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);

    // Rounds 4-7
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 0);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);

    // Rounds 8-11
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 12-15
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 0);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 16-19
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 20-23
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 ^= MSG1;

    // Rounds 24-27
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 1);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 28-31
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 32-35
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 1);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 36-39
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 ^= MSG1;

    // Rounds 40-43
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 44-47
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 2);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 48-51
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 52-55
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 2);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 ^= MSG1;

    // Rounds 56-59
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 ^= MSG2;

    // Rounds 60-63
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 ^= MSG3;

    // Rounds 64-67
    E0 = _mm_sha1nexte_epu32(E0, MSG0);
    E1 = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 3);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 ^= MSG0;

    // Rounds 68-71
    E1 = _mm_sha1nexte_epu32(E1, MSG1);
    E0 = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);
    MSG3 ^= MSG1;

    // Rounds 72-75
    E0 = _mm_sha1nexte_epu32(E0, MSG2);
    E1 = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 3);

    // Rounds 76-79
    E1 = _mm_sha1nexte_epu32(E1, MSG3);
    E0 = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);

    // Combine state
    E0 = _mm_sha1nexte_epu32(E0, _mm_set_epi32(E0_SAVE, 0, 0, 0));
    ABCD += ABCD_SAVE;

    // Save state
    ABCD = _mm_shuffle_epi32(ABCD, 0x1B);
    simd::storeu(reinterpret_cast<simd::Vec128u32* SIMD_RESTRICT>(state + 5), ABCD);
    state[9] = _mm_extract_epi32(E0, 3);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA256 sha-ni implementation
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "sha256_internal.h"

/// <summary>
/// SHA2 compress block
/// </summary>
/// <param name="state">The SHA2 state</param>
/// <param name="block">The message to compress</param>
extern "C" void sha256_block_shani(uint32_t state[8], const uint32_t W[16])
{
    Vec128u32 STATE0, STATE1, MSG0, MSG1, MSG2, MSG3;
    Vec128u32 MSG, TMP; // tmps

    /* Load initial values */
    TMP    = simd::loadu((const Vec128u32* SIMD_RESTRICT)(state + 0));
    STATE1 = simd::loadu((const Vec128u32* SIMD_RESTRICT)(state + 4));

    TMP    = _mm_shuffle_epi32(TMP, 0xB1);       // CDAB ->
    STATE1 = _mm_shuffle_epi32(STATE1, 0x1B);    // EFGH ->
    STATE0 = _mm_alignr_epi8(TMP, STATE1, 8);    // ABEF -> SSSE3
    STATE1 = _mm_blend_epi16(STATE1, TMP, 0xF0); // CDGH -> SSE4.1

    // Load message
    MSG0 = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W +  0));
    MSG1 = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W +  4));
    MSG2 = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W +  8));
    MSG3 = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W + 12));

    /* Rounds 0-3 */
    MSG    = MSG0 + simd::load(((const Vec128u32*)sha256_consts) + 0);
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);

    /* Rounds 4-7 */
    MSG    = MSG1 + simd::load(((const Vec128u32*)sha256_consts) + 1);
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG0   = _mm_sha256msg1_epu32(MSG0, MSG1);

    /* Rounds 8-11 */
    MSG    = MSG2 + simd::load(((const Vec128u32*)sha256_consts) + 2);
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG1   = _mm_sha256msg1_epu32(MSG1, MSG2);

    /* Rounds 12-59 */
    for (int i = 3; i < 12; i += 4)
    {
        /* Rounds 12-15 */
        MSG    = MSG3 + simd::load(((const Vec128u32*)sha256_consts) + i + 0);
        STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
        TMP    = _mm_alignr_epi8(MSG3, MSG2, 4);
        MSG0  += TMP;
        MSG0   = _mm_sha256msg2_epu32(MSG0, MSG3);
        MSG    = _mm_shuffle_epi32(MSG, 0x0E);
        STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
        MSG2   = _mm_sha256msg1_epu32(MSG2, MSG3);

        /* Rounds 16-19 */
        MSG    = MSG0 + simd::load(((const Vec128u32*)sha256_consts) + i + 1);
        STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
        TMP    = _mm_alignr_epi8(MSG0, MSG3, 4);
        MSG1  += TMP;
        MSG1   = _mm_sha256msg2_epu32(MSG1, MSG0);
        MSG    = _mm_shuffle_epi32(MSG, 0x0E);
        STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
        MSG3   = _mm_sha256msg1_epu32(MSG3, MSG0);

        /* Rounds 20-23 */
        MSG    = MSG1 + simd::load(((const Vec128u32*)sha256_consts) + i + 2);
        STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
        TMP    = _mm_alignr_epi8(MSG1, MSG0, 4);
        MSG2  += TMP;
        MSG2   = _mm_sha256msg2_epu32(MSG2, MSG1);
        MSG    = _mm_shuffle_epi32(MSG, 0x0E);
        STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
        MSG0   = _mm_sha256msg1_epu32(MSG0, MSG1);

        /* Rounds 24-27 */
        MSG    = MSG2 + simd::load(((const Vec128u32*)sha256_consts) + i + 3);
        STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
        TMP    = _mm_alignr_epi8(MSG2, MSG1, 4);
        MSG3   += TMP;
        MSG3   = _mm_sha256msg2_epu32(MSG3, MSG2);
        MSG    = _mm_shuffle_epi32(MSG, 0x0E);
        STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
        MSG1   = _mm_sha256msg1_epu32(MSG1, MSG2); // NOTE: can be eliminated in last iteration
    }

    /* Rounds 60-63 */
    MSG    = MSG3 + simd::load(((const Vec128u32*)sha256_consts) + 15);
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);

    // Align dwords
    TMP    = _mm_shuffle_epi32(STATE0, 0x1B);    // FEBA
    STATE1 = _mm_shuffle_epi32(STATE1, 0xB1);    // DCHG
    STATE0 = _mm_blend_epi16(TMP, STATE1, 0xF0); // DCBA
    STATE1 = _mm_alignr_epi8(STATE1, TMP, 8);    // ABEF

    // Combine state
    STATE0 += simd::loadu((const Vec128u32* SIMD_RESTRICT)(state + 0));
    STATE1 += simd::loadu((const Vec128u32* SIMD_RESTRICT)(state + 4));

    // Save state
    simd::storeu((Vec128u32* SIMD_RESTRICT)(state + 0), STATE0);
    simd::storeu((Vec128u32* SIMD_RESTRICT)(state + 4), STATE1);
}

/// <summary>
/// SHA2 compress block
/// </summary>
/// <param name="state">The SHA2 state</param>
/// <param name="block">The message to compress</param>
extern "C" void sha256_block_shani_x2(uint32_t state[16], const uint32_t W[32])
{
    Vec128u32 STATE0, STATE1, MSG0, MSG1, MSG2, MSG3;
    Vec128u32 MSG, TMP;    // tmps
    Vec128u32 STATE0_2, STATE1_2, MSG0_2, MSG1_2, MSG2_2, MSG3_2;
    Vec128u32 MSG_2, TMP_2; // tmps

    // Load initial values
    TMP      = simd::loadu((const Vec128u32* SIMD_RESTRICT)(state +  0));
    STATE1   = simd::loadu((const Vec128u32* SIMD_RESTRICT)(state +  4));
    TMP_2    = simd::loadu((const Vec128u32* SIMD_RESTRICT)(state +  8));
    STATE1_2 = simd::loadu((const Vec128u32* SIMD_RESTRICT)(state + 12));

    TMP      = _mm_shuffle_epi32(TMP  , 0xB1);         // CDAB
    TMP_2    = _mm_shuffle_epi32(TMP_2, 0xB1);         // CDAB
    STATE1   = _mm_shuffle_epi32(STATE1  , 0x1B);      // EFGH
    STATE1_2 = _mm_shuffle_epi32(STATE1_2, 0x1B);      // EFGH
    STATE0   = _mm_alignr_epi8(TMP  , STATE1  , 8);    // ABEF -> SSSE3
    STATE0_2 = _mm_alignr_epi8(TMP_2, STATE1_2, 8);    // ABEF -> SSSE3
    STATE1   = _mm_blend_epi16(STATE1  , TMP  , 0xF0); // CDGH -> SSE4.1
    STATE1_2 = _mm_blend_epi16(STATE1_2, TMP_2, 0xF0); // CDGH -> SSE4.1

    // Load message
    MSG0   = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W +  0));
    MSG1   = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W +  4));
    MSG2   = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W +  8));
    MSG3   = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W + 12));
    MSG0_2 = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W + 16));
    MSG1_2 = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W + 20));
    MSG2_2 = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W + 24));
    MSG3_2 = simd::loadu((const Vec128u32* SIMD_RESTRICT)(W + 28));

    /* Rounds 0-3 */
    MSG      = MSG0   + simd::load(((const Vec128u32*)sha256_consts) + 0);
    MSG_2    = MSG0_2 + simd::load(((const Vec128u32*)sha256_consts) + 0);
    STATE1   = _mm_sha256rnds2_epu32(STATE1  , STATE0  , MSG  );
    STATE1_2 = _mm_sha256rnds2_epu32(STATE1_2, STATE0_2, MSG_2);
    MSG      = _mm_shuffle_epi32(MSG  , 0x0E);
    MSG_2    = _mm_shuffle_epi32(MSG_2, 0x0E);
    STATE0   = _mm_sha256rnds2_epu32(STATE0  , STATE1  , MSG  );
    STATE0_2 = _mm_sha256rnds2_epu32(STATE0_2, STATE1_2, MSG_2);

    /* Rounds 4-7 */
    MSG      = MSG1   + simd::load(((const Vec128u32*)sha256_consts) + 1);
    MSG_2    = MSG1_2 + simd::load(((const Vec128u32*)sha256_consts) + 1);
    STATE1   = _mm_sha256rnds2_epu32(STATE1  , STATE0  , MSG  );
    STATE1_2 = _mm_sha256rnds2_epu32(STATE1_2, STATE0_2, MSG_2);
    MSG      = _mm_shuffle_epi32(MSG  , 0x0E);
    MSG_2    = _mm_shuffle_epi32(MSG_2, 0x0E);
    STATE0   = _mm_sha256rnds2_epu32(STATE0  , STATE1  , MSG  );
    STATE0_2 = _mm_sha256rnds2_epu32(STATE0_2, STATE1_2, MSG_2);
    MSG0     = _mm_sha256msg1_epu32(MSG0  , MSG1  );
    MSG0_2   = _mm_sha256msg1_epu32(MSG0_2, MSG1_2);

    /* Rounds 8-11 */
    MSG      = MSG2   + simd::load(((const Vec128u32*)sha256_consts) + 2);
    MSG_2    = MSG2_2 + simd::load(((const Vec128u32*)sha256_consts) + 2);
    STATE1   = _mm_sha256rnds2_epu32(STATE1  , STATE0  , MSG  );
    STATE1_2 = _mm_sha256rnds2_epu32(STATE1_2, STATE0_2, MSG_2);
    MSG      = _mm_shuffle_epi32(MSG  , 0x0E);
    MSG_2    = _mm_shuffle_epi32(MSG_2, 0x0E);
    STATE0   = _mm_sha256rnds2_epu32(STATE0  , STATE1  , MSG  );
    STATE0_2 = _mm_sha256rnds2_epu32(STATE0_2, STATE1_2, MSG_2);
    MSG1     = _mm_sha256msg1_epu32(MSG1  , MSG2  );
    MSG1_2   = _mm_sha256msg1_epu32(MSG1_2, MSG2_2);

    /* Rounds 12-59*/
    for (int i = 3; i < 12; i += 4)
    {
        /* Rounds 12-15 */
        MSG      = MSG3   + simd::load(((const Vec128u32*)sha256_consts) + i + 0);
        MSG_2    = MSG3_2 + simd::load(((const Vec128u32*)sha256_consts) + i + 0);
        STATE1   = _mm_sha256rnds2_epu32(STATE1  , STATE0  , MSG  );
        STATE1_2 = _mm_sha256rnds2_epu32(STATE1_2, STATE0_2, MSG_2);
        TMP      = _mm_alignr_epi8(MSG3  , MSG2  , 4);
        TMP_2    = _mm_alignr_epi8(MSG3_2, MSG2_2, 4);
        MSG0    += TMP;
        MSG0_2  += TMP_2;
        MSG0     = _mm_sha256msg2_epu32(MSG0  , MSG3  );
        MSG0_2   = _mm_sha256msg2_epu32(MSG0_2, MSG3_2);
        MSG      = _mm_shuffle_epi32(MSG  , 0x0E);
        MSG_2    = _mm_shuffle_epi32(MSG_2, 0x0E);
        STATE0   = _mm_sha256rnds2_epu32(STATE0  , STATE1  , MSG  );
        STATE0_2 = _mm_sha256rnds2_epu32(STATE0_2, STATE1_2, MSG_2);
        MSG2     = _mm_sha256msg1_epu32(MSG2  , MSG3  );
        MSG2_2   = _mm_sha256msg1_epu32(MSG2_2, MSG3_2);

        /* Rounds 16-19 */
        MSG      = MSG0   + simd::load(((const Vec128u32*)sha256_consts) + i + 1);
        MSG_2    = MSG0_2 + simd::load(((const Vec128u32*)sha256_consts) + i + 1);
        STATE1   = _mm_sha256rnds2_epu32(STATE1  , STATE0  , MSG  );
        STATE1_2 = _mm_sha256rnds2_epu32(STATE1_2, STATE0_2, MSG_2);
        TMP      = _mm_alignr_epi8(MSG0  , MSG3  , 4);
        TMP_2    = _mm_alignr_epi8(MSG0_2, MSG3_2, 4);
        MSG1    += TMP;
        MSG1_2  += TMP_2;
        MSG1     = _mm_sha256msg2_epu32(MSG1  , MSG0  );
        MSG1_2   = _mm_sha256msg2_epu32(MSG1_2, MSG0_2);
        MSG      = _mm_shuffle_epi32(MSG  , 0x0E);
        MSG_2    = _mm_shuffle_epi32(MSG_2, 0x0E);
        STATE0   = _mm_sha256rnds2_epu32(STATE0  , STATE1  , MSG  );
        STATE0_2 = _mm_sha256rnds2_epu32(STATE0_2, STATE1_2, MSG_2);
        MSG3     = _mm_sha256msg1_epu32(MSG3  , MSG0  );
        MSG3_2   = _mm_sha256msg1_epu32(MSG3_2, MSG0_2);

        /* Rounds 20-23 */
        MSG      = MSG1   + simd::load(((const Vec128u32*)sha256_consts) + i + 2);
        MSG_2    = MSG1_2 + simd::load(((const Vec128u32*)sha256_consts) + i + 2);
        STATE1   = _mm_sha256rnds2_epu32(STATE1  , STATE0  , MSG  );
        STATE1_2 = _mm_sha256rnds2_epu32(STATE1_2, STATE0_2, MSG_2);
        TMP      = _mm_alignr_epi8(MSG1  , MSG0  , 4);
        TMP_2    = _mm_alignr_epi8(MSG1_2, MSG0_2, 4);
        MSG2    += TMP;
        MSG2_2  += TMP_2;
        MSG2     = _mm_sha256msg2_epu32(MSG2  , MSG1  );
        MSG2_2   = _mm_sha256msg2_epu32(MSG2_2, MSG1_2);
        MSG      = _mm_shuffle_epi32(MSG  , 0x0E);
        MSG_2    = _mm_shuffle_epi32(MSG_2, 0x0E);
        STATE0   = _mm_sha256rnds2_epu32(STATE0  , STATE1  , MSG  );
        STATE0_2 = _mm_sha256rnds2_epu32(STATE0_2, STATE1_2, MSG_2);
        MSG0     = _mm_sha256msg1_epu32(MSG0  , MSG1  );
        MSG0_2   = _mm_sha256msg1_epu32(MSG0_2, MSG1_2);

        /* Rounds 24-27 */
        MSG      = MSG2   + simd::load(((const Vec128u32*)sha256_consts) + i + 3);
        MSG_2    = MSG2_2 + simd::load(((const Vec128u32*)sha256_consts) + i + 3);
        STATE1   = _mm_sha256rnds2_epu32(STATE1  , STATE0  , MSG  );
        STATE1_2 = _mm_sha256rnds2_epu32(STATE1_2, STATE0_2, MSG_2);
        TMP      = _mm_alignr_epi8(MSG2  , MSG1  , 4);
        TMP_2    = _mm_alignr_epi8(MSG2_2, MSG1_2, 4);
        MSG3     += TMP;
        MSG3_2   += TMP_2;
        MSG3     = _mm_sha256msg2_epu32(MSG3  , MSG2  );
        MSG3_2   = _mm_sha256msg2_epu32(MSG3_2, MSG2_2);
        MSG      = _mm_shuffle_epi32(MSG  , 0x0E);
        MSG_2    = _mm_shuffle_epi32(MSG_2, 0x0E);
        STATE0   = _mm_sha256rnds2_epu32(STATE0  , STATE1  , MSG  );
        STATE0_2 = _mm_sha256rnds2_epu32(STATE0_2, STATE1_2, MSG_2);
        MSG1     = _mm_sha256msg1_epu32(MSG1  , MSG2  ); // NOTE: can be eliminated in last iteration
        MSG1_2   = _mm_sha256msg1_epu32(MSG1_2, MSG2_2); // NOTE: can be eliminated in last iteration
    }

    /* Rounds 60-63*/
    MSG      = MSG3   + simd::load(((const Vec128u32*)sha256_consts) + 15);
    MSG_2    = MSG3_2 + simd::load(((const Vec128u32*)sha256_consts) + 15);
    STATE1   = _mm_sha256rnds2_epu32(STATE1  , STATE0  , MSG  );
    STATE1_2 = _mm_sha256rnds2_epu32(STATE1_2, STATE0_2, MSG_2);
    MSG      = _mm_shuffle_epi32(MSG  , 0x0E);
    MSG_2    = _mm_shuffle_epi32(MSG_2, 0x0E);
    STATE0   = _mm_sha256rnds2_epu32(STATE0  , STATE1  , MSG  );
    STATE0_2 = _mm_sha256rnds2_epu32(STATE0_2, STATE1_2, MSG_2);

    // Align dwords
    TMP      = _mm_shuffle_epi32(STATE0  , 0x1B);      // FEBA
    TMP_2    = _mm_shuffle_epi32(STATE0_2, 0x1B);      // FEBA
    STATE1   = _mm_shuffle_epi32(STATE1  , 0xB1);      // DCHG
    STATE1_2 = _mm_shuffle_epi32(STATE1_2, 0xB1);      // DCHG
    STATE0   = _mm_blend_epi16(TMP  , STATE1  , 0xF0); // DCBA
    STATE0_2 = _mm_blend_epi16(TMP_2, STATE1_2, 0xF0); // DCBA
    STATE1   = _mm_alignr_epi8(STATE1  , TMP  , 8);    // ABEF
    STATE1_2 = _mm_alignr_epi8(STATE1_2, TMP_2, 8);    // ABEF

    // Combine state
    STATE0   += simd::loadu((const Vec128u32* SIMD_RESTRICT)(state +  0));
    STATE1   += simd::loadu((const Vec128u32* SIMD_RESTRICT)(state +  4));
    STATE0_2 += simd::loadu((const Vec128u32* SIMD_RESTRICT)(state +  8));
    STATE1_2 += simd::loadu((const Vec128u32* SIMD_RESTRICT)(state + 12));

    // Save state
    simd::storeu((Vec128u32* SIMD_RESTRICT)(state +  0), STATE0);
    simd::storeu((Vec128u32* SIMD_RESTRICT)(state +  4), STATE1);
    simd::storeu((Vec128u32* SIMD_RESTRICT)(state +  8), STATE0_2);
    simd::storeu((Vec128u32* SIMD_RESTRICT)(state + 12), STATE1_2);
}

