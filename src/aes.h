/////////////////////////////////////////////////////////////////////////////////
// This file is part of 'Fast-Small-Crypto'
// 
// Copyright (c) 2024 by Alain Espinosa.
/////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

static constexpr uint8_t AES_BLOCKLEN = 16;        // Block length in bytes - AES is 128b block only
static constexpr uint8_t AES128_KEY_LENGTH = 16;
static constexpr uint8_t AES192_KEY_LENGTH = 24;
static constexpr uint8_t AES256_KEY_LENGTH = 32;

void AES_ECB_encrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length) noexcept;
void AES_ECB_decrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length) noexcept;

void AES_CBC_encrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length, const uint8_t iv[AES_BLOCKLEN]) noexcept;
void AES_CBC_decrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length, const uint8_t iv[AES_BLOCKLEN]) noexcept;

void AES_CTR_xcrypt(uint8_t* data, const size_t data_length, const uint8_t* key, const uint8_t key_length, const uint8_t iv[AES_BLOCKLEN]) noexcept;
