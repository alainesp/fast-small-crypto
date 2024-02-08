//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MD4 Message-Digest Algorithm
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library
//
// Unit Testing

#include <gtest/gtest.h>
#include "md4.h"
#include <wy.hpp>
#include "reference_implementation.cpp"

TEST(md4, md4_block_PLAIN_C)
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
			md4_transform(state + j * 4, block + j * 16);
		md4_block_plain_c(state_simd, block_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(block); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism], block[j]);
    }
}
TEST(md4, md4_block_SSE2_x3)
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
			md4_transform(state + j * 4, block + j * 16);
		md4_block_sse2_x3(state_simd, block_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(block); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism], block[j]);
    }
}
TEST(md4, md4_block_AVX_x3)
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
			md4_transform(state + j * 4, block + j * 16);
		md4_block_avx_x3(state_simd, block_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(block); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism], block[j]);
    }
}
TEST(md4, md4_block_AVX2_x3)
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
			md4_transform(state + j * 4, block + j * 16);
		md4_block_avx2_x3(state_simd, block_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(block); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism], block[j]);
    }
}
TEST(md4, md4_block_AVX512_x4)
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
			md4_transform(state + j * 4, block + j * 16);
		md4_block_avx512_x4(state_simd, block_simd);

        // Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 4 + (j % 4) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(block); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(block_simd)[j / 16 + (j % 16) * parallelism], block[j]);
    }
}
