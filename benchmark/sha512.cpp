//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHA512 - Secure Hash Algorithm 2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library
//
// Micro-benchmark

#include <benchmark/benchmark.h>
#include "sha512.h"

static void BM_sha512_block_PLAIN_C(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::PLAIN_C))
		_benchmark_state.SkipWithMessage("No PLAIN_C");

	uint64_t state[8];
	uint64_t W[16];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		sha512_block_plain_c(state, W);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 1, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_sha512_block_PLAIN_C);

static void BM_sha512_block_SSE2(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::SSE2))
		_benchmark_state.SkipWithMessage("No SSE2");

	simd::Vec128u64 state[8];
	simd::Vec128u64 W[16];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		sha512_block_sse2(state, W);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 2, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_sha512_block_SSE2);

static void BM_sha512_block_AVX(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AVX))
		_benchmark_state.SkipWithMessage("No AVX");

	simd::Vec128u64 state[8];
	simd::Vec128u64 W[16];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		sha512_block_avx(state, W);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 2, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_sha512_block_AVX);

static void BM_sha512_block_AVX2(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AVX2))
		_benchmark_state.SkipWithMessage("No AVX2");

	simd::Vec256u64 state[8];
	simd::Vec256u64 W[16];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		sha512_block_avx2(state, W);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 4, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_sha512_block_AVX2);

static void BM_sha512_block_AVX512(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AVX512))
		_benchmark_state.SkipWithMessage("No AVX512");

	simd::Vec512u64 state[8];
	simd::Vec512u64 W[16];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		sha512_block_avx512(state, W);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 8, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_sha512_block_AVX512);

