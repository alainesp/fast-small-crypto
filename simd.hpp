//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file is part of 'SIMD-Function'
// 
// Copyright(c) 2024 by Alain Espinosa.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#ifndef SimdScalarType
#define SimdScalarType uint32_t
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Compiler
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
    #include <intrin.h>
    #define SIMD_RESTRICT __restrict
    #define SIMD_INLINE __forceinline
#else
    #define SIMD_RESTRICT __restrict__
    #ifdef __OPTIMIZE__
        #define SIMD_INLINE inline __attribute__((always_inline))
    #else
        #define SIMD_INLINE inline
    #endif
#endif  // !_MSC_VER

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Architecture
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// x86
#if defined(__i386__) || defined(_M_IX86)
#define SIMD_ARCH_X86_32 1
#else
#define SIMD_ARCH_X86_32 0
#endif

#if defined(__x86_64__) || defined(_M_X64)
#define SIMD_ARCH_X86_64 1
#else
#define SIMD_ARCH_X86_64 0
#endif

#if SIMD_ARCH_X86_32 && SIMD_ARCH_X86_64
#error "Cannot have both x86-32 and x86-64"
#endif

#if SIMD_ARCH_X86_32 || SIMD_ARCH_X86_64
#define SIMD_ARCH_X86 1
#else
#define SIMD_ARCH_X86 0
#endif

// ARM
#if defined(__ARM_ARCH_ISA_A64) || defined(__aarch64__) || defined(_M_ARM64)
#define SIMD_ARCH_ARM_A64 1
#else
#define SIMD_ARCH_ARM_A64 0
#endif

#if (defined(__ARM_ARCH) && __ARM_ARCH == 7) || (defined(_M_ARM) && _M_ARM == 7)
#define SIMD_ARCH_ARM_V7 1
#else
#define SIMD_ARCH_ARM_V7 0
#endif

#if SIMD_ARCH_ARM_A64 && SIMD_ARCH_ARM_V7
#error "Cannot have both A64 and V7"
#endif

// Any *supported* version of Arm, i.e. 7 or later
#if SIMD_ARCH_ARM_A64 || SIMD_ARCH_ARM_V7
#define SIMD_ARCH_ARM 1
#else
#define SIMD_ARCH_ARM 0
#endif

// Checks
#if SIMD_ARCH_X86 && SIMD_ARCH_ARM
#error "Cannot have both x86 and ARM"
#endif

#if SIMD_ARCH_X86 == 0 && SIMD_ARCH_ARM == 0
#error "Unsupported CPU architecture"
#endif

// Operating system
#if defined(_WIN32) || defined(_WIN64)
#define SIMD_OS_WIN 1
#else
#define SIMD_OS_WIN 0
#endif

#if defined(linux) || defined(__linux__)
#define SIMD_OS_LINUX 1
#else
#define SIMD_OS_LINUX 0
#endif

// Include files outside namespace
#if SIMD_ARCH_ARM
#include <arm_neon.h>
#endif

#if SIMD_ARCH_X86
#include <emmintrin.h> // sse2
#include <immintrin.h> // avx/avx2
#ifdef __clang__
    #include <avxintrin.h>
    // avxintrin defines __m256i and must come before avx2intrin.
    #include <avx2intrin.h>
    #include <bmi2intrin.h>  // _pext_u64
    #include <f16cintrin.h>
    #include <fmaintrin.h>
    #include <smmintrin.h>

    #include <avx512fintrin.h>
    #include <avx512vlintrin.h>
    #include <avx512bwintrin.h>
    #include <avx512vlbwintrin.h>
    #include <avx512dqintrin.h>
    #include <avx512vldqintrin.h>
    #include <avx512cdintrin.h>
    #include <avx512vlcdintrin.h>
#endif
#endif

namespace simd
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARM Neon
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
using Vec128u8  = uint8x16_t;
using Vec128i8  =  int8x16_t;
using Vec128u16 = uint16x8_t;
using Vec128i16 =  int16x8_t;
using Vec128u32 = uint32x4_t;
using Vec128i32 =  int32x4_t;
using Vec128u64 = uint64x2_t;
using Vec128i64 =  int64x2_t;
using Vec128    = __n128;
//using Vec128f16 = float16x8_t;
using Vec128f32 = float32x4_t;
#if SIMD_ARCH_ARM_A64
using Vec128f64 = float64x2_t;
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// x86 SSE2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _MSC_VER

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes" // Ignore SIMD attributes on template param
#pragma GCC diagnostic ignored "-Wpsabi" // Ignore SIMD attributes on template param

template <class RAW> struct BaseVector
{
    BaseVector() noexcept = default;
    BaseVector(const RAW raw) noexcept : raw(raw) {}
    operator RAW() const noexcept { return raw; }

    RAW raw;
};
#endif

#if SIMD_ARCH_X86
#ifdef _MSC_VER
using Vec128u8  = __m128i;
using Vec128i8  = __m128i;
using Vec128u16 = __m128i;
using Vec128i16 = __m128i;
using Vec128u32 = __m128i;
using Vec128i32 = __m128i;
using Vec128u64 = __m128i;
using Vec128i64 = __m128i;
using Vec128Int = __m128i;
using Vec128f32 = __m128 ;
using Vec128f64 = __m128d;
#else
using Vec128u8  = BaseVector<__m128i>;
using Vec128i8  = BaseVector<__m128i>;
using Vec128u16 = BaseVector<__m128i>;
using Vec128i16 = BaseVector<__m128i>;
using Vec128u32 = BaseVector<__m128i>;
using Vec128i32 = BaseVector<__m128i>;
using Vec128u64 = BaseVector<__m128i>;
using Vec128i64 = BaseVector<__m128i>;
using Vec128Int = BaseVector<__m128i>;
using Vec128f32 = BaseVector<__m128 >;
using Vec128f64 = BaseVector<__m128d>;
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// x86 AVX/AVX2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_X86
#ifdef _MSC_VER
using Vec256u8  = __m256i;
using Vec256i8  = __m256i;
using Vec256u16 = __m256i;
using Vec256i16 = __m256i;
using Vec256u32 = __m256i;
using Vec256i32 = __m256i;
using Vec256u64 = __m256i;
using Vec256i64 = __m256i;
using Vec256Int = __m256i;
using Vec256f32 = __m256 ;
using Vec256f64 = __m256d;
#else
using Vec256u8  = BaseVector<__m256i>;
using Vec256i8  = BaseVector<__m256i>;
using Vec256u16 = BaseVector<__m256i>;
using Vec256i16 = BaseVector<__m256i>;
using Vec256u32 = BaseVector<__m256i>;
using Vec256i32 = BaseVector<__m256i>;
using Vec256u64 = BaseVector<__m256i>;
using Vec256i64 = BaseVector<__m256i>;
using Vec256Int = BaseVector<__m256i>;
using Vec256f32 = BaseVector<__m256 >;
using Vec256f64 = BaseVector<__m256d>;
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// x86 AVX512
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_X86
#ifdef _MSC_VER
using Vec512u8  = __m512i;
using Vec512i8  = __m512i;
using Vec512u16 = __m512i;
using Vec512i16 = __m512i;
using Vec512u32 = __m512i;
using Vec512i32 = __m512i;
using Vec512u64 = __m512i;
using Vec512i64 = __m512i;
using Vec512Int = __m512i;
using Vec512f32 = __m512 ;
using Vec512f64 = __m512d;
#else
using Vec512u8  = BaseVector<__m512i>;
using Vec512i8  = BaseVector<__m512i>;
using Vec512u16 = BaseVector<__m512i>;
using Vec512i16 = BaseVector<__m512i>;
using Vec512u32 = BaseVector<__m512i>;
using Vec512i32 = BaseVector<__m512i>;
using Vec512u64 = BaseVector<__m512i>;
using Vec512i64 = BaseVector<__m512i>;
using Vec512Int = BaseVector<__m512i>;
using Vec512f32 = BaseVector<__m512 >;
using Vec512f64 = BaseVector<__m512d>;

