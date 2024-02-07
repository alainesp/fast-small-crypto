//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA1 - Secure Hash Algorithm 1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SimdScalarType uint32_t
#include "simd.hpp"
using namespace simd;

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
    _mm_storeu_si128((__m128i*) state, ABCD);
    state[4] = _mm_extract_epi32(E0, 3);
}

