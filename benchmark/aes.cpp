//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AES encryption algorithm benchmark
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>
#include "aes.h"
#include "simd.hpp"

// AES128
static void BM_aes128_cbc_encrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t iv[AES_BLOCKLEN];
	uint8_t key[AES128_KEY_LENGTH];
	uint32_t num_calls = 0;

	for (auto _ : _benchmark_state) {
		AES_CBC_encrypt(plaintext, sizeof(plaintext), key, sizeof(key), iv);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_aes128_cbc_encrypt);

static void BM_aes128_cbc_decrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t iv[AES_BLOCKLEN];
	uint8_t key[AES128_KEY_LENGTH];
	uint32_t num_calls = 0;

	for (auto _ : _benchmark_state) {
		AES_CBC_decrypt(plaintext, sizeof(plaintext), key, sizeof(key), iv);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_aes128_cbc_decrypt);

// Disable AES-NI on OpenSSL and benchmark:
//     OPENSSL_ia32cap="~0x200000200000000" openssl speed -elapsed -evp aes-128-ecb
static void BM_aes128_ecb_encrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES128_KEY_LENGTH];
	uint32_t num_calls = 0;

	for (auto _ : _benchmark_state) {
		AES_ECB_encrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_aes128_ecb_encrypt);

static void BM_aes128_ecb_decrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES128_KEY_LENGTH];
	uint32_t num_calls = 0;

	for (auto _ : _benchmark_state) {
		AES_ECB_decrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_aes128_ecb_decrypt);

static void BM_aesni128_ecb_encrypt(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AES))
		_benchmark_state.SkipWithMessage("No AESNI");

	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES128_KEY_LENGTH];
	uint32_t num_calls = 0;

	for (auto _ : _benchmark_state) {
		AESNI_ECB_encrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_aesni128_ecb_encrypt);

static void BM_aesni128_ecb_decrypt(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AES))
		_benchmark_state.SkipWithMessage("No AESNI");

	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES128_KEY_LENGTH];
	uint32_t num_calls = 0;

	for (auto _ : _benchmark_state) {
		AESNI_ECB_decrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_aesni128_ecb_decrypt);

// AES192
static void BM_aes192_cbc_encrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t iv[AES_BLOCKLEN];
	uint8_t key[AES192_KEY_LENGTH];
	uint32_t num_calls = 0;

	for (auto _ : _benchmark_state) {
		AES_CBC_encrypt(plaintext, sizeof(plaintext), key, sizeof(key), iv);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_aes192_cbc_encrypt);

static void BM_aes192_ecb_encrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES192_KEY_LENGTH];
	uint32_t num_calls = 0;

	for (auto _ : _benchmark_state) {
		AES_ECB_encrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_aes192_ecb_encrypt);

// AES256
static void BM_aes256_cbc_encrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t iv[AES_BLOCKLEN];
	uint8_t key[AES256_KEY_LENGTH];
	uint32_t num_calls = 0;

	for (auto _ : _benchmark_state) {
		AES_CBC_encrypt(plaintext, sizeof(plaintext), key, sizeof(key), iv);
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_aes256_cbc_encrypt);

static void BM_aes256_ecb_encrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES256_KEY_LENGTH];
	uint32_t num_calls = 0;

	for (auto _ : _benchmark_state) {
		AES_ECB_encrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_calls++;
	}
	_benchmark_state.counters["CallRate"] = benchmark::Counter(num_calls, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_aes256_ecb_encrypt);