#pragma GCC diagnostic pop

#endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Zero initilization
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
// Neon
static SIMD_INLINE Vec128 Zero() noexcept { return vdupq_n_u32(0); }
#endif

#if SIMD_ARCH_X86
template<class Vector> static SIMD_INLINE Vector Zero() noexcept {}
// SSE2
template<> SIMD_INLINE Vec128Int Zero() noexcept { return _mm_setzero_si128(); }
template<> SIMD_INLINE Vec128f32 Zero() noexcept { return _mm_setzero_ps();    }
template<> SIMD_INLINE Vec128f64 Zero() noexcept { return _mm_setzero_pd();    }
// AVX/AVX2
template<> SIMD_INLINE Vec256Int Zero() noexcept { return _mm256_setzero_si256(); }
template<> SIMD_INLINE Vec256f32 Zero() noexcept { return _mm256_setzero_ps();    }
template<> SIMD_INLINE Vec256f64 Zero() noexcept { return _mm256_setzero_pd();    }
// AVX512
template<> SIMD_INLINE Vec512Int Zero() noexcept { return _mm512_setzero_si512(); }
template<> SIMD_INLINE Vec512f32 Zero() noexcept { return _mm512_setzero_ps();    }
template<> SIMD_INLINE Vec512f64 Zero() noexcept { return _mm512_setzero_pd();    }
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Set
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
// Neon
static SIMD_INLINE Vec128u8  Set(const uint8_t  value) noexcept { return vdupq_n_u8 (value); }
static SIMD_INLINE Vec128i8  Set(const int8_t   value) noexcept { return vdupq_n_s8 (value); }
static SIMD_INLINE Vec128u16 Set(const uint16_t value) noexcept { return vdupq_n_u16(value); }
static SIMD_INLINE Vec128i16 Set(const int16_t  value) noexcept { return vdupq_n_s16(value); }
static SIMD_INLINE Vec128u32 Set(const uint32_t value) noexcept { return vdupq_n_u32(value); }
static SIMD_INLINE Vec128i32 Set(const int32_t  value) noexcept { return vdupq_n_s32(value); }
static SIMD_INLINE Vec128u64 Set(const uint64_t value) noexcept { return vdupq_n_u64(value); }
static SIMD_INLINE Vec128i64 Set(const int64_t  value) noexcept { return vdupq_n_s64(value); }
static SIMD_INLINE Vec128f32 Set(const float    value) noexcept { return vdupq_n_f32(value); }
//static SIMD_INLINE Vec128f64 Set(const double   value) noexcept { return vdupq_n_f64(value); }
#endif

#if SIMD_ARCH_X86
template<class T, class Vector> static SIMD_INLINE Vector Set(const T value) noexcept {}
// SSE2
template<> SIMD_INLINE Vec128u8  Set(const uint8_t  value) noexcept { return _mm_set1_epi8  (value); }
template<> SIMD_INLINE Vec128i8  Set(const int8_t   value) noexcept { return _mm_set1_epi8  (value); }
template<> SIMD_INLINE Vec128u16 Set(const uint16_t value) noexcept { return _mm_set1_epi16 (value); }
template<> SIMD_INLINE Vec128i16 Set(const int16_t  value) noexcept { return _mm_set1_epi16 (value); }
template<> SIMD_INLINE Vec128u32 Set(const uint32_t value) noexcept { return _mm_set1_epi32 (value); }
template<> SIMD_INLINE Vec128i32 Set(const int32_t  value) noexcept { return _mm_set1_epi32 (value); }
template<> SIMD_INLINE Vec128u64 Set(const uint64_t value) noexcept { return _mm_set1_epi64x(value); }
template<> SIMD_INLINE Vec128i64 Set(const int64_t  value) noexcept { return _mm_set1_epi64x(value); }
template<> SIMD_INLINE Vec128f32 Set(const float    value) noexcept { return _mm_set1_ps    (value); }
template<> SIMD_INLINE Vec128f64 Set(const double   value) noexcept { return _mm_set1_pd    (value); }
// AVX/AVX2
template<> SIMD_INLINE Vec256u8  Set(const uint8_t  value) noexcept { return _mm256_set1_epi8  (value); }
template<> SIMD_INLINE Vec256i8  Set(const int8_t   value) noexcept { return _mm256_set1_epi8  (value); }
template<> SIMD_INLINE Vec256u16 Set(const uint16_t value) noexcept { return _mm256_set1_epi16 (value); }
template<> SIMD_INLINE Vec256i16 Set(const int16_t  value) noexcept { return _mm256_set1_epi16 (value); }
template<> SIMD_INLINE Vec256u32 Set(const uint32_t value) noexcept { return _mm256_set1_epi32 (value); }
template<> SIMD_INLINE Vec256i32 Set(const int32_t  value) noexcept { return _mm256_set1_epi32 (value); }
template<> SIMD_INLINE Vec256u64 Set(const uint64_t value) noexcept { return _mm256_set1_epi64x(value); }
template<> SIMD_INLINE Vec256i64 Set(const int64_t  value) noexcept { return _mm256_set1_epi64x(value); }
template<> SIMD_INLINE Vec256f32 Set(const float    value) noexcept { return _mm256_set1_ps    (value); }
template<> SIMD_INLINE Vec256f64 Set(const double   value) noexcept { return _mm256_set1_pd    (value); }
// AVX512
template<> SIMD_INLINE Vec512u8  Set(const uint8_t  value) noexcept { return _mm512_set1_epi8 (value); }
template<> SIMD_INLINE Vec512i8  Set(const int8_t   value) noexcept { return _mm512_set1_epi8 (value); }
template<> SIMD_INLINE Vec512u16 Set(const uint16_t value) noexcept { return _mm512_set1_epi16(value); }
template<> SIMD_INLINE Vec512i16 Set(const int16_t  value) noexcept { return _mm512_set1_epi16(value); }
template<> SIMD_INLINE Vec512u32 Set(const uint32_t value) noexcept { return _mm512_set1_epi32(value); }
template<> SIMD_INLINE Vec512i32 Set(const int32_t  value) noexcept { return _mm512_set1_epi32(value); }
template<> SIMD_INLINE Vec512u64 Set(const uint64_t value) noexcept { return _mm512_set1_epi64(value); }
template<> SIMD_INLINE Vec512i64 Set(const int64_t  value) noexcept { return _mm512_set1_epi64(value); }
template<> SIMD_INLINE Vec512f32 Set(const float    value) noexcept { return _mm512_set1_ps   (value); }
template<> SIMD_INLINE Vec512f64 Set(const double   value) noexcept { return _mm512_set1_pd   (value); }
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
// Neon
template<class T = SimdScalarType> static SIMD_INLINE Vec128 load(const Vec128* SIMD_RESTRICT aligned) noexcept {

    if constexpr (std::is_same<T, float>::value)       return vld1q_f32(reinterpret_cast<const float  *>(aligned));
    //else if constexpr (std::is_same<T, double>::value) return vld1q_f64(reinterpret_cast<const double *>(aligned));
    else if constexpr (sizeof(T) == 1)                 return vld1q_s8 (reinterpret_cast<const int8_t *>(aligned));// Same instruction as unsigned
    else if constexpr (sizeof(T) == 2)                 return vld1q_s16(reinterpret_cast<const int16_t*>(aligned));
    else if constexpr (sizeof(T) == 4)                 return vld1q_s32(reinterpret_cast<const int32_t*>(aligned));
    else if constexpr (sizeof(T) == 8)                 return vld1q_s64(reinterpret_cast<const int64_t*>(aligned));
}
static SIMD_INLINE Vec128 loadu(const Vec128* SIMD_RESTRICT unaligned) noexcept { return load(unaligned); }
#endif

