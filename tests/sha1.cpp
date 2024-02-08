//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA1 - Secure Hash Algorithm 1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library
//
// Unit Testing

#define _CRT_SECURE_NO_WARNINGS
#include <gtest/gtest.h>
#include "sha1.h"
#include <wy.hpp>
#include "reference_implementation.cpp"

TEST(sha1, sha1_block_PLAIN_C)
{
	if (!simd::cpu_supports(simd::CpuFeatures::PLAIN_C))
		GTEST_SKIP() << "No PLAIN_C";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(uint32_t) / sizeof(uint32_t);

	uint32_t state[5 * parallelism];
	uint32_t state_simd[5 * parallel_factor];
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
			reinterpret_cast<uint32_t*>(state_simd)[j / 5 + (j % 5) * parallelism] = state[j];
		r.generate_stream<uint32_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha1_transform(state + j * 5, W + j * 16);
		sha1_block_plain_c(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 5 + (j % 5) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha1, sha1_block_SHANI)
{
	if (!simd::cpu_supports(simd::CpuFeatures::SHANI | simd::CpuFeatures::SSE41))
		GTEST_SKIP() << "No SHA-NI";

	constexpr size_t parallelism = 1;

	uint32_t state[5 * parallelism];
	uint32_t state_simd[5 * parallelism];
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
			sha1_transform(state + j * 5, W + j * 16);
		sha1_block_shani(state_simd, W_simd);

		// Compare results
		ASSERT_EQ(0, memcmp(state_simd, state, sizeof(state)));
	}
}
TEST(sha1, sha1_block_SHANI_x2)
{
	if (!simd::cpu_supports(simd::CpuFeatures::SHANI | simd::CpuFeatures::SSE41))
		GTEST_SKIP() << "No SHA-NI";

	constexpr size_t parallelism = 2;

	uint32_t state[5 * parallelism];
	uint32_t state_simd[5 * parallelism];
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
			sha1_transform(state + j * 5, W + j * 16);
		sha1_block_shani_x2(state_simd, W_simd);

		// Compare results
		ASSERT_EQ(0, memcmp(state_simd, state, sizeof(state)));
	}
}
TEST(sha1, sha1_block_SSE2)
{
	if (!simd::cpu_supports(simd::CpuFeatures::SSE2))
		GTEST_SKIP() << "No SSE2";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state[5 * parallelism];
	simd::Vec128u32 state_simd[5 * parallel_factor];
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
			reinterpret_cast<uint32_t*>(state_simd)[j / 5 + (j % 5) * parallelism] = state[j];
		r.generate_stream<uint32_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha1_transform(state + j * 5, W + j * 16);
		sha1_block_sse2(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 5 + (j % 5) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha1, sha1_block_AVX)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX))
		GTEST_SKIP() << "No AVX";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state[5 * parallelism];
	simd::Vec128u32 state_simd[5 * parallel_factor];
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
			reinterpret_cast<uint32_t*>(state_simd)[j / 5 + (j % 5) * parallelism] = state[j];
		r.generate_stream<uint32_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha1_transform(state + j * 5, W + j * 16);
		sha1_block_avx(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 5 + (j % 5) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha1, sha1_block_AVX2)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX2))
		GTEST_SKIP() << "No AVX2";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec256u32) / sizeof(uint32_t);

	uint32_t state[5 * parallelism];
	simd::Vec256u32 state_simd[5 * parallel_factor];
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
			reinterpret_cast<uint32_t*>(state_simd)[j / 5 + (j % 5) * parallelism] = state[j];
		r.generate_stream<uint32_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha1_transform(state + j * 5, W + j * 16);
		sha1_block_avx2(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 5 + (j % 5) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}
TEST(sha1, sha1_block_AVX512)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX512))
		GTEST_SKIP() << "No AVX512";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec512u32) / sizeof(uint32_t);

	uint32_t state[5 * parallelism];
	simd::Vec512u32 state_simd[5 * parallel_factor];
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
			reinterpret_cast<uint32_t*>(state_simd)[j / 5 + (j % 5) * parallelism] = state[j];
		r.generate_stream<uint32_t>(W);
		// Copy values to simd
		for (size_t j = 0; j < std::size(W); j++)
			reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism] = W[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			sha1_transform(state + j * 5, W + j * 16);
		sha1_block_avx512(state_simd, W_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 5 + (j % 5) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
    }
}

// SHA1 reference
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
TEST(sha1, reference)
{
	const uint32_t initial_state[] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xC3D2E1F0 };
	uint32_t state[5];
	uint32_t message[16];
	char hex[41];

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), " ");
	sha1_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 5; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "B858CB282617FB0956D960215C8E84D1CCF909C6" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "a");
	sha1_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 5; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "86F7E437FAA5A7FCE15D1DDCB9EAEAEA377667B8" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "abc");
	sha1_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 5; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "A9993E364706816ABA3E25717850C26C9CD0D89D" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "message digest");
	sha1_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 5; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "C12252CEDA8BE8994D5FA0290A47231C1D16AAE3" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "abcdefghijklmnopqrstuvwxyz");
	sha1_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 5; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "32D10C7B8CF96570CA04CE37F2A19D84240D3A89" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	memcpy(message, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\x80\x00", 64);
	for (uint32_t i = 0; i < 16; i++)
		message[i] = byteswap32(message[i]);
	sha1_transform(state, message);
	memset(message, 0, 64);
	message[15] = 62 << 3;
	sha1_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 5; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "761C457BF73B14D27E9E9265C46F4B4DDA11F940" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	memcpy(message, "1234567890123456789012345678901234567890123456789012345678901234", 64);
	for (uint32_t i = 0; i < 16; i++)
		message[i] = byteswap32(message[i]);
	sha1_transform(state, message);
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "5678901234567890");
	message[15] = 80 << 3;
	sha1_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 5; i++)
		sprintf(hex + strlen(hex), "%08X", state[i]);
	ASSERT_EQ(std::string{ "50ABF5706A150990A08B2C5EA40FA0E585554732" }, std::string{ hex });
}