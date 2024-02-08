//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA256 - Secure Hash Algorithm 2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library
//
// Unit Testing

#define _CRT_SECURE_NO_WARNINGS
#include <gtest/gtest.h>
#include "sha256.h"
#include <wy.hpp>
#include "reference_implementation.cpp"

TEST(sha256, sha256_block_PLAIN_C)
{
	if (!simd::cpu_supports(simd::CpuFeatures::PLAIN_C))
		GTEST_SKIP() << "No PLAIN_C";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(uint32_t) / sizeof(uint32_t);

	uint32_t state[8 * parallelism];
	uint32_t state_simd[8 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t W[16 * parallelism];
	uint32_t W_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint32_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint32_t*>(state_simd)[j / 8 + (j % 8) * parallelism] = state[j];
		r.generate_stream<uint32_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha256_transform(state + j * 8, W + j * 16);
		sha256_block_plain_c(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 8 + (j % 8) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha256, sha256_block_SHANI)
{
	if (!simd::cpu_supports(simd::CpuFeatures::SHANI | simd::CpuFeatures::SSE41))
		GTEST_SKIP() << "No SHANI";

	constexpr size_t parallelism = 1;

	uint32_t state[8 * parallelism];
	uint32_t state_simd[8 * parallelism];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t W[16 * parallelism];
	uint32_t W_simd[16 * parallelism];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

	// Create a pseudo-random generator
	wy::rand r;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream<uint32_t>(state);
		memcpy(state_simd, state, sizeof(state)); // Copy values to simd
		r.generate_stream<uint32_t>(W);
		memcpy(W_simd, W, sizeof(W));             // Copy values to simd

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			sha256_transform(state + j * 8, W + j * 16);
		sha256_block_shani(state_simd, W_simd);

		// Compare results
		ASSERT_EQ(0, memcmp(state_simd, state, sizeof(state)));
	}
}
TEST(sha256, sha256_block_SHANI_x2)
{
	if (!simd::cpu_supports(simd::CpuFeatures::SHANI | simd::CpuFeatures::SSE41))
		GTEST_SKIP() << "No SHANI";

	constexpr size_t parallelism = 2;

	uint32_t state[8 * parallelism];
	uint32_t state_simd[8 * parallelism];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t W[16 * parallelism];
	uint32_t W_simd[16 * parallelism];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

	// Create a pseudo-random generator
	wy::rand r;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream<uint32_t>(state);
		memcpy(state_simd, state, sizeof(state)); // Copy values to simd
		r.generate_stream<uint32_t>(W);
		memcpy(W_simd, W, sizeof(W));             // Copy values to simd

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			sha256_transform(state + j * 8, W + j * 16);
		sha256_block_shani_x2(state_simd, W_simd);

		// Compare results
		ASSERT_EQ(0, memcmp(state_simd, state, sizeof(state)));
	}
}
TEST(sha256, sha256_block_SSE2)
{
	if (!simd::cpu_supports(simd::CpuFeatures::SSE2))
		GTEST_SKIP() << "No SSE2";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state[8 * parallelism];
	simd::Vec128u32 state_simd[8 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t W[16 * parallelism];
	simd::Vec128u32 W_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint32_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint32_t*>(state_simd)[j / 8 + (j % 8) * parallelism] = state[j];
		r.generate_stream<uint32_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha256_transform(state + j * 8, W + j * 16);
		sha256_block_sse2(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 8 + (j % 8) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha256, sha256_block_AVX)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX))
		GTEST_SKIP() << "No AVX";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state[8 * parallelism];
	simd::Vec128u32 state_simd[8 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t W[16 * parallelism];
	simd::Vec128u32 W_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint32_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint32_t*>(state_simd)[j / 8 + (j % 8) * parallelism] = state[j];
		r.generate_stream<uint32_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha256_transform(state + j * 8, W + j * 16);
		sha256_block_avx(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 8 + (j % 8) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha256, sha256_block_AVX2)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX2))
		GTEST_SKIP() << "No AVX2";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec256u32) / sizeof(uint32_t);

	uint32_t state[8 * parallelism];
	simd::Vec256u32 state_simd[8 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t W[16 * parallelism];
	simd::Vec256u32 W_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint32_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint32_t*>(state_simd)[j / 8 + (j % 8) * parallelism] = state[j];
		r.generate_stream<uint32_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha256_transform(state + j * 8, W + j * 16);
		sha256_block_avx2(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 8 + (j % 8) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha256, sha256_block_AVX512)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX512))
		GTEST_SKIP() << "No AVX512";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec512u32) / sizeof(uint32_t);

	uint32_t state[8 * parallelism];
	simd::Vec512u32 state_simd[8 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t W[16 * parallelism];
	simd::Vec512u32 W_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(W), sizeof(W_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint32_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint32_t*>(state_simd)[j / 8 + (j % 8) * parallelism] = state[j];
		r.generate_stream<uint32_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha256_transform(state + j * 8, W + j * 16);
		sha256_block_avx512(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 8 + (j % 8) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}

// SHA256 reference
#include "fsc.cpp"
static void copy_with_padding(uint8_t message[64], const char* text)
{
	size_t text_length = strlen(text);
	ASSERT_LT(text_length, 56);

	memcpy(message, text, text_length);
	message[text_length] = 0x80;
	memset(message + text_length + 1, 0, 64 - text_length - 1);
	reinterpret_cast<uint32_t*>(message)[15] = static_cast<uint32_t>(text_length) << 3;

	for (uint32_t i = 0; i < 14; i++)
		reinterpret_cast<uint32_t*>(message)[i] = byteswap32(reinterpret_cast<uint32_t*>(message)[i]);
}
TEST(sha256, reference)
{
	const uint32_t initial_state[] = { 0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A, 0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19 };
	uint32_t state[8];
	uint32_t message[16];
	char hex[65];

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), " ");
	sha256_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "36A9E7F1C95B82FFB99743E0C5C4CE95D83C9A430AAC59F84EF3CBFAB6145068" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "a");
	sha256_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "CA978112CA1BBDCAFAC231B39A23DC4DA786EFF8147C4E72B9807785AFEE48BB" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "abc");
	sha256_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "BA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "message digest");
	sha256_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "F7846F55CF23E14EEBEAB5B4E1550CAD5B509E3348FBC4EFA3A1413D393CB650" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "abcdefghijklmnopqrstuvwxyz");
	sha256_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "71C480DF93D6AE2F1EFAD1447C66C9525E316218CF51FC8D9ED832F2DAF18B73" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	memcpy(message, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\x80\x00", 64);
	for (uint32_t i = 0; i < 16; i++)
		message[i] = byteswap32(message[i]);
	sha256_transform(state, message);
	memset(message, 0, 64);
	message[15] = 62 << 3;
	sha256_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "DB4BFCBD4DA0CD85A60C3C37D3FBD8805C77F15FC6B1FDFE614EE0A7C8FDB4C0" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	memcpy(message, "1234567890123456789012345678901234567890123456789012345678901234", 64);
	for (uint32_t i = 0; i < 16; i++)
		message[i] = byteswap32(message[i]);
	sha256_transform(state, message);
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "5678901234567890");
	message[15] = 80 << 3;
	sha256_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 8; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "F371BC4A311F2B009EEF952DD83CA80E2B60026C8E935592D0F9C308453C813E" }, std::string{ hex });
}