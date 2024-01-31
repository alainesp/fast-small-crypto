/////////////////////////////////////////////////////////////////////////////////
// This file is part of 'Fast-Small-Crypto'
// 
// Copyright (c) 2024 by Alain Espinosa.
/////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include "simd.hpp"

#if SIMD_ARCH_X86
	#include <xmmintrin.h>
	#if _MSC_VER
		#include <intrin.h>
	#else
		#include <cpuid.h>
	#endif 
#elif (SIMD_ARCH_ARM/* || HWY_ARCH_PPC || HWY_ARCH_S390X*/) && SIMD_OS_LINUX
	// sys/auxv.h does not always include asm/hwcap.h, or define HWCAP*, hence we
	// still include this directly.
	#include <asm/hwcap.h>
	#include <sys/auxv.h>
#endif

static constexpr bool is_bit_set(const uint32_t reg, const int index) noexcept { return reg & (1U << index); }

#if SIMD_ARCH_X86
/// <summary>
/// x86 CPUID
/// </summary>
/// <param name="level"></param>
/// <param name="count"></param>
/// <param name="abcd"></param>
static void cpuid(const uint32_t level, const uint32_t count, uint32_t abcd[4]) noexcept {
#if _MSC_VER
	int regs[4];
	__cpuidex(regs, level, count);
	for (int i = 0; i < 4; ++i)
		abcd[i] = regs[i];
#else
	uint32_t a, b, c, d;
	__cpuid_count(level, count, a, b, c, d);
	abcd[0] = a;
	abcd[1] = b;
	abcd[2] = c;
	abcd[3] = d;
#endif
}

/// <summary>
/// Returns the lower 32 bits of extended control register 0.
/// Requires CPU support for "OSXSAVE".
/// </summary>
/// <returns></returns>
static uint32_t ReadXCR0() noexcept {
#if _MSC_VER
	return static_cast<uint32_t>(_xgetbv(0));
#else
	uint32_t xcr0, xcr0_high;
	const uint32_t index = 0;
	asm volatile(".byte 0x0F, 0x01, 0xD0"
		: "=a"(xcr0), "=d"(xcr0_high)
		: "c"(index));
	return xcr0;
#endif
}

using namespace simd;