#if SIMD_ARCH_X86
// SSE2
static SIMD_INLINE Vec128Int load (const Vec128Int* SIMD_RESTRICT   aligned) noexcept { return _mm_load_si128(reinterpret_cast<const __m128i*>(aligned)); }
static SIMD_INLINE Vec128f32 load (const Vec128f32* SIMD_RESTRICT   aligned) noexcept { return _mm_load_ps(reinterpret_cast<const float*>(aligned)); }
static SIMD_INLINE Vec128f64 load (const Vec128f64* SIMD_RESTRICT   aligned) noexcept { return _mm_load_pd(reinterpret_cast<const double*>(aligned)); }
static SIMD_INLINE Vec128Int loadu(const Vec128Int* SIMD_RESTRICT unaligned) noexcept { return _mm_loadu_si128(reinterpret_cast<const __m128i*>(unaligned)); }
static SIMD_INLINE Vec128f32 loadu(const Vec128f32* SIMD_RESTRICT unaligned) noexcept { return _mm_loadu_ps(reinterpret_cast<const float*>(unaligned)); }
static SIMD_INLINE Vec128f64 loadu(const Vec128f64* SIMD_RESTRICT unaligned) noexcept { return _mm_loadu_pd(reinterpret_cast<const double*>(unaligned)); }
// AVX/AVX2
static SIMD_INLINE Vec256Int load (const Vec256Int* SIMD_RESTRICT   aligned) noexcept { return _mm256_load_si256(reinterpret_cast<const __m256i*>(aligned)); }
static SIMD_INLINE Vec256f32 load (const Vec256f32* SIMD_RESTRICT   aligned) noexcept { return _mm256_load_ps(reinterpret_cast<const float*>(aligned)); }
static SIMD_INLINE Vec256f64 load (const Vec256f64* SIMD_RESTRICT   aligned) noexcept { return _mm256_load_pd(reinterpret_cast<const double*>(aligned)); }
static SIMD_INLINE Vec256Int loadu(const Vec256Int* SIMD_RESTRICT unaligned) noexcept { return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(unaligned)); }
static SIMD_INLINE Vec256f32 loadu(const Vec256f32* SIMD_RESTRICT unaligned) noexcept { return _mm256_loadu_ps(reinterpret_cast<const float*>(unaligned)); }
static SIMD_INLINE Vec256f64 loadu(const Vec256f64* SIMD_RESTRICT unaligned) noexcept { return _mm256_loadu_pd(reinterpret_cast<const double*>(unaligned)); }
// AVX512
static SIMD_INLINE Vec512Int load (const Vec512Int* SIMD_RESTRICT   aligned) noexcept { return _mm512_load_si512 (  aligned); }
static SIMD_INLINE Vec512f32 load (const Vec512f32* SIMD_RESTRICT   aligned) noexcept { return _mm512_load_ps    (  aligned); }
static SIMD_INLINE Vec512f64 load (const Vec512f64* SIMD_RESTRICT   aligned) noexcept { return _mm512_load_pd    (  aligned); }
static SIMD_INLINE Vec512Int loadu(const Vec512Int* SIMD_RESTRICT unaligned) noexcept { return _mm512_loadu_si512(unaligned); }
static SIMD_INLINE Vec512f32 loadu(const Vec512f32* SIMD_RESTRICT unaligned) noexcept { return _mm512_loadu_ps   (unaligned); }
static SIMD_INLINE Vec512f64 loadu(const Vec512f64* SIMD_RESTRICT unaligned) noexcept { return _mm512_loadu_pd   (unaligned ); }
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Store
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
// Neon
template<class T = SimdScalarType> static SIMD_INLINE void store(Vec128* SIMD_RESTRICT aligned, const Vec128u8 v) noexcept {

    if constexpr (std::is_same<T, float>::value)       vst1q_f32(reinterpret_cast<float  *>(aligned), v);
    //else if constexpr (std::is_same<T, double>::value) vst1q_f64(reinterpret_cast<double *>(aligned), v);
    else if constexpr (sizeof(T) == 1)                 vst1q_s8 (reinterpret_cast<int8_t *>(aligned), v);// Same instruction as unsigned
    else if constexpr (sizeof(T) == 2)                 vst1q_s16(reinterpret_cast<int16_t*>(aligned), v);
    else if constexpr (sizeof(T) == 4)                 vst1q_s32(reinterpret_cast<int32_t*>(aligned), v);
    else if constexpr (sizeof(T) == 8)                 vst1q_s64(reinterpret_cast<int64_t*>(aligned), v);
}
static SIMD_INLINE void storeu(Vec128* SIMD_RESTRICT unaligned, const Vec128u8 v) noexcept { store(unaligned, v); }
#endif

