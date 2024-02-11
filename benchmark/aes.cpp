//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AES encryption algorithm benchmark
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>
#include "aes.h"
#include "simd.hpp"

// AES128
// Disable AES-NI on OpenSSL and benchmark:
//     OPENSSL_ia32cap="~0x200000200000000" openssl speed -elapsed -evp aes-128-ecb
static void BM_aes128_ecb_encrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES128_KEY_LENGTH];
	int64_t num_bytes = 0;

	for (auto _ : _benchmark_state) {
		AES_ECB_encrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_bytes += 16;
	}
	_benchmark_state.SetBytesProcessed(num_bytes);
}
BENCHMARK(BM_aes128_ecb_encrypt);

// AES192
static void BM_aes192_ecb_encrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES192_KEY_LENGTH];
	int64_t num_bytes = 0;

	for (auto _ : _benchmark_state) {
		AES_ECB_encrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_bytes += 16;
	}
	_benchmark_state.SetBytesProcessed(num_bytes);
}
BENCHMARK(BM_aes192_ecb_encrypt);

// AES256
static void BM_aes256_ecb_encrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES256_KEY_LENGTH];
	int64_t num_bytes = 0;

	for (auto _ : _benchmark_state) {
		AES_ECB_encrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_bytes += 16;
	}
	_benchmark_state.SetBytesProcessed(num_bytes);
}
BENCHMARK(BM_aes256_ecb_encrypt);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AESNI
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AES128
static void BM_aesni128_ecb_encrypt(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AES))
		_benchmark_state.SkipWithMessage("No AESNI");

	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES128_KEY_LENGTH];
	int64_t num_bytes = 0;

	for (auto _ : _benchmark_state) {
		AESNI_ECB_encrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_bytes += 16;
	}
	_benchmark_state.SetBytesProcessed(num_bytes);
}
BENCHMARK(BM_aesni128_ecb_encrypt);

// AES192
static void BM_aesni192_ecb_encrypt(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AES))
		_benchmark_state.SkipWithMessage("No AESNI");

	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES192_KEY_LENGTH];
	int64_t num_bytes = 0;

	for (auto _ : _benchmark_state) {
		AESNI_ECB_encrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_bytes += 16;
	}
	_benchmark_state.SetBytesProcessed(num_bytes);
}
BENCHMARK(BM_aesni192_ecb_encrypt);

// AES256
static void BM_aesni256_ecb_encrypt(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AES))
		_benchmark_state.SkipWithMessage("No AESNI");

	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES256_KEY_LENGTH];
	int64_t num_bytes = 0;

	for (auto _ : _benchmark_state) {
		AESNI_ECB_encrypt(plaintext, sizeof(plaintext), key, sizeof(key));
		num_bytes += 16;
	}
	_benchmark_state.SetBytesProcessed(num_bytes);
}
BENCHMARK(BM_aesni256_ecb_encrypt);
