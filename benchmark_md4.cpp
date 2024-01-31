#include <benchmark/benchmark.h>
#include "md4.h"

static void BM_md4_block_PLAIN_C(benchmark::State& _benchmark_state) {
	uint32_t state[4];
	uint32_t block[16];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_plain_c(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 1, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_PLAIN_C);

static void BM_md4_block_SSE2_x1(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::SSE2 & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No SSE2");

	simd::Vec128u32 state[4];
	simd::Vec128u32 block[16];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_sse2_x1(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 4, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_SSE2_x1);

static void BM_md4_block_SSE2_x2(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::SSE2 & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No SSE2");

	simd::Vec128u32 state[8];
	simd::Vec128u32 block[32];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_sse2_x2(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 8, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_SSE2_x2);

static void BM_md4_block_SSE2_x3(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::SSE2 & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No SSE2");

	simd::Vec128u32 state[12];
	simd::Vec128u32 block[48];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_sse2_x3(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 12, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_SSE2_x3);

static void BM_md4_block_SSE2_x4(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::SSE2 & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No SSE2");

	simd::Vec128u32 state[16];
	simd::Vec128u32 block[64];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_sse2_x4(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 16, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_SSE2_x4);

static void BM_md4_block_AVX_x1(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX");

	simd::Vec128u32 state[4];
	simd::Vec128u32 block[16];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx_x1(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 4, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX_x1);

static void BM_md4_block_AVX_x2(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX");

	simd::Vec128u32 state[8];
	simd::Vec128u32 block[32];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx_x2(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 8, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX_x2);

static void BM_md4_block_AVX_x3(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX");

	simd::Vec128u32 state[12];
	simd::Vec128u32 block[48];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx_x3(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 12, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX_x3);

static void BM_md4_block_AVX_x4(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX");

	simd::Vec128u32 state[16];
	simd::Vec128u32 block[64];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx_x4(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 16, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX_x4);

static void BM_md4_block_AVX2_x1(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX2 & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX2");

	simd::Vec256u32 state[4];
	simd::Vec256u32 block[16];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx2_x1(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 8, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX2_x1);

static void BM_md4_block_AVX2_x2(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX2 & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX2");

	simd::Vec256u32 state[8];
	simd::Vec256u32 block[32];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx2_x2(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 16, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX2_x2);

static void BM_md4_block_AVX2_x3(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX2 & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX2");

	simd::Vec256u32 state[12];
	simd::Vec256u32 block[48];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx2_x3(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 24, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX2_x3);

static void BM_md4_block_AVX2_x4(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX2 & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX2");

	simd::Vec256u32 state[16];
	simd::Vec256u32 block[64];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx2_x4(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 32, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX2_x4);

static void BM_md4_block_AVX512_x1(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX512F & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX512F");

	simd::Vec512u32 state[4];
	simd::Vec512u32 block[16];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx512_x1(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 16, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX512_x1);

static void BM_md4_block_AVX512_x2(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX512F & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX512F");

	simd::Vec512u32 state[8];
	simd::Vec512u32 block[32];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx512_x2(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 32, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX512_x2);

static void BM_md4_block_AVX512_x3(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX512F & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX512F");

	simd::Vec512u32 state[12];
	simd::Vec512u32 block[48];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx512_x3(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 48, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX512_x3);

static void BM_md4_block_AVX512_x4(benchmark::State& _benchmark_state) {
	if (!(simd::CpuFeatures::AVX512F & simd::get_cpu_features()))
		_benchmark_state.SkipWithMessage("No AVX512F");

	simd::Vec512u32 state[16];
	simd::Vec512u32 block[64];
	uint32_t num_calls = 0;
	for (auto _ : _benchmark_state) {
		md4_block_avx512_x4(state, block);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls * 64, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_md4_block_AVX512_x4);

