//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA512 - Secure Hash Algorithm 2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library
//
// Unit Testing

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