#if SIMD_ARCH_X86
// SSE2
static SIMD_INLINE void store (Vec128Int* SIMD_RESTRICT   aligned, const Vec128Int v) noexcept { _mm_store_si128(reinterpret_cast<__m128i*>(aligned), v); }
static SIMD_INLINE void store (Vec128f32* SIMD_RESTRICT   aligned, const Vec128f32 v) noexcept { _mm_store_ps(reinterpret_cast<float*>(aligned) , v); }
static SIMD_INLINE void store (Vec128f64* SIMD_RESTRICT   aligned, const Vec128f64 v) noexcept { _mm_store_pd(reinterpret_cast<double*>(aligned), v); }
static SIMD_INLINE void storeu(Vec128Int* SIMD_RESTRICT unaligned, const Vec128Int v) noexcept { _mm_storeu_si128(reinterpret_cast<__m128i*>(unaligned), v); }
static SIMD_INLINE void storeu(Vec128f32* SIMD_RESTRICT unaligned, const Vec128f32 v) noexcept { _mm_storeu_ps(reinterpret_cast<float*>(unaligned) , v) ; }
static SIMD_INLINE void storeu(Vec128f64* SIMD_RESTRICT unaligned, const Vec128f64 v) noexcept { _mm_storeu_pd(reinterpret_cast<double*>(unaligned), v) ; }
// AVX/AVX2
static SIMD_INLINE void store (Vec256Int* SIMD_RESTRICT   aligned, const Vec256Int v) noexcept { _mm256_store_si256(reinterpret_cast<__m256i*>(aligned), v); }
static SIMD_INLINE void store (Vec256f32* SIMD_RESTRICT   aligned, const Vec256f32 v) noexcept { _mm256_store_ps(reinterpret_cast<float*>(aligned) , v); }
static SIMD_INLINE void store (Vec256f64* SIMD_RESTRICT   aligned, const Vec256f64 v) noexcept { _mm256_store_pd(reinterpret_cast<double*>(aligned), v); }
static SIMD_INLINE void storeu(Vec256Int* SIMD_RESTRICT unaligned, const Vec256Int v) noexcept { _mm256_storeu_si256(reinterpret_cast<__m256i*>(unaligned), v); }
static SIMD_INLINE void storeu(Vec256f32* SIMD_RESTRICT unaligned, const Vec256f32 v) noexcept { _mm256_storeu_ps(reinterpret_cast<float*>(unaligned) , v); }
static SIMD_INLINE void storeu(Vec256f64* SIMD_RESTRICT unaligned, const Vec256f64 v) noexcept { _mm256_storeu_pd(reinterpret_cast<double*>(unaligned), v); }
// AVX512
static SIMD_INLINE void store (Vec512Int* SIMD_RESTRICT   aligned, const Vec512Int v) noexcept { _mm512_store_si512 (  aligned, v); }
static SIMD_INLINE void store (Vec512f32* SIMD_RESTRICT   aligned, const Vec512f32 v) noexcept { _mm512_store_ps    (  aligned, v); }
static SIMD_INLINE void store (Vec512f64* SIMD_RESTRICT   aligned, const Vec512f64 v) noexcept { _mm512_store_pd    (  aligned, v); }
static SIMD_INLINE void storeu(Vec512Int* SIMD_RESTRICT unaligned, const Vec512Int v) noexcept { _mm512_storeu_si512(unaligned, v); }
static SIMD_INLINE void storeu(Vec512f32* SIMD_RESTRICT unaligned, const Vec512f32 v) noexcept { _mm512_storeu_ps   (unaligned, v); }
static SIMD_INLINE void storeu(Vec512f64* SIMD_RESTRICT unaligned, const Vec512f64 v) noexcept { _mm512_storeu_pd   (unaligned, v); }
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// And
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
// Neon
template<class Vector> static SIMD_INLINE Vector operator&(const Vector a, const Vector b) noexcept { return vandq_u32(a, b); }
#endif

#if SIMD_ARCH_X86
// SSE2
static SIMD_INLINE Vec128Int operator&(const Vec128Int a, const Vec128Int b) noexcept { return _mm_and_si128(a, b); }
static SIMD_INLINE Vec128f32 operator&(const Vec128f32 a, const Vec128f32 b) noexcept { return _mm_and_ps   (a, b); }
static SIMD_INLINE Vec128f64 operator&(const Vec128f64 a, const Vec128f64 b) noexcept { return _mm_and_pd   (a, b); }
// AVX/AVX2
static SIMD_INLINE Vec256Int operator&(const Vec256Int a, const Vec256Int b) noexcept { return _mm256_and_si256(a, b); }
static SIMD_INLINE Vec256f32 operator&(const Vec256f32 a, const Vec256f32 b) noexcept { return _mm256_and_ps   (a, b); }
static SIMD_INLINE Vec256f64 operator&(const Vec256f64 a, const Vec256f64 b) noexcept { return _mm256_and_pd   (a, b); }
// AVX512
static SIMD_INLINE Vec512Int operator&(const Vec512Int a, const Vec512Int b) noexcept { return _mm512_and_si512(a, b); }
static SIMD_INLINE Vec512f32 operator&(const Vec512f32 a, const Vec512f32 b) noexcept { return _mm512_and_ps   (a, b); }
static SIMD_INLINE Vec512f64 operator&(const Vec512f64 a, const Vec512f64 b) noexcept { return _mm512_and_pd   (a, b); }
#endif
// &=
template<class Vector, class T> static SIMD_INLINE Vector operator&=(Vector& a, const T b) noexcept { return (a = a & b);}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Andn
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_X86
// SSE2
static SIMD_INLINE Vec128Int andn(const Vec128Int a, const Vec128Int b) noexcept { return _mm_andnot_si128(a, b); }
static SIMD_INLINE Vec128f32 andn(const Vec128f32 a, const Vec128f32 b) noexcept { return _mm_andnot_ps   (a, b); }
static SIMD_INLINE Vec128f64 andn(const Vec128f64 a, const Vec128f64 b) noexcept { return _mm_andnot_pd   (a, b); }
// AVX/AVX2
static SIMD_INLINE Vec256Int andn(const Vec256Int a, const Vec256Int b) noexcept { return _mm256_andnot_si256(a, b); }
static SIMD_INLINE Vec256f32 andn(const Vec256f32 a, const Vec256f32 b) noexcept { return _mm256_andnot_ps   (a, b); }
static SIMD_INLINE Vec256f64 andn(const Vec256f64 a, const Vec256f64 b) noexcept { return _mm256_andnot_pd   (a, b); }
// AVX512
static SIMD_INLINE Vec512Int andn(const Vec512Int a, const Vec512Int b) noexcept { return _mm512_andnot_si512(a, b); }
static SIMD_INLINE Vec512f32 andn(const Vec512f32 a, const Vec512f32 b) noexcept { return _mm512_andnot_ps   (a, b); }
static SIMD_INLINE Vec512f64 andn(const Vec512f64 a, const Vec512f64 b) noexcept { return _mm512_andnot_pd   (a, b); }
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
// Neon
template<class Vector> static SIMD_INLINE Vector operator|(const Vector a, const Vector b) noexcept { return vorrq_u32(a, b); }
#endif

