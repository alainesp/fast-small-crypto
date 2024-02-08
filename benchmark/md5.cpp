//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MD5 Message-Digest Algorithm
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatically generated code by SIMD-function library
//
// Micro-benchmark

#include <benchmark/benchmark.h>
#include "md5.h"

static void BM_md5_block_PLAIN_C(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::PLAIN_C))
		_benchmark_state.SkipWithMessage("No PLAIN_C");

	uint32_t state[4];
	uint32_t block[16];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md5_block_plain_c(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 1, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md5_block_PLAIN_C);

static void BM_md5_block_SSE2_x3(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::SSE2))
		_benchmark_state.SkipWithMessage("No SSE2");

	simd::Vec128u32 state[12];
	simd::Vec128u32 block[48];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md5_block_sse2_x3(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 12, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md5_block_SSE2_x3);

static void BM_md5_block_AVX_x3(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AVX))
		_benchmark_state.SkipWithMessage("No AVX");

	simd::Vec128u32 state[12];
	simd::Vec128u32 block[48];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md5_block_avx_x3(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 12, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md5_block_AVX_x3);

static void BM_md5_block_AVX2_x3(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AVX2))
		_benchmark_state.SkipWithMessage("No AVX2");

	simd::Vec256u32 state[12];
	simd::Vec256u32 block[48];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md5_block_avx2_x3(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 24, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md5_block_AVX2_x3);

static void BM_md5_block_AVX512_x4(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AVX512))
		_benchmark_state.SkipWithMessage("No AVX512");

	simd::Vec512u32 state[16];
	simd::Vec512u32 block[64];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md5_block_avx512_x4(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 64, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md5_block_AVX512_x4);

