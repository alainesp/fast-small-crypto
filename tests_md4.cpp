/////////////////////////////////////////////////////////////////////////////////
// This file is part of 'Fast-Small-Crypto'
// 
// Copyright (c) 2024 by Alain Espinosa.
/////////////////////////////////////////////////////////////////////////////////

// Include the required header
#include <gtest/gtest.h>
#include <string>
#include <wy.hpp>
#include "fsc.cpp"

/////////////////////////////////////////////////////////////////////////////////
/// MD4
/////////////////////////////////////////////////////////////////////////////////
#include "reference_implementation.c"

static void copy_with_padding(uint8_t message[64], const char* text)
{
	size_t text_length = strlen(text);
	ASSERT_LT(text_length, 56);

	memcpy(message, text, text_length);
	message[text_length] = 0x80;
	memset(message + text_length + 1, 0, 64 - text_length - 1);
	reinterpret_cast<uint32_t*>(message)[14] = static_cast<uint32_t>(text_length) << 3;
}
TEST(md4, reference)
{
	const uint32_t initial_state[] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
	uint32_t state[4];
	uint32_t message[16];
	char hex[33];

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "");
	md4_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "31D6CFE0D16AE931B73C59D7E0C089C0" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "a");
	md4_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "BDE52CB31DE33E46245E05FBDBD6FB24" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "abc");
	md4_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "A448017AAF21D8525FC10AE87AA6729D" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "message digest");
	md4_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "D9130A8164549FE818874806E1C7014B" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "abcdefghijklmnopqrstuvwxyz");
	md4_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "D79E1C308AA5BBCDEEA8ED63DF412DA9" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	memcpy(message, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\x80\x00", 64);
	md4_transform(state, message);
	memset(message, 0, 64);
	message[14] = 62 << 3;
	md4_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "043F8582F241DB351CE627E153E7F0E4" }, std::string{ hex });

	memcpy(state, initial_state, sizeof(initial_state));
	memcpy(message, "1234567890123456789012345678901234567890123456789012345678901234", 64);
	md4_transform(state, message);
	copy_with_padding(reinterpret_cast<uint8_t*>(message), "5678901234567890");
	message[14] = 80 << 3;
	md4_transform(state, message);
	hex[0] = 0;
	for (uint32_t i = 0; i < 4; i++)
		sprintf(hex + strlen(hex), "%08X", byteswap32(state[i]));
	ASSERT_EQ(std::string{ "E33B4DDC9C38F2199C3E7B164FCC0536" }, std::string{ hex });
}

#include <md4.h>

TEST(md4, plain_c)
{
	uint32_t state0[4];
	uint32_t state1[4];
	uint32_t message0[16];
	uint32_t message1[16];

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + 4, state0);
		std::copy(random_values.cbegin(), random_values.cbegin() + 4, state1);
		std::copy(random_values.cbegin() + 4, random_values.cend(), message0);
		std::copy(random_values.cbegin() + 4, random_values.cend(), message1);

		md4_transform(state0, message0);
		md4_block_plain_c(state1, message1);

		ASSERT_EQ(0, memcmp(state0, state1, sizeof(state0)));
	}
}

// SSE2
TEST(md4, md4_block_SSE2_x1)
{
	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec128u32 state1[4 * parallel_factor];
	simd::Vec128u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_sse2_x1(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_SSE2_x2)
{
	constexpr size_t parallel_factor = 2;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec128u32 state1[4 * parallel_factor];
	simd::Vec128u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_sse2_x2(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_SSE2_x3)
{
	constexpr size_t parallel_factor = 3;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec128u32 state1[4 * parallel_factor];
	simd::Vec128u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_sse2_x3(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_SSE2_x4)
{
	constexpr size_t parallel_factor = 4;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec128u32 state1[4 * parallel_factor];
	simd::Vec128u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_sse2_x4(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
// AVX
TEST(md4, md4_block_AVX_x1)
{
	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec128u32 state1[4 * parallel_factor];
	simd::Vec128u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx_x1(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_AVX_x2)
{
	constexpr size_t parallel_factor = 2;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec128u32 state1[4 * parallel_factor];
	simd::Vec128u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx_x2(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_AVX_x3)
{
	constexpr size_t parallel_factor = 3;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec128u32 state1[4 * parallel_factor];
	simd::Vec128u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx_x3(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_AVX_x4)
{
	constexpr size_t parallel_factor = 4;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec128u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec128u32 state1[4 * parallel_factor];
	simd::Vec128u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx_x4(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
// AVX2
TEST(md4, md4_block_AVX2_x1)
{
	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec256u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec256u32 state1[4 * parallel_factor];
	simd::Vec256u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx2_x1(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_AVX2_x2)
{
	constexpr size_t parallel_factor = 2;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec256u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec256u32 state1[4 * parallel_factor];
	simd::Vec256u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx2_x2(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_AVX2_x3)
{
	constexpr size_t parallel_factor = 3;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec256u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec256u32 state1[4 * parallel_factor];
	simd::Vec256u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx2_x3(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_AVX2_x4)
{
	constexpr size_t parallel_factor = 4;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec256u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec256u32 state1[4 * parallel_factor];
	simd::Vec256u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx2_x4(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
// AVX512
TEST(md4, md4_block_AVX512_x1)
{
	constexpr size_t parallel_factor = 1;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec512u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec512u32 state1[4 * parallel_factor];
	simd::Vec512u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx512_x1(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_AVX512_x2)
{
	constexpr size_t parallel_factor = 2;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec512u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec512u32 state1[4 * parallel_factor];
	simd::Vec512u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx512_x2(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_AVX512_x3)
{
	constexpr size_t parallel_factor = 3;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec512u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec512u32 state1[4 * parallel_factor];
	simd::Vec512u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx512_x3(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}
TEST(md4, md4_block_AVX512_x4)
{
	constexpr size_t parallel_factor = 4;
	constexpr size_t parallelism = parallel_factor * sizeof(simd::Vec512u32) / sizeof(uint32_t);

	uint32_t state0[4 * parallelism];
	uint32_t message0[16 * parallelism];

	simd::Vec512u32 state1[4 * parallel_factor];
	simd::Vec512u32 message1[16 * parallel_factor];

	ASSERT_EQ(sizeof(state0), sizeof(state1));
	ASSERT_EQ(sizeof(message0), sizeof(message1));

	// Create a pseudo-random generator
	wy::rand r;
	std::vector<uint32_t> random_values;

	for (size_t i = 0; i < 64; i++)
	{
		r.generate_stream(random_values, std::size(state0) + std::size(message0));
		std::copy(random_values.cbegin(), random_values.cbegin() + std::size(state0), state0);
		std::copy(random_values.cbegin() + std::size(state0), random_values.cend(), message0);

		// Copy values to simd
		for (size_t j = 0; j < std::size(state0); j++)
			reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism] = state0[j];
		for (size_t j = 0; j < std::size(message0); j++)
			reinterpret_cast<uint32_t*>(message1)[j / 16 + (j & 15) * parallelism] = message0[j];

		// Hash
		for (size_t j = 0; j < parallelism; j++)
			md4_transform(state0 + j * 4, message0 + j * 16);
		md4_block_avx512_x4(state1, message1);
		// Compare results
		for (size_t j = 0; j < std::size(state0); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state1)[j / 4 + (j & 3) * parallelism], state0[j]);
	}
}

