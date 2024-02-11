//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AES encryption algorithm benchmark
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>
#include "aes.h"
#include "simd.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// uint32_t algorithm
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable AES-NI on OpenSSL and benchmark:
//     OPENSSL_ia32cap="~0x200000200000000" openssl speed -elapsed -evp aes-128-ecb
static void BM_aes_ecb_encrypt(benchmark::State& _benchmark_state) {
	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES256_KEY_LENGTH];
	uint8_t key_length = _benchmark_state.range(0);
	int64_t num_bytes = 0;

	for (auto _ : _benchmark_state) {
		AES_ECB_encrypt(plaintext, sizeof(plaintext), key, key_length);
		num_bytes += 16;
	}
	_benchmark_state.SetBytesProcessed(num_bytes);
}
BENCHMARK(BM_aes_ecb_encrypt)->DenseRange(16, 32, 8);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AESNI
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void BM_aesni_ecb_encrypt(benchmark::State& _benchmark_state) {
	if (!simd::cpu_supports(simd::CpuFeatures::AES))
		_benchmark_state.SkipWithMessage("No AESNI");

	uint8_t plaintext[AES_BLOCKLEN];
	uint8_t key[AES256_KEY_LENGTH];
	uint8_t key_length = _benchmark_state.range(0);
	int64_t num_bytes = 0;

	for (auto _ : _benchmark_state) {
		AESNI_ECB_encrypt(plaintext, sizeof(plaintext), key, key_length);
		num_bytes += 16;
	}
	_benchmark_state.SetBytesProcessed(num_bytes);
}
BENCHMARK(BM_aesni_ecb_encrypt)->DenseRange(16, 32, 8);

