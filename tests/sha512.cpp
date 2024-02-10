//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA512 - Secure Hash Algorithm 2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library
//
// Unit Testing

#define _CRT_SECURE_NO_WARNINGS
#include <gtest/gtest.h>
#include "sha512.h"
#include <wy.hpp>
#include "reference_implementation.cpp"

TEST(sha512, sha512_block_PLAIN_C)
{
	if (!simd::cpu_supports(simd::CpuFeatures::PLAIN_C))
		GTEST_SKIP() << "No PLAIN_C";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(uint64_t) / sizeof(uint64_t);

	uint64_t state[8 * parallelism];
	uint64_t state_simd[8 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint64_t W[16 * parallelism];
	uint64_t W_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint64_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint64_t*>(state_simd)[j / 8 + (j % 8) * parallelism] = state[j];
		r.generate_stream<uint64_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint64_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha512_transform(state + j * 8, W + j * 16);
		sha512_block_plain_c(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint64_t*>(state_simd)[j / 8 + (j % 8) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint64_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha512, sha512_block_SSE2)
{
	if (!simd::cpu_supports(simd::CpuFeatures::SSE2))
		GTEST_SKIP() << "No SSE2";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u64) / sizeof(uint64_t);

	uint64_t state[8 * parallelism];
	simd::Vec128u64 state_simd[8 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint64_t W[16 * parallelism];
	simd::Vec128u64 W_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint64_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint64_t*>(state_simd)[j / 8 + (j % 8) * parallelism] = state[j];
		r.generate_stream<uint64_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint64_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha512_transform(state + j * 8, W + j * 16);
		sha512_block_sse2(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint64_t*>(state_simd)[j / 8 + (j % 8) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint64_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha512, sha512_block_AVX)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX))
		GTEST_SKIP() << "No AVX";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u64) / sizeof(uint64_t);

	uint64_t state[8 * parallelism];
	simd::Vec128u64 state_simd[8 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint64_t W[16 * parallelism];
	simd::Vec128u64 W_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint64_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint64_t*>(state_simd)[j / 8 + (j % 8) * parallelism] = state[j];
		r.generate_stream<uint64_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint64_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha512_transform(state + j * 8, W + j * 16);
		sha512_block_avx(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint64_t*>(state_simd)[j / 8 + (j % 8) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint64_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha512, sha512_block_AVX2)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX2))
		GTEST_SKIP() << "No AVX2";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec256u64) / sizeof(uint64_t);

	uint64_t state[8 * parallelism];
	simd::Vec256u64 state_simd[8 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint64_t W[16 * parallelism];
	simd::Vec256u64 W_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint64_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint64_t*>(state_simd)[j / 8 + (j % 8) * parallelism] = state[j];
		r.generate_stream<uint64_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint64_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha512_transform(state + j * 8, W + j * 16);
		sha512_block_avx2(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint64_t*>(state_simd)[j / 8 + (j % 8) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint64_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha512, sha512_block_AVX512)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX512))
		GTEST_SKIP() << "No AVX512";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec512u64) / sizeof(uint64_t);

	uint64_t state[8 * parallelism];
	simd::Vec512u64 state_simd[8 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint64_t W[16 * parallelism];
	simd::Vec512u64 W_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint64_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint64_t*>(state_simd)[j / 8 + (j % 8) * parallelism] = state[j];
		r.generate_stream<uint64_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint64_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha512_transform(state + j * 8, W + j * 16);
		sha512_block_avx512(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint64_t*>(state_simd)[j / 8 + (j % 8) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint64_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}

// SHA512 reference
#include "byteswap.h"
static void copy_with_padding(uint8_t message[128], const char* text)
{
	size_t text_length = strlen(text);
	ASSERT_LT(text_length, 112);

	memcpy(message, text, text_length);
	message[text_length] = 0x80;
	memset(message + text_length + 1, 0, 128 - text_length - 1);
	reinterpret_cast<uint64_t*>(message)[15] = static_cast<uint64_t>(text_length) << 3;

	for (uint32_t i = 0; i < 14; i++)
		reinterpret_cast<uint64_t*>(message)[i] = byteswap64(reinterpret_cast<uint64_t*>(message)[i]);
}
TEST(sha512, reference)
{
	const uint64_t initial_state[] = { 
		0x6A09E667F3BCC908ULL, 0xBB67AE8584CAA73BULL, 0x3C6EF372FE94F82BULL, 0xA54FF53A5F1D36F1ULL,
		0x510E527FADE682D1ULL, 0x9B05688C2B3E6C1FULL, 0x1F83D9ABFB41BD6BULL, 0x5BE0CD19137E2179ULL
	};
	uint64_t state[8];
	uint64_t message[16];
	char hex[129];

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), " ");
	sha512_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%016llX", state[i]);
	ASSERT_EQ(std::string{ "F90DDD77E400DFE6A3FCF479B00B1EE29E7015C5BB8CD70F5F15B4886CC339275FF553FC8A053F8DDC7324F45168CFFAF81F8C3AC93996F6536EEF38E5E40768" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "a");
	sha512_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%016llX", state[i]);
	ASSERT_EQ(std::string{ "1F40FC92DA241694750979EE6CF582F2D5D7D28E18335DE05ABC54D0560E0F5302860C652BF08D560252AA5E74210546F369FBBBCE8C12CFC7957B2652FE9A75" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "abc");
	sha512_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%016llX", state[i]);
	ASSERT_EQ(std::string{ "DDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "message digest");
	sha512_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%016llX", state[i]);
	ASSERT_EQ(std::string{ "107DBF389D9E9F71A3A95F6C055B9251BC5268C2BE16D6C13492EA45B0199F3309E16455AB1E96118E8A905D5597B72038DDB372A89826046DE66687BB420E7C" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "abcdefghijklmnopqrstuvwxyz");
	sha512_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%016llX", state[i]);
	ASSERT_EQ(std::string{ "4DBFF86CC2CA1BAE1E16468A05CB9881C97F1753BCE3619034898FAA1AABE429955A1BF8EC483D7421FE3C1646613A59ED5441FB0F321389F77F48A879C7B1F1" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	sha512_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%016llX", state[i]);
	ASSERT_EQ(std::string{ "1E07BE23C26A86EA37EA810C8EC7809352515A970E9253C26F536CFC7A9996C45C8370583E0A78FA4A90041D71A4CEAB7423F19C71B9D5A3E01249F0BEBD5894" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
	sha512_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%016llX", state[i]);
	ASSERT_EQ(std::string{ "72EC1EF1124A45B047E8B7C75A932195135BB61DE24EC0D1914042246E0AEC3A2354E093D76F3048B456764346900CB130D2A4FD5DD16ABB5E30BCB850DEE843" }, std::string{ hex });
}