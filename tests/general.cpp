/////////////////////////////////////////////////////////////////////////////////
// This file is part of 'Fast-Small-Crypto'
// 
// Copyright (c) 2024 by Alain Espinosa.
/////////////////////////////////////////////////////////////////////////////////

// Include the required header
#include <gtest/gtest.h>
#include <string>
#include <bit>
#include "byteswap.h"

/////////////////////////////////////////////////////////////////////////////////
/// General
/////////////////////////////////////////////////////////////////////////////////
TEST(general, Endianness)
{
	uint64_t val = 0x0102'0304'0506'0708;
	uint8_t byteArray[8];

	memcpy(byteArray, &val, sizeof(byteArray));

	for (size_t i = 0; i < 8; i++)
		if constexpr (std::endian::native == std::endian::little)
			ASSERT_EQ(byteArray[i], (val >> i * 8) & 0xff);
		else
			ASSERT_EQ(byteArray[7 - i], (val >> i * 8) & 0xff);
}
TEST(general, Byteswap)
{
	uint64_t val64 = 0x0102'0304'0506'0708;
	uint64_t swap64 = byteswap64(val64);	
	for (size_t i = 0; i < 8; i++)
	{
		ASSERT_EQ((swap64 >> (7 - i) * 8) & 0xff, (val64 >> i * 8) & 0xff);
	}
	ASSERT_EQ(val64, byteswap64(swap64));

	uint32_t val32 = 0x0102'0304;
	uint32_t swap32 = byteswap32(val32);
	for (size_t i = 0; i < 4; i++)
	{
		ASSERT_EQ((swap32 >> (3 - i) * 8) & 0xff, (val32 >> i * 8) & 0xff);
	}
	ASSERT_EQ(val32, byteswap32(swap32));
}
