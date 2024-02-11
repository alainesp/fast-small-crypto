/////////////////////////////////////////////////////////////////////////////////
// This file is part of 'Fast-Small-Crypto'
// 
// Copyright (c) 2024 by Alain Espinosa.
/////////////////////////////////////////////////////////////////////////////////

// Include the required header
#include <gtest/gtest.h>
#include "aes.h"
#include "simd.hpp"
#include <wy.hpp>

static const uint8_t aes_key_lengths[] = { AES128_KEY_LENGTH, AES192_KEY_LENGTH, AES256_KEY_LENGTH };

TEST(aes, ecb_encrypt_decrypt)
{
	uint8_t original_data[4 * AES_BLOCKLEN];
	uint8_t processed_data[4 * AES_BLOCKLEN];
	uint8_t key[AES256_KEY_LENGTH];

	// Create a pseudo-random generator
	wy::rand r;

	for (size_t i = 0; i < 1024; i++)
	{
		r.generate_stream<uint8_t>(key);
		r.generate_stream<uint8_t>(original_data);
		memcpy(processed_data, original_data, sizeof(processed_data));
		
		// Encrypt-Decrypt
		for (size_t k_index = 0; k_index < std::size(aes_key_lengths); k_index++)
		{
			AES_ECB_encrypt(processed_data, sizeof(processed_data), key, aes_key_lengths[k_index]);
			AES_ECB_decrypt(processed_data, sizeof(processed_data), key, aes_key_lengths[k_index]);

			// Compare results
			for (size_t j = 0; j < std::size(original_data); j++)
				ASSERT_EQ(original_data[j], processed_data[j]);
		}
	}
}
TEST(aes, cbc_encrypt_decrypt)
{
	uint8_t original_data[4 * AES_BLOCKLEN];
	uint8_t processed_data[4 * AES_BLOCKLEN];
	uint8_t key[AES256_KEY_LENGTH];
	uint8_t iv[AES_BLOCKLEN];

	// Create a pseudo-random generator
	wy::rand r;

	for (size_t i = 0; i < 1024; i++)
	{
		r.generate_stream<uint8_t>(key);
		r.generate_stream<uint8_t>(iv);
		r.generate_stream<uint8_t>(original_data);
		memcpy(processed_data, original_data, sizeof(processed_data));

		// Encrypt-Decrypt
		for (size_t k_index = 0; k_index < std::size(aes_key_lengths); k_index++)
		{
			AES_CBC_encrypt(processed_data, sizeof(processed_data), key, aes_key_lengths[k_index], iv);
			AES_CBC_decrypt(processed_data, sizeof(processed_data), key, aes_key_lengths[k_index], iv);

			// Compare results
			for (size_t j = 0; j < std::size(original_data); j++)
				ASSERT_EQ(original_data[j], processed_data[j]);
		}
	}
}
TEST(aes, ctr_encrypt_decrypt)
{
	uint8_t original_data[4 * AES_BLOCKLEN];
	uint8_t processed_data[4 * AES_BLOCKLEN];
	uint8_t key[AES256_KEY_LENGTH];
	uint8_t iv[AES_BLOCKLEN];

	// Create a pseudo-random generator
	wy::rand r;

	for (size_t i = 0; i < 1024; i++)
	{
		r.generate_stream<uint8_t>(key);
		r.generate_stream<uint8_t>(iv);
		r.generate_stream<uint8_t>(original_data);
		memcpy(processed_data, original_data, sizeof(processed_data));

		// Encrypt-Decrypt
		for (size_t k_index = 0; k_index < std::size(aes_key_lengths); k_index++)
		{
			AES_CTR_xcrypt(processed_data, sizeof(processed_data), key, aes_key_lengths[k_index], iv);
			AES_CTR_xcrypt(processed_data, sizeof(processed_data), key, aes_key_lengths[k_index], iv);

			// Compare results
			for (size_t j = 0; j < std::size(original_data); j++)
				ASSERT_EQ(original_data[j], processed_data[j]);
		}
	}
}