// Returns bit array of FeatureIndex from CPUID feature flags.
static CpuFeatures cpu_feature_flag_x86() noexcept {
	CpuFeatures flags = CpuFeatures::PLAIN_C;  // return value

	uint32_t abcd[4];
	cpuid(0, 0, abcd);
	const uint32_t max_level = abcd[0];

	// Standard feature flags
	cpuid(1, 0, abcd);
	// Operating system support
	const bool has_osxsave = is_bit_set(abcd[2], 27);
	uint32_t xcr0 = 0;
	if (has_osxsave)
		xcr0 = ReadXCR0();
	const bool xsave_xmm = (xcr0 & 2);          // is_bit_set(xcr0, 1)
	const bool xsave_ymm = (xcr0 & 6) == 6;     // is_bit_set(xcr0, 2)
	const bool xsave_zmm = (xcr0 & 230) == 230; // is_bit_set(xcr0, 5) && is_bit_set(xcr0, 6) && is_bit_set(xcr0, 7)

#if SIMD_ARCH_X86_64
	flags |=  CpuFeatures::SSE | CpuFeatures::SSE2;  // always present in x64
	flags |=  is_bit_set(abcd[2],  0)               ? CpuFeatures::SSE3  : CpuFeatures::NONE;
	flags |=  is_bit_set(abcd[2],  1)               ? CpuFeatures::CLMUL : CpuFeatures::NONE;
	flags |=  is_bit_set(abcd[2],  9)               ? CpuFeatures::SSSE3 : CpuFeatures::NONE;
	flags |=  is_bit_set(abcd[2], 19)               ? CpuFeatures::SSE41 : CpuFeatures::NONE;
	flags |=  is_bit_set(abcd[2], 20)               ? CpuFeatures::SSE42 : CpuFeatures::NONE;
	flags |=  is_bit_set(abcd[2], 25)               ? CpuFeatures::AES   : CpuFeatures::NONE;
#else
	flags |= (is_bit_set(abcd[3], 25) && xsave_xmm) ? CpuFeatures::SSE   : CpuFeatures::NONE;
	flags |= (is_bit_set(abcd[3], 26) && xsave_xmm) ? CpuFeatures::SSE2  : CpuFeatures::NONE;
	flags |= (is_bit_set(abcd[2],  0) && xsave_xmm) ? CpuFeatures::SSE3  : CpuFeatures::NONE;
	flags |= (is_bit_set(abcd[2],  1) && xsave_xmm) ? CpuFeatures::CLMUL : CpuFeatures::NONE;
	flags |= (is_bit_set(abcd[2],  9) && xsave_xmm) ? CpuFeatures::SSSE3 : CpuFeatures::NONE;
	flags |= (is_bit_set(abcd[2], 19) && xsave_xmm) ? CpuFeatures::SSE41 : CpuFeatures::NONE;
	flags |= (is_bit_set(abcd[2], 20) && xsave_xmm) ? CpuFeatures::SSE42 : CpuFeatures::NONE;
	flags |= (is_bit_set(abcd[2], 25) && xsave_xmm) ? CpuFeatures::AES   : CpuFeatures::NONE;
#endif
	flags |= (is_bit_set(abcd[2], 28) && xsave_ymm) ? CpuFeatures::AVX  : CpuFeatures::NONE;
	flags |= (is_bit_set(abcd[2], 12) && xsave_ymm) ? CpuFeatures::FMA  : CpuFeatures::NONE;
	flags |= (is_bit_set(abcd[2], 29) && xsave_ymm) ? CpuFeatures::F16C : CpuFeatures::NONE;

	// Extended feature flags
	cpuid(0x80000001U, 0, abcd);
	flags |=  is_bit_set(abcd[2],  5)               ? CpuFeatures::LZCNT : CpuFeatures::NONE;

	// Extended features
	if (max_level >= 7) {
		cpuid(7, 0, abcd);
		flags |=  is_bit_set(abcd[1],  3)               ? CpuFeatures::BMI  : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[1],  5) && xsave_ymm) ? CpuFeatures::AVX2 : CpuFeatures::NONE;
		flags |=  is_bit_set(abcd[1],  8)               ? CpuFeatures::BMI2 : CpuFeatures::NONE;

		flags |= (is_bit_set(abcd[1], 16) && xsave_zmm) ? CpuFeatures::AVX512F  : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[1], 17) && xsave_zmm) ? CpuFeatures::AVX512DQ : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[1], 28) && xsave_zmm) ? CpuFeatures::AVX512CD : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[1], 30) && xsave_zmm) ? CpuFeatures::AVX512BW : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[1], 31) && xsave_zmm) ? CpuFeatures::AVX512VL : CpuFeatures::NONE;

		flags |= (is_bit_set(abcd[2],  1) && xsave_zmm) ? CpuFeatures::VBMI       : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[2],  6) && xsave_zmm) ? CpuFeatures::VBMI2      : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[2],  8) && xsave_zmm) ? CpuFeatures::GFNI       : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[2],  9) && xsave_zmm) ? CpuFeatures::VAES       : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[2], 10) && xsave_zmm) ? CpuFeatures::VPCLMULQDQ : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[2], 11) && xsave_zmm) ? CpuFeatures::VNNI       : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[2], 12) && xsave_zmm) ? CpuFeatures::BITALG     : CpuFeatures::NONE;
		flags |= (is_bit_set(abcd[2], 14) && xsave_zmm) ? CpuFeatures::POPCNTDQ   : CpuFeatures::NONE;

		flags |= (is_bit_set(abcd[3], 23) && xsave_zmm) ? CpuFeatures::AVX512FP16 : CpuFeatures::NONE;
	}

	return flags;
}
#endif

#if SIMD_ARCH_ARM
static CpuFeatures cpu_feature_flag_arm() noexcept {
	CpuFeatures flags = CpuFeatures::PLAIN_C;  // return value

	const unsigned long hw = getauxval(AT_HWCAP);

#if SIMD_ARCH_ARM_A64
	flags |= CpuFeatures::NEON | CpuFeatures::VFPv4;  // aarch64 always has NEON and VFPv4..

	// .. but not necessarily AES, which is required for HWY_NEON.
#if defined(HWCAP_AES)
	if (hw & HWCAP_AES)
		flags |= CpuFeatures::AES;
#endif  // HWCAP_AES

#if defined(HWCAP_SVE)
	if (hw & HWCAP_SVE)
		flags |= CpuFeatures::SVE;
#endif

#ifndef HWCAP2_SVE2
#define HWCAP2_SVE2 (1 << 1)
#endif
#ifndef HWCAP2_SVEAES
#define HWCAP2_SVEAES (1 << 2)
#endif
	const unsigned long hw2 = getauxval(AT_HWCAP2);
	if ((hw2 & HWCAP2_SVE2) && (hw2 & HWCAP2_SVEAES))
		flags |= CpuFeatures::SVE2;

#else

	// Some old auxv.h / hwcap.h do not define these. If not, treat as unsupported.
#if defined(HWCAP_NEON) && defined(HWCAP_VFPv4)
	if ((hw & HWCAP_NEON) && (hw & HWCAP_VFPv4))
		flags |= CpuFeatures::NEON | CpuFeatures::VFPv4;
#endif

	// aarch32 would check getauxval(AT_HWCAP2) & HWCAP2_AES, but we do not yet
	// support that platform, and Armv7 lacks AES entirely.

#endif

	return flags;
}
#endif

static CpuFeatures saved_flags = CpuFeatures::NONE;

CpuFeatures simd::get_cpu_features() noexcept {
	if (saved_flags == CpuFeatures::NONE)
	{
#if SIMD_ARCH_X86
		saved_flags = cpu_feature_flag_x86();
#elif SIMD_ARCH_ARM
		saved_flags = cpu_feature_flag_arm();
#endif
	}
	return saved_flags;
}
