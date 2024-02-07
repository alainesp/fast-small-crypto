//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA1 - Secure Hash Algorithm 1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library
//
// Unit Testing

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
	if (!simd::cpu_supports(simd::CpuFeatures::SHANI))
		GTEST_SKIP() << "No SHA-NI";

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
		sha1_block_shani(state_simd, W_simd);

		// Compare results
		for (size_t j = 0; j < std::size(state); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(state_simd)[j / 5 + (j % 5) * parallelism], state[j]);
		for (size_t j = 0; j < std::size(W); j++)
			ASSERT_EQ(reinterpret_cast<uint32_t*>(W_simd)[j / 16 + (j % 16) * parallelism], W[j]);
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
