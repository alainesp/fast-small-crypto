//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MD5 Message-Digest Algorithm
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library
//
// Unit Testing

#define _CRT_SECURE_NO_WARNINGS
#include <gtest/gtest.h>
#include "md5.h"
#include <wy.hpp>
#include "reference_implementation.cpp"

TEST(md5, md5_block_PLAIN_C)
{
	if (!simd::cpu_supports(simd::CpuFeatures::PLAIN_C))
		GTEST_SKIP() << "No PLAIN_C";

	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(uint32_t) / sizeof(uint32_t);

	uint32_t state[4 * parallelism];
	uint32_t state_simd[4 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t block[16 * parallelism];
	uint32_t block_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(block), sizeof(block_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint32_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism] = state[j];
		r.generate_stream<uint32_t>(block);
		// Copy values to simd
		for (size_t j = 0; j < std::size(block); j++)
			reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism] = block[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			md5_transform(state + j * 4, block + j * 16);
		md5_block_plain_c(state_simd, block_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(block); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism], block[j]);
    }
}
TEST(md5, md5_block_SSE2_x3)
{
	if (!simd::cpu_supports(simd::CpuFeatures::SSE2))
		GTEST_SKIP() << "No SSE2";

	constexpr size_t parallel_factor = 3;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state[4 * parallelism];
	simd::Vec128u32 state_simd[4 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t block[16 * parallelism];
	simd::Vec128u32 block_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(block), sizeof(block_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint32_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism] = state[j];
		r.generate_stream<uint32_t>(block);
		// Copy values to simd
		for (size_t j = 0; j < std::size(block); j++)
			reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism] = block[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			md5_transform(state + j * 4, block + j * 16);
		md5_block_sse2_x3(state_simd, block_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(block); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism], block[j]);
    }
}
TEST(md5, md5_block_AVX_x3)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX))
		GTEST_SKIP() << "No AVX";

	constexpr size_t parallel_factor = 3;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state[4 * parallelism];
	simd::Vec128u32 state_simd[4 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t block[16 * parallelism];
	simd::Vec128u32 block_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(block), sizeof(block_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint32_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism] = state[j];
		r.generate_stream<uint32_t>(block);
		// Copy values to simd
		for (size_t j = 0; j < std::size(block); j++)
			reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism] = block[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			md5_transform(state + j * 4, block + j * 16);
		md5_block_avx_x3(state_simd, block_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(block); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism], block[j]);
    }
}
TEST(md5, md5_block_AVX2_x3)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX2))
		GTEST_SKIP() << "No AVX2";

	constexpr size_t parallel_factor = 3;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec256u32) / sizeof(uint32_t);

	uint32_t state[4 * parallelism];
	simd::Vec256u32 state_simd[4 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t block[16 * parallelism];
	simd::Vec256u32 block_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(block), sizeof(block_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint32_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism] = state[j];
		r.generate_stream<uint32_t>(block);
		// Copy values to simd
		for (size_t j = 0; j < std::size(block); j++)
			reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism] = block[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			md5_transform(state + j * 4, block + j * 16);
		md5_block_avx2_x3(state_simd, block_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(block); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism], block[j]);
    }
}
TEST(md5, md5_block_AVX512_x4)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AVX512))
		GTEST_SKIP() << "No AVX512";

	constexpr size_t parallel_factor = 4;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec512u32) / sizeof(uint32_t);

	uint32_t state[4 * parallelism];
	simd::Vec512u32 state_simd[4 * parallel_factor];
	ASSERT_EQ(sizeof(state), sizeof(state_simd));
	uint32_t block[16 * parallelism];
	simd::Vec512u32 block_simd[16 * parallel_factor];
	ASSERT_EQ(sizeof(block), sizeof(block_simd));

    // Create a pseudo-random generator
    wy::rand r;

    for (size_t i = 0; i < 64; i++)
    {
		r.generate_stream<uint32_t>(state);
		// Copy values to simd
		for (size_t j = 0; j < std::size(state); j++)
			reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism] = state[j];
		r.generate_stream<uint32_t>(block);
		// Copy values to simd
		for (size_t j = 0; j < std::size(block); j++)
			reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism] = block[j];

        // Hash
        for (size_t j = 0; j < parallelism; j++)
			md5_transform(state + j * 4, block + j * 16);
		md5_block_avx512_x4(state_simd, block_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(block); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism], block[j]);
    }
}

// MD5 reference
#include "fsc.cpp"
static void copy_with_padding(uint8_t message[64], const char* text)
{
	size_t text_length = strlen(text);
	ASSERT_LT(text_length, 56);

	memcpy(message, text, text_length);
	message[text_length] = 0x80;
	memset(message + text_length + 1, 0, 64 - text_length - 1);
	reinterpret_cast<uint32_t*>(message)[14] = static_cast<uint32_t>(text_length) << 3;
}
TEST(md5, reference)
{
	const uint32_t initial_state[] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
	uint32_t state[4];
	uint32_t message[16];
	char hex[33];

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "");
	md5_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "D41D8CD98F00B204E9800998ECF8427E" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "a");
	md5_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "0CC175B9C0F1B6A831C399E269772661" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "abc");
	md5_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "900150983CD24FB0D6963F7D28E17F72" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "message digest");
	md5_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "F96B697D7CB7938D525A2F31AAF161D0" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "abcdefghijklmnopqrstuvwxyz");
	md5_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "C3FCD3D76192E4007DFB496CCA67E13B" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	memcpy(message, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\x80\x00", 64);
	md5_transform(state, message);
	memset(message, 0, 64);
	message[14] = 62 << 3;
	md5_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "D174AB98D277D9F5A5611C2C9F419D9F" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	memcpy(message, "1234567890123456789012345678901234567890123456789012345678901234", 64);
	md5_transform(state, message);
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "5678901234567890");
	message[14] = 80 << 3;
	md5_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "57EDF4A22BE3C955AC49DA2E2107B67A" }, std::string{ hex });
}