TEST(aesni, ecb_encrypt_decrypt)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AES))
		GTEST_SKIP() << "No AESNI";

	uint8_t original_data[4 * AES_BLOCKLEN];
	uint8_t processed_data[4 * AES_BLOCKLEN];
	uint8_t key[AES256_KEY_LENGTH];

	// Create a pseudo-random generator
	wy::rand r;

	for (size_t i = 0; i < 1024; i++)
	{
		r.generate_stream<uint8_t>(key);
		r.generate_stream<uint8_t>(original_data);
		memcpy(processed_data, original_data, sizeof(processed_data));

		// Encrypt-Decrypt
		for (size_t k_index = 0; k_index < std::size(aes_key_lengths); k_index++)
		{
			AESNI_ECB_encrypt(processed_data, sizeof(processed_data), key, aes_key_lengths[k_index]);
			AESNI_ECB_decrypt(processed_data, sizeof(processed_data), key, aes_key_lengths[k_index]);

			// Compare results
			for (size_t j = 0; j < std::size(original_data); j++)
				ASSERT_EQ(original_data[j], processed_data[j]);
		}
	}
}
TEST(aesni, cbc_encrypt_decrypt)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AES))
		GTEST_SKIP() << "No AESNI";

	uint8_t original_data[4 * AES_BLOCKLEN];
	uint8_t processed_data[4 * AES_BLOCKLEN];
	uint8_t key[AES256_KEY_LENGTH];
	uint8_t iv[AES_BLOCKLEN];

	// Create a pseudo-random generator
	wy::rand r;

	for (size_t i = 0; i < 1024; i++)
	{
		r.generate_stream<uint8_t>(key);
		r.generate_stream<uint8_t>(iv);
		r.generate_stream<uint8_t>(original_data);
		memcpy(processed_data, original_data, sizeof(processed_data));

		// Encrypt-Decrypt
		for (size_t k_index = 0; k_index < std::size(aes_key_lengths); k_index++)
		{
			AESNI_CBC_encrypt(processed_data, sizeof(processed_data), key, aes_key_lengths[k_index], iv);
			AESNI_CBC_decrypt(processed_data, sizeof(processed_data), key, aes_key_lengths[k_index], iv);

			// Compare results
			for (size_t j = 0; j < std::size(original_data); j++)
				ASSERT_EQ(original_data[j], processed_data[j]);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Cryptographic Algorithm Validation Program [CAVP]
/////////////////////////////////////////////////////////////////////////////////////////////////////
// https://csrc.nist.gov/projects/cryptographic-algorithm-validation-program/block-ciphers

#include <filesystem>
#include <iostream>
#include <fstream>

enum class AESModes
{
	CBC,
	ECB,
	CTR
};

using AES_ECB_FUNC = void (*)(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length) noexcept;
using AES_CBC_FUNC = void (*)(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length, const uint8_t iv[AES_BLOCKLEN]) noexcept;

/// <summary>
/// Search for all .rsp files in the given directory and perform the tests
/// </summary>
/// <param name="dir">The directory to search for test vectors</param>
static void aes_load_tests_from_directory(const std::string& dir, int repeated, AES_ECB_FUNC ecb_enc, AES_ECB_FUNC ecb_dec, AES_CBC_FUNC cbc_enc, AES_CBC_FUNC cbc_dec) noexcept
{
	uint8_t plaintext[10 * AES_BLOCKLEN];
	uint8_t ciphertext[sizeof(plaintext)];
	uint8_t data[sizeof(plaintext)];
	uint8_t key[AES256_KEY_LENGTH];
	uint8_t iv[AES_BLOCKLEN];
	int plaintext_size = -1;
	int ciphertext_size = -1;
	bool key_readed = false;
	bool is_encrypting = false;

	for (const auto& entry : std::filesystem::directory_iterator(dir))
		if (entry.is_regular_file())
		{
			const auto file = entry.path().filename();
			const auto u8file = file.string();

			// Modes supported
			if (file.extension() == ".rsp" && (u8file.starts_with("CBC") || u8file.starts_with("ECB") || u8file.starts_with("CTR")))
			{
				AESModes mode = u8file.starts_with("CBC") ? AESModes::CBC : (u8file.starts_with("ECB") ? AESModes::ECB : AESModes::CTR);
				uint8_t key_length = std::stoi(u8file.substr(u8file.size() - 7, 3)) / 8;
				ASSERT_TRUE(key_length == AES128_KEY_LENGTH || key_length == AES192_KEY_LENGTH || key_length == AES256_KEY_LENGTH);

				// Open file with data
				std::ifstream rsp_tests(entry.path());
				std::string line;
				ASSERT_TRUE(rsp_tests.is_open());

				// Read line by line
				while (getline(rsp_tests, line))
				{
					if (line.starts_with("[ENCRYPT]")) is_encrypting = true;
					if (line.starts_with("[DECRYPT]")) is_encrypting = false;

					// Read data
					if (line.starts_with("KEY = "))
					{
						ASSERT_EQ(line.size(), 6 + key_length * 2);
						key_readed = true;
						for (uint8_t i = 0; i < key_length; i++)
							key[i] = std::stoi(line.substr(6 + i * 2, 2), nullptr, 16);
					}

					if (line.starts_with("IV = "))
					{
						ASSERT_EQ(line.size(), 5 + AES_BLOCKLEN * 2);
						for (int i = 0; i < AES_BLOCKLEN; i++)
							iv[i] = std::stoi(line.substr(5 + i * 2, 2), nullptr, 16);
					}

					if (line.starts_with("PLAINTEXT = "))
					{
						plaintext_size = static_cast<int>((line.size() - 12) / 2);
						ASSERT_EQ(0, plaintext_size % AES_BLOCKLEN);
						ASSERT_LE(plaintext_size, sizeof(plaintext));

						for (int i = 0; i < plaintext_size; i++)
							plaintext[i] = std::stoi(line.substr(12 + i * 2, 2), nullptr, 16);
					}

					if (line.starts_with("CIPHERTEXT = "))
					{
						ciphertext_size = static_cast<int>((line.size() - 13) / 2);
						ASSERT_EQ(0, ciphertext_size % AES_BLOCKLEN);
						ASSERT_LE(ciphertext_size, sizeof(ciphertext));

						for (int i = 0; i < ciphertext_size; i++)
							ciphertext[i] = std::stoi(line.substr(13 + i * 2, 2), nullptr, 16);
					}

					// If we have the data needed
					if (plaintext_size > 0 && ciphertext_size > 0 && key_readed)
					{
						ASSERT_EQ(plaintext_size, ciphertext_size);
						ASSERT_LE(plaintext_size, sizeof(data));

						// Test encryption
						if (is_encrypting)
						{
							memcpy(data, plaintext, plaintext_size);
							switch (mode)
							{
							case AESModes::CBC:
								for (int i = 0; i < repeated; i++)
								{
									cbc_enc(data, plaintext_size, key, key_length, iv);
									// Swap data and iv
									uint8_t tmp[AES_BLOCKLEN];
									memcpy(tmp, data, AES_BLOCKLEN);
									memcpy(data, iv, AES_BLOCKLEN);
									memcpy(iv, tmp, AES_BLOCKLEN);
								}
								memcpy(data, iv, AES_BLOCKLEN);
								break;
							case AESModes::ECB: for (int i = 0; i < repeated; i++) ecb_enc(data, plaintext_size, key, key_length);            break;
							case AESModes::CTR: for (int i = 0; i < repeated; i++) AES_CTR_xcrypt(data, plaintext_size, key, key_length, iv); break;
							default: ASSERT_TRUE(false); break;
							}
							for (size_t j = 0; j < plaintext_size; j++)
								ASSERT_EQ(data[j], ciphertext[j]);
						}

						// Test decryption
						if (!is_encrypting)
						{
							memcpy(data, ciphertext, plaintext_size);
							switch (mode)
							{
							case AESModes::CBC:
								uint8_t tmp[AES_BLOCKLEN];
								uint8_t tmp2[AES_BLOCKLEN];
								memcpy(tmp2, iv, AES_BLOCKLEN);
								for (int i = 0; i < repeated; i++)
								{
									memcpy(tmp, data, AES_BLOCKLEN);
									cbc_dec(data, plaintext_size, key, key_length, iv);
									memcpy(iv, tmp, AES_BLOCKLEN);
									// Swap data and tmp2
									memcpy(tmp, data, AES_BLOCKLEN);
									memcpy(data, tmp2, AES_BLOCKLEN);
									memcpy(tmp2, tmp, AES_BLOCKLEN);
								}
								memcpy(data, tmp2, AES_BLOCKLEN);
								break;
							case AESModes::ECB: for (int i = 0; i < repeated; i++) ecb_dec(data, plaintext_size, key, key_length);            break;
							case AESModes::CTR: for (int i = 0; i < repeated; i++) AES_CTR_xcrypt(data, plaintext_size, key, key_length, iv); break;
							default: ASSERT_TRUE(false); break;
							}
							// Compare results
							for (size_t j = 0; j < plaintext_size; j++)
								ASSERT_EQ(data[j], plaintext[j]);
						}

						plaintext_size = -1;
						ciphertext_size = -1;
						key_readed = false;
					}
				}

				rsp_tests.close();
			}
		}
}

// AES Known Answer Test (KAT) Vectors
TEST(aes, KAT_vectors)
{
	aes_load_tests_from_directory(TEST_DIR "KAT_AES", 1, AES_ECB_encrypt, AES_ECB_decrypt, AES_CBC_encrypt, AES_CBC_decrypt);
}
TEST(aesni, KAT_vectors)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AES))
		GTEST_SKIP() << "No AESNI";

	aes_load_tests_from_directory(TEST_DIR "KAT_AES", 1, AESNI_ECB_encrypt, AESNI_ECB_decrypt, AESNI_CBC_encrypt, AESNI_CBC_decrypt);
}
// AES Monte Carlo Test (MCT) Sample Vectors
TEST(aes, MCT_vectors)
{
	aes_load_tests_from_directory(TEST_DIR "aesmct", 1000, AES_ECB_encrypt, AES_ECB_decrypt, AES_CBC_encrypt, AES_CBC_decrypt);
}
TEST(aesni, MCT_vectors)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AES))
		GTEST_SKIP() << "No AESNI";

	aes_load_tests_from_directory(TEST_DIR "aesmct", 1000, AESNI_ECB_encrypt, AESNI_ECB_decrypt, AESNI_CBC_encrypt, AESNI_CBC_decrypt);
}
// AES Multiblock Message Test (MMT) Sample Vectors
TEST(aes, MMT_vectors)
{
	aes_load_tests_from_directory(TEST_DIR "aesmmt", 1, AES_ECB_encrypt, AES_ECB_decrypt, AES_CBC_encrypt, AES_CBC_decrypt);
}
TEST(aesni, MMT_vectors)
{
	if (!simd::cpu_supports(simd::CpuFeatures::AES))
		GTEST_SKIP() << "No AESNI";

	aes_load_tests_from_directory(TEST_DIR "aesmmt", 1, AESNI_ECB_encrypt, AESNI_ECB_decrypt, AESNI_CBC_encrypt, AESNI_CBC_decrypt);
}