#if SIMD_ARCH_X86
// SSE2
static SIMD_INLINE Vec128Int operator|(const Vec128Int a, const Vec128Int b) noexcept { return _mm_or_si128(a, b); }
static SIMD_INLINE Vec128f32 operator|(const Vec128f32 a, const Vec128f32 b) noexcept { return _mm_or_ps   (a, b); }
static SIMD_INLINE Vec128f64 operator|(const Vec128f64 a, const Vec128f64 b) noexcept { return _mm_or_pd   (a, b); }
// AVX/AVX2
static SIMD_INLINE Vec256Int operator|(const Vec256Int a, const Vec256Int b) noexcept { return _mm256_or_si256(a, b); }
static SIMD_INLINE Vec256f32 operator|(const Vec256f32 a, const Vec256f32 b) noexcept { return _mm256_or_ps   (a, b); }
static SIMD_INLINE Vec256f64 operator|(const Vec256f64 a, const Vec256f64 b) noexcept { return _mm256_or_pd   (a, b); }
// AVX512
static SIMD_INLINE Vec512Int operator|(const Vec512Int a, const Vec512Int b) noexcept { return _mm512_or_si512(a, b); }
static SIMD_INLINE Vec512f32 operator|(const Vec512f32 a, const Vec512f32 b) noexcept { return _mm512_or_ps   (a, b); }
static SIMD_INLINE Vec512f64 operator|(const Vec512f64 a, const Vec512f64 b) noexcept { return _mm512_or_pd   (a, b); }
#endif
// |=
template<class Vector, class T> static SIMD_INLINE Vector operator|=(Vector& a, const T b) noexcept { return (a = a | b); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// XOR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
// Neon
template<class Vector> static SIMD_INLINE Vector operator^(const Vector a, const Vector b) noexcept { return veorq_u32(a, b); }
#endif

#if SIMD_ARCH_X86
// SSE2
static SIMD_INLINE Vec128Int operator^(const Vec128Int a, const Vec128Int b) noexcept { return _mm_xor_si128(a, b); }
static SIMD_INLINE Vec128f32 operator^(const Vec128f32 a, const Vec128f32 b) noexcept { return _mm_xor_ps   (a, b); }
static SIMD_INLINE Vec128f64 operator^(const Vec128f64 a, const Vec128f64 b) noexcept { return _mm_xor_pd   (a, b); }
// AVX/AVX2
static SIMD_INLINE Vec256Int operator^(const Vec256Int a, const Vec256Int b) noexcept { return _mm256_xor_si256(a, b); }
static SIMD_INLINE Vec256f32 operator^(const Vec256f32 a, const Vec256f32 b) noexcept { return _mm256_xor_ps   (a, b); }
static SIMD_INLINE Vec256f64 operator^(const Vec256f64 a, const Vec256f64 b) noexcept { return _mm256_xor_pd   (a, b); }
// AVX512
static SIMD_INLINE Vec512Int operator^(const Vec512Int a, const Vec512Int b) noexcept { return _mm512_xor_si512(a, b); }
static SIMD_INLINE Vec512f32 operator^(const Vec512f32 a, const Vec512f32 b) noexcept { return _mm512_xor_ps   (a, b); }
static SIMD_INLINE Vec512f64 operator^(const Vec512f64 a, const Vec512f64 b) noexcept { return _mm512_xor_pd   (a, b); }
#endif
// ^=
template<class Vector, class T> static SIMD_INLINE Vector operator^=(Vector& a, const T b) noexcept { return (a = a ^ b); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sum
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vector + Vector
#if SIMD_ARCH_ARM
// Neon
template<class T = SimdScalarType> static SIMD_INLINE Vec128 operator+(const Vec128 a, const Vec128 b) noexcept {

    if constexpr (std::is_same<T, float>::value)       return vaddq_f32(a, b);
    //else if constexpr (std::is_same<T, double>::value) return vaddq_f64(a, b);
    else if constexpr (sizeof(T) == 1)                 return vaddq_s8 (a, b);// Same instruction as unsigned
    else if constexpr (sizeof(T) == 2)                 return vaddq_s16(a, b);
    else if constexpr (sizeof(T) == 4)                 return vaddq_s32(a, b);
    else if constexpr (sizeof(T) == 8)                 return vaddq_s64(a, b);
}

static SIMD_INLINE Vec128u8  operator+(const Vec128u8  a, const uint8_t  b) noexcept { return vaddq_u8 (a, Set(b)); }
static SIMD_INLINE Vec128i8  operator+(const Vec128i8  a, const int8_t   b) noexcept { return vaddq_s8 (a, Set(b)); }
static SIMD_INLINE Vec128u16 operator+(const Vec128u16 a, const uint16_t b) noexcept { return vaddq_u16(a, Set(b)); }
static SIMD_INLINE Vec128i16 operator+(const Vec128i16 a, const int16_t  b) noexcept { return vaddq_s16(a, Set(b)); }
static SIMD_INLINE Vec128u32 operator+(const Vec128u32 a, const uint32_t b) noexcept { return vaddq_u32(a, Set(b)); }
static SIMD_INLINE Vec128i32 operator+(const Vec128i32 a, const int32_t  b) noexcept { return vaddq_s32(a, Set(b)); }
static SIMD_INLINE Vec128u64 operator+(const Vec128u64 a, const uint64_t b) noexcept { return vaddq_u64(a, Set(b)); }
static SIMD_INLINE Vec128i64 operator+(const Vec128i64 a, const int64_t  b) noexcept { return vaddq_s64(a, Set(b)); }
static SIMD_INLINE Vec128f32 operator+(const Vec128f32 a, const float    b) noexcept { return vaddq_f32(a, Set(b)); }
//static SIMD_INLINE Vec128f64 operator+(const Vec128f64 a, const double   b) noexcept { return vaddq_f64(a, Set(b)); }
#endif

#if SIMD_ARCH_X86
// SSE2
template<class T = SimdScalarType> static SIMD_INLINE Vec128Int operator+(const Vec128Int a, const Vec128Int b) noexcept {
    if constexpr (sizeof(T) == 1)      return _mm_add_epi8 (a, b);
    else if constexpr (sizeof(T) == 2) return _mm_add_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm_add_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm_add_epi64(a, b);
}
static SIMD_INLINE Vec128f32 operator+(const Vec128f32 a, const Vec128f32 b) noexcept { return _mm_add_ps(a, b); }
static SIMD_INLINE Vec128f64 operator+(const Vec128f64 a, const Vec128f64 b) noexcept { return _mm_add_pd(a, b); }
// AVX/AVX2
template<class T = SimdScalarType> static SIMD_INLINE Vec256Int operator+(const Vec256Int a, const Vec256Int b) noexcept {
    if constexpr (sizeof(T) == 1)      return _mm256_add_epi8(a, b);
    else if constexpr (sizeof(T) == 2) return _mm256_add_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm256_add_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm256_add_epi64(a, b);
}
static SIMD_INLINE Vec256f32 operator+(const Vec256f32 a, const Vec256f32 b) noexcept { return _mm256_add_ps(a, b); }
static SIMD_INLINE Vec256f64 operator+(const Vec256f64 a, const Vec256f64 b) noexcept { return _mm256_add_pd(a, b); }
// AVX512
template<class T = SimdScalarType> static SIMD_INLINE Vec512Int operator+(const Vec512Int a, const Vec512Int b) noexcept {
    if constexpr (sizeof(T) == 1)      return _mm512_add_epi8(a, b);
    else if constexpr (sizeof(T) == 2) return _mm512_add_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm512_add_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm512_add_epi64(a, b);
}
static SIMD_INLINE Vec512f32 operator+(const Vec512f32 a, const Vec512f32 b) noexcept { return _mm512_add_ps(a, b); }
static SIMD_INLINE Vec512f64 operator+(const Vec512f64 a, const Vec512f64 b) noexcept { return _mm512_add_pd(a, b); }

// Vector + Scalar
// SSE2
static SIMD_INLINE Vec128u8  operator+(const Vec128u8  a, const uint8_t  b) noexcept { return _mm_add_epi8 (a, Set<uint8_t , Vec128u8 >(b)); }
static SIMD_INLINE Vec128i8  operator+(const Vec128i8  a, const int8_t   b) noexcept { return _mm_add_epi8 (a, Set<int8_t  , Vec128i8 >(b)); }
static SIMD_INLINE Vec128u16 operator+(const Vec128u16 a, const uint16_t b) noexcept { return _mm_add_epi16(a, Set<uint16_t, Vec128u16>(b)); }
static SIMD_INLINE Vec128i16 operator+(const Vec128i16 a, const int16_t  b) noexcept { return _mm_add_epi16(a, Set<int16_t , Vec128i16>(b)); }
static SIMD_INLINE Vec128u32 operator+(const Vec128u32 a, const uint32_t b) noexcept { return _mm_add_epi32(a, Set<uint32_t, Vec128u32>(b)); }
static SIMD_INLINE Vec128i32 operator+(const Vec128i32 a, const int32_t  b) noexcept { return _mm_add_epi32(a, Set<int32_t , Vec128i32>(b)); }
static SIMD_INLINE Vec128u64 operator+(const Vec128u64 a, const uint64_t b) noexcept { return _mm_add_epi64(a, Set<uint64_t, Vec128u64>(b)); }
static SIMD_INLINE Vec128i64 operator+(const Vec128i64 a, const int64_t  b) noexcept { return _mm_add_epi64(a, Set<int64_t , Vec128i64>(b)); }
static SIMD_INLINE Vec128f32 operator+(const Vec128f32 a, const float    b) noexcept { return _mm_add_ps   (a, Set<float   , Vec128f32>(b)); }
static SIMD_INLINE Vec128f64 operator+(const Vec128f64 a, const double   b) noexcept { return _mm_add_pd   (a, Set<double  , Vec128f64>(b)); }
// AVX/AVX2
static SIMD_INLINE Vec256u8  operator+(const Vec256u8  a, const uint8_t  b) noexcept { return _mm256_add_epi8 (a, Set<uint8_t , Vec256u8 >(b)); }
static SIMD_INLINE Vec256i8  operator+(const Vec256i8  a, const int8_t   b) noexcept { return _mm256_add_epi8 (a, Set<int8_t  , Vec256i8 >(b)); }
static SIMD_INLINE Vec256u16 operator+(const Vec256u16 a, const uint16_t b) noexcept { return _mm256_add_epi16(a, Set<uint16_t, Vec256u16>(b)); }
static SIMD_INLINE Vec256i16 operator+(const Vec256i16 a, const int16_t  b) noexcept { return _mm256_add_epi16(a, Set<int16_t , Vec256i16>(b)); }
static SIMD_INLINE Vec256u32 operator+(const Vec256u32 a, const uint32_t b) noexcept { return _mm256_add_epi32(a, Set<uint32_t, Vec256u32>(b)); }
static SIMD_INLINE Vec256i32 operator+(const Vec256i32 a, const int32_t  b) noexcept { return _mm256_add_epi32(a, Set<int32_t , Vec256i32>(b)); }
static SIMD_INLINE Vec256u64 operator+(const Vec256u64 a, const uint64_t b) noexcept { return _mm256_add_epi64(a, Set<uint64_t, Vec256u64>(b)); }
static SIMD_INLINE Vec256i64 operator+(const Vec256i64 a, const int64_t  b) noexcept { return _mm256_add_epi64(a, Set<int64_t , Vec256i64>(b)); }
static SIMD_INLINE Vec256f32 operator+(const Vec256f32 a, const float    b) noexcept { return _mm256_add_ps   (a, Set<float   , Vec256f32>(b)); }
static SIMD_INLINE Vec256f64 operator+(const Vec256f64 a, const double   b) noexcept { return _mm256_add_pd   (a, Set<double  , Vec256f64>(b)); }
// AVX512
static SIMD_INLINE Vec512u8  operator+(const Vec512u8  a, const uint8_t  b) noexcept { return _mm512_add_epi8 (a, Set<uint8_t , Vec512u8 >(b)); }
static SIMD_INLINE Vec512i8  operator+(const Vec512i8  a, const int8_t   b) noexcept { return _mm512_add_epi8 (a, Set<int8_t  , Vec512i8 >(b)); }
static SIMD_INLINE Vec512u16 operator+(const Vec512u16 a, const uint16_t b) noexcept { return _mm512_add_epi16(a, Set<uint16_t, Vec512u16>(b)); }
static SIMD_INLINE Vec512i16 operator+(const Vec512i16 a, const int16_t  b) noexcept { return _mm512_add_epi16(a, Set<int16_t , Vec512i16>(b)); }
static SIMD_INLINE Vec512u32 operator+(const Vec512u32 a, const uint32_t b) noexcept { return _mm512_add_epi32(a, Set<uint32_t, Vec512u32>(b)); }
static SIMD_INLINE Vec512i32 operator+(const Vec512i32 a, const int32_t  b) noexcept { return _mm512_add_epi32(a, Set<int32_t , Vec512i32>(b)); }
static SIMD_INLINE Vec512u64 operator+(const Vec512u64 a, const uint64_t b) noexcept { return _mm512_add_epi64(a, Set<uint64_t, Vec512u64>(b)); }
static SIMD_INLINE Vec512i64 operator+(const Vec512i64 a, const int64_t  b) noexcept { return _mm512_add_epi64(a, Set<int64_t , Vec512i64>(b)); }
static SIMD_INLINE Vec512f32 operator+(const Vec512f32 a, const float    b) noexcept { return _mm512_add_ps   (a, Set<float   , Vec512f32>(b)); }
static SIMD_INLINE Vec512f64 operator+(const Vec512f64 a, const double   b) noexcept { return _mm512_add_pd   (a, Set<double  , Vec512f64>(b)); }
#endif
// Vector += T
template<class Vector, class T> static SIMD_INLINE Vector operator+=(Vector& a, const T b) noexcept { return (a = a + b); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Substration
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
// Neon
template<class T = SimdScalarType> static SIMD_INLINE Vec128 operator-(const Vec128 a, const Vec128 b) noexcept {

    if constexpr (std::is_same<T, float>::value)       return vsubq_f32(a, b);
    //else if constexpr (std::is_same<T, double>::value) return vsubq_f64(a, b);
    else if constexpr (sizeof(T) == 1)                 return vsubq_s8(a, b);// Same instruction as unsigned
    else if constexpr (sizeof(T) == 2)                 return vsubq_s16(a, b);
    else if constexpr (sizeof(T) == 4)                 return vsubq_s32(a, b);
    else if constexpr (sizeof(T) == 8)                 return vsubq_s64(a, b);
}

static SIMD_INLINE Vec128u8  operator-(const Vec128u8  a, const uint8_t  b) noexcept { return vsubq_u8 (a, Set(b)); }
static SIMD_INLINE Vec128i8  operator-(const Vec128i8  a, const int8_t   b) noexcept { return vsubq_s8 (a, Set(b)); }
static SIMD_INLINE Vec128u16 operator-(const Vec128u16 a, const uint16_t b) noexcept { return vsubq_u16(a, Set(b)); }
static SIMD_INLINE Vec128i16 operator-(const Vec128i16 a, const int16_t  b) noexcept { return vsubq_s16(a, Set(b)); }
static SIMD_INLINE Vec128u32 operator-(const Vec128u32 a, const uint32_t b) noexcept { return vsubq_u32(a, Set(b)); }
static SIMD_INLINE Vec128i32 operator-(const Vec128i32 a, const int32_t  b) noexcept { return vsubq_s32(a, Set(b)); }
static SIMD_INLINE Vec128u64 operator-(const Vec128u64 a, const uint64_t b) noexcept { return vsubq_u64(a, Set(b)); }
static SIMD_INLINE Vec128i64 operator-(const Vec128i64 a, const int64_t  b) noexcept { return vsubq_s64(a, Set(b)); }
static SIMD_INLINE Vec128f32 operator-(const Vec128f32 a, const float    b) noexcept { return vsubq_f32(a, Set(b)); }
//static SIMD_INLINE Vec128f64 operator-(const Vec128f64 a, const double   b) noexcept { return vsubq_f64(a, Set(b)); }
#endif

#if SIMD_ARCH_X86
// SSE2
template<class T = SimdScalarType> static SIMD_INLINE Vec128Int operator-(const Vec128Int a, const Vec128Int b) noexcept {
    if constexpr (sizeof(T) == 1)      return _mm_sub_epi8(a, b);
    else if constexpr (sizeof(T) == 2) return _mm_sub_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm_sub_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm_sub_epi64(a, b);
}
static SIMD_INLINE Vec128f32 operator-(const Vec128f32 a, const Vec128f32 b) noexcept { return _mm_sub_ps(a, b); }
static SIMD_INLINE Vec128f64 operator-(const Vec128f64 a, const Vec128f64 b) noexcept { return _mm_sub_pd(a, b); }
// AVX/AVX2
template<class T = SimdScalarType> static SIMD_INLINE Vec256Int operator-(const Vec256Int a, const Vec256Int b) noexcept {
    if constexpr (sizeof(T) == 1)      return _mm256_sub_epi8(a, b);
    else if constexpr (sizeof(T) == 2) return _mm256_sub_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm256_sub_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm256_sub_epi64(a, b);
}
static SIMD_INLINE Vec256f32 operator-(const Vec256f32 a, const Vec256f32 b) noexcept { return _mm256_sub_ps(a, b); }
static SIMD_INLINE Vec256f64 operator-(const Vec256f64 a, const Vec256f64 b) noexcept { return _mm256_sub_pd(a, b); }
// AVX512
template<class T = SimdScalarType> static SIMD_INLINE Vec512Int operator-(const Vec512Int a, const Vec512Int b) noexcept {
    if constexpr (sizeof(T) == 1)      return _mm512_sub_epi8(a, b);
    else if constexpr (sizeof(T) == 2) return _mm512_sub_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm512_sub_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm512_sub_epi64(a, b);
}
static SIMD_INLINE Vec512f32 operator-(const Vec512f32 a, const Vec512f32 b) noexcept { return _mm512_sub_ps(a, b); }
static SIMD_INLINE Vec512f64 operator-(const Vec512f64 a, const Vec512f64 b) noexcept { return _mm512_sub_pd(a, b); }
#endif
// Vector -= T
template<class Vector, class T> static SIMD_INLINE Vector operator-=(Vector& a, const T b) noexcept { return (a = a - b); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Multiplication
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
// Neon
template<class T = SimdScalarType> static SIMD_INLINE Vec128 operator*(const Vec128 a, const Vec128 b) noexcept {

    if constexpr (std::is_same<T, float>::value)       return vmulq_f32(a, b);
    //else if constexpr (std::is_same<T, double>::value) return vmulq_f64(a, b);
    else if constexpr (sizeof(T) == 1)                 return vmulq_s8 (a, b);// Same instruction as unsigned
    else if constexpr (sizeof(T) == 2)                 return vmulq_s16(a, b);
    else if constexpr (sizeof(T) == 4)                 return vmulq_s32(a, b);
}

static SIMD_INLINE Vec128u8  operator*(const Vec128u8  a, const uint8_t  b) noexcept { return vmulq_u8 (a, Set(b)); }
static SIMD_INLINE Vec128i8  operator*(const Vec128i8  a, const int8_t   b) noexcept { return vmulq_s8 (a, Set(b)); }
static SIMD_INLINE Vec128u16 operator*(const Vec128u16 a, const uint16_t b) noexcept { return vmulq_n_u16(a, b); }
static SIMD_INLINE Vec128i16 operator*(const Vec128i16 a, const int16_t  b) noexcept { return vmulq_n_s16(a, b); }
static SIMD_INLINE Vec128u32 operator*(const Vec128u32 a, const uint32_t b) noexcept { return vmulq_n_u32(a, b); }
static SIMD_INLINE Vec128i32 operator*(const Vec128i32 a, const int32_t  b) noexcept { return vmulq_n_s32(a, b); }
static SIMD_INLINE Vec128f32 operator*(const Vec128f32 a, const float    b) noexcept { return vmulq_n_f32(a, b); }
//static SIMD_INLINE Vec128f64 operator*(const Vec128f64 a, const double   b) noexcept { return vmulq_n_f64(a, b); }
#endif

#if SIMD_ARCH_X86
// SSE2
template<class T = SimdScalarType> static SIMD_INLINE Vec128Int operator*(const Vec128Int a, const Vec128Int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm_mullo_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm_mullo_epi32(a, b);// highway gave a SSSE3 version
}
static SIMD_INLINE Vec128f32 operator*(const Vec128f32 a, const Vec128f32 b) noexcept { return _mm_mul_ps(a, b); }
static SIMD_INLINE Vec128f64 operator*(const Vec128f64 a, const Vec128f64 b) noexcept { return _mm_mul_pd(a, b); }
// AVX/AVX2
template<class T = SimdScalarType> static SIMD_INLINE Vec256Int operator*(const Vec256Int a, const Vec256Int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm256_mullo_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm256_mullo_epi32(a, b);
}
static SIMD_INLINE Vec256f32 operator*(const Vec256f32 a, const Vec256f32 b) noexcept { return _mm256_mul_ps(a, b); }
static SIMD_INLINE Vec256f64 operator*(const Vec256f64 a, const Vec256f64 b) noexcept { return _mm256_mul_pd(a, b); }
// AVX512
template<class T = SimdScalarType> static SIMD_INLINE Vec512Int operator*(const Vec512Int a, const Vec512Int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm512_mullo_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm512_mullo_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm512_mullo_epi64(a, b);
}
static SIMD_INLINE Vec512f32 operator*(const Vec512f32 a, const Vec512f32 b) noexcept { return _mm512_mul_ps(a, b); }
static SIMD_INLINE Vec512f64 operator*(const Vec512f64 a, const Vec512f64 b) noexcept { return _mm512_mul_pd(a, b); }
#endif
// Vector *= T
template<class Vector, class T> static SIMD_INLINE Vector operator*=(Vector& a, const T b) noexcept { return (a = a * b); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Division
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
// Neon: Not supported
#endif

#if SIMD_ARCH_X86
// SSE2
static SIMD_INLINE Vec128f32 operator/(const Vec128f32 a, const Vec128f32 b) noexcept { return _mm_div_ps(a, b); }
static SIMD_INLINE Vec128f64 operator/(const Vec128f64 a, const Vec128f64 b) noexcept { return _mm_div_pd(a, b); }
// AVX/AVX2
static SIMD_INLINE Vec256f32 operator/(const Vec256f32 a, const Vec256f32 b) noexcept { return _mm256_div_ps(a, b); }
static SIMD_INLINE Vec256f64 operator/(const Vec256f64 a, const Vec256f64 b) noexcept { return _mm256_div_pd(a, b); }
// AVX512
static SIMD_INLINE Vec512f32 operator/(const Vec512f32 a, const Vec512f32 b) noexcept { return _mm512_div_ps(a, b); }
static SIMD_INLINE Vec512f64 operator/(const Vec512f64 a, const Vec512f64 b) noexcept { return _mm512_div_pd(a, b); }
#endif
// Vector /= T
template<class Vector, class T> static SIMD_INLINE Vector operator/=(Vector& a, const T b) noexcept { return (a = a / b); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shifts
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if SIMD_ARCH_ARM
// Neon
template<class T = SimdScalarType> static SIMD_INLINE Vec128 operator<<(const Vec128 a, const Vec128 shift_amount) noexcept {

    if constexpr (sizeof(T) == 1)      return vshlq_u8 (a, shift_amount);// Same instruction as signed
    else if constexpr (sizeof(T) == 2) return vshlq_u16(a, shift_amount);
    else if constexpr (sizeof(T) == 4) return vshlq_u32(a, shift_amount);
    else if constexpr (sizeof(T) == 8) return vshlq_u64(a, shift_amount);
}
template<class T = SimdScalarType> static SIMD_INLINE Vec128 operator<<(const Vec128 a, const int shift_amount) noexcept {

    if constexpr (sizeof(T) == 1)      return vshlq_n_u8 (a, shift_amount);// Same instruction as signed
    else if constexpr (sizeof(T) == 2) return vshlq_n_u16(a, shift_amount);
    else if constexpr (sizeof(T) == 4) return vshlq_n_u32(a, shift_amount);
    else if constexpr (sizeof(T) == 8) return vshlq_n_u64(a, shift_amount);
}
// Unsupported
//template<class T = SimdScalarType> static SIMD_INLINE Vec128 operator>>(const Vec128 a, const Vec128 shift_amount) noexcept {
//
//    if constexpr (sizeof(T) == 1)      return vshrq_u8 (a, shift_amount);// Same instruction as signed
//    else if constexpr (sizeof(T) == 2) return vshrq_u16(a, shift_amount);
//    else if constexpr (sizeof(T) == 4) return vshrq_u32(a, shift_amount);
//    else if constexpr (sizeof(T) == 8) return vshrq_u64(a, shift_amount);
//}
template<class T = SimdScalarType> static SIMD_INLINE Vec128 operator>>(const Vec128 a, const int shift_amount) noexcept {

    if constexpr (sizeof(T) == 1)      return vshrq_n_u8 (a, shift_amount);// Same instruction as signed
    else if constexpr (sizeof(T) == 2) return vshrq_n_u16(a, shift_amount);
    else if constexpr (sizeof(T) == 4) return vshrq_n_u32(a, shift_amount);
    else if constexpr (sizeof(T) == 8) return vshrq_n_u64(a, shift_amount);
}
#endif

// Vector << Vector
#if SIMD_ARCH_X86
// SSE2
template<class T = SimdScalarType> static SIMD_INLINE Vec128Int operator<<(const Vec128Int a, const Vec128Int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm_sll_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm_sll_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm_sll_epi64(a, b);
}
// AVX/AVX2
template<class T = SimdScalarType> static SIMD_INLINE Vec256Int operator<<(const Vec256Int a, const Vec128Int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm256_sll_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm256_sll_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm256_sll_epi64(a, b);
}
// AVX512
template<class T = SimdScalarType> static SIMD_INLINE Vec512Int operator<<(const Vec512Int a, const Vec128Int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm512_sll_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm512_sll_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm512_sll_epi64(a, b);
}

// Vector << int
// SSE2
template<class T = SimdScalarType> static SIMD_INLINE Vec128Int operator<<(const Vec128Int a, const int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm_slli_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm_slli_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm_slli_epi64(a, b);
}
// AVX/AVX2
template<class T = SimdScalarType> static SIMD_INLINE Vec256Int operator<<(const Vec256Int a, const int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm256_slli_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm256_slli_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm256_slli_epi64(a, b);
}
// AVX512
template<class T = SimdScalarType> static SIMD_INLINE Vec512Int operator<<(const Vec512Int a, const int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm512_slli_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm512_slli_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm512_slli_epi64(a, b);
}

// Vector >> Vector
// SSE2
template<class T = SimdScalarType> static SIMD_INLINE Vec128Int operator>>(const Vec128Int a, const Vec128Int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm_srl_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm_srl_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm_srl_epi64(a, b);
}
// AVX/AVX2
template<class T = SimdScalarType> static SIMD_INLINE Vec256Int operator>>(const Vec256Int a, const Vec128Int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm256_srl_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm256_srl_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm256_srl_epi64(a, b);
}
// AVX512
template<class T = SimdScalarType> static SIMD_INLINE Vec512Int operator>>(const Vec512Int a, const Vec128Int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm512_srl_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm512_srl_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm512_srl_epi64(a, b);
}

// Vector >> int
// SSE2
template<class T = SimdScalarType> static SIMD_INLINE Vec128Int operator>>(const Vec128Int a, const int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm_srli_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm_srli_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm_srli_epi64(a, b);
}
// AVX/AVX2
template<class T = SimdScalarType> static SIMD_INLINE Vec256Int operator>>(const Vec256Int a, const int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm256_srli_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm256_srli_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm256_srli_epi64(a, b);
}
// AVX512
template<class T = SimdScalarType> static SIMD_INLINE Vec512Int operator>>(const Vec512Int a, const int b) noexcept {
    if constexpr (sizeof(T) == 2)      return _mm512_srli_epi16(a, b);
    else if constexpr (sizeof(T) == 4) return _mm512_srli_epi32(a, b);
    else if constexpr (sizeof(T) == 8) return _mm512_srli_epi64(a, b);
}
#endif

// Vector <<= T, Vector >>= T
template<class Vector, class T> static SIMD_INLINE Vector operator<<=(Vector& a, const T b) noexcept { return (a = a << b); }
template<class Vector, class T> static SIMD_INLINE Vector operator>>=(Vector& a, const T b) noexcept { return (a = a >> b); }

// Rotation
template<class Vector, class T = SimdScalarType> static SIMD_INLINE Vector rotl(const Vector a, const int b) noexcept { return (a << b) | (a >> (sizeof(T) * 8 - b)); }
template<class Vector, class T = SimdScalarType> static SIMD_INLINE Vector rotr(const Vector a, const int b) noexcept { return (a >> b) | (a << (sizeof(T) * 8 - b)); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CPU feature detection
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class CpuFeatures : uint32_t {
	NONE       = 0,
	PLAIN_C    = 1 <<  0,
#if SIMD_ARCH_ARM
	NEON       = 1 <<  1,
	VFPv4      = 1 <<  2,
	AES        = 1 <<  3,

	SVE        = 1 <<  4,
	SVE2       = 1 <<  5
#elif SIMD_ARCH_X86
	SSE        = 1 <<  1,
	SSE2       = 1 <<  2,
	SSE3       = 1 <<  3,
	SSSE3      = 1 <<  4,
	SSE41      = 1 <<  5,
	SSE42      = 1 <<  6,
	CLMUL      = 1 <<  7,
	AES        = 1 <<  8,

	AVX        = 1 <<  9,
	AVX2       = 1 << 10,
	F16C       = 1 << 11,
	FMA        = 1 << 12,
	LZCNT      = 1 << 13,
	BMI        = 1 << 14,
	BMI2       = 1 << 15,

    AVX512 = 1 << 16, // The same as AVX512F
	AVX512F    = 1 << 16,
	AVX512VL   = 1 << 17,
	AVX512CD   = 1 << 18,
	AVX512DQ   = 1 << 19,
	AVX512BW   = 1 << 20,
	AVX512FP16 = 1 << 21,

	VNNI       = 1 << 22,
	VPCLMULQDQ = 1 << 23,
	VBMI       = 1 << 24,
	VBMI2      = 1 << 25,
	VAES       = 1 << 26,
	POPCNTDQ   = 1 << 27,
	BITALG     = 1 << 28,
	GFNI	   = 1 << 29
#endif
};
static SIMD_INLINE bool operator&(const CpuFeatures lhs, const CpuFeatures rhs) noexcept
{
    return static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs);
}
static SIMD_INLINE CpuFeatures operator|(const CpuFeatures lhs, const CpuFeatures rhs) noexcept
{
    return static_cast<CpuFeatures>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}
static SIMD_INLINE CpuFeatures operator|=(CpuFeatures& lhs, const CpuFeatures rhs) noexcept
{
    return (lhs = static_cast<CpuFeatures>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs)));
}
/// <summary>
/// CPU features detection
/// </summary>
/// <returns></returns>
CpuFeatures get_cpu_features() noexcept;
static SIMD_INLINE bool cpu_supports(CpuFeatures feature) noexcept { return feature & simd::get_cpu_features(); }

}
