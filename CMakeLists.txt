###############################################################################################################
# This file is part of 'Fast-Small-Crypto'
# 
# Copyright (c) 2024 by Alain Espinosa.
###############################################################################################################
cmake_minimum_required (VERSION 3.12)

project (fast-small-crypto VERSION 1.0.0.0 DESCRIPTION "Fast crypto implementations for small data"
			HOMEPAGE_URL https://github.com/alainesp/fast-small-crypto LANGUAGES CXX)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

###############################################################################################################
# Library configuration
###############################################################################################################
option(FSC_BUILD_EXAMPLE   "Build the example"           OFF)
option(FSC_BUILD_BENCHMARK "Build the benchmark testing" OFF)
option(FSC_BUILD_TESTS     "Build the tests"             OFF)

if(CMAKE_COMPILER_IS_GNUCXX)
	set_source_files_properties("src/md4_avx.cpp"    "src/md5_avx.cpp"    "src/sha1_avx.cpp"    "src/sha256_avx.cpp"    "src/sha512_avx.cpp"    PROPERTIES COMPILE_FLAGS -mavx)
	set_source_files_properties("src/md4_avx2.cpp"   "src/md5_avx2.cpp"   "src/sha1_avx2.cpp"   "src/sha256_avx2.cpp"   "src/sha512_avx2.cpp"   PROPERTIES COMPILE_FLAGS -mavx2)
	set_source_files_properties("src/md4_avx512.cpp" "src/md5_avx512.cpp" "src/sha1_avx512.cpp" "src/sha256_avx512.cpp" "src/sha512_avx512.cpp" PROPERTIES COMPILE_FLAGS -mavx512f)
    set_source_files_properties("src/x86_shani.cpp" PROPERTIES COMPILE_FLAGS "-msha -msse4.1")
    set_source_files_properties("src/x86_aesni.cpp" PROPERTIES COMPILE_FLAGS -maes)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set_source_files_properties("src/md4_avx.cpp"    "src/md5_avx.cpp"    "src/sha1_avx.cpp"    "src/sha256_avx.cpp"    "src/sha512_avx.cpp"    PROPERTIES COMPILE_FLAGS -mavx)
	set_source_files_properties("src/md4_avx2.cpp"   "src/md5_avx2.cpp"   "src/sha1_avx2.cpp"   "src/sha256_avx2.cpp"   "src/sha512_avx2.cpp"   PROPERTIES COMPILE_FLAGS -mavx2)
	set_source_files_properties("src/md4_avx512.cpp" "src/md5_avx512.cpp" "src/sha1_avx512.cpp" "src/sha256_avx512.cpp" "src/sha512_avx512.cpp" PROPERTIES COMPILE_FLAGS -mavx512f)
    set_source_files_properties("src/x86_shani.cpp" PROPERTIES COMPILE_FLAGS "-msha -msse4.1")
    set_source_files_properties("src/x86_aesni.cpp" PROPERTIES COMPILE_FLAGS -maes)
elseif(MSVC)
	set_source_files_properties("src/md4_avx.cpp"    "src/md5_avx.cpp"    "src/sha1_avx.cpp"    "src/sha256_avx.cpp"    "src/sha512_avx.cpp"    PROPERTIES COMPILE_FLAGS /arch:AVX)
	set_source_files_properties("src/md4_avx2.cpp"   "src/md5_avx2.cpp"   "src/sha1_avx2.cpp"   "src/sha256_avx2.cpp"   "src/sha512_avx2.cpp"   PROPERTIES COMPILE_FLAGS /arch:AVX2)
	set_source_files_properties("src/md4_avx512.cpp" "src/md5_avx512.cpp" "src/sha1_avx512.cpp" "src/sha256_avx512.cpp" "src/sha512_avx512.cpp" PROPERTIES COMPILE_FLAGS /arch:AVX512)
    set_source_files_properties("src/x86_shani.cpp" PROPERTIES COMPILE_FLAGS /arch:SSE2)
    set_source_files_properties("src/x86_aesni.cpp" PROPERTIES COMPILE_FLAGS /arch:SSE2)
endif()

add_library(FSC STATIC "src/cpuid.cpp" "src/x86_shani.cpp" "src/aes.cpp" "src/x86_aesni.cpp"
    "src/md4.cpp"        "src/md5.cpp"        "src/sha1.cpp"        "src/sha256.cpp"        "src/sha512.cpp"
    "src/md4_avx.cpp"    "src/md5_avx.cpp"    "src/sha1_avx.cpp"    "src/sha256_avx.cpp"    "src/sha512_avx.cpp"
    "src/md4_avx2.cpp"   "src/md5_avx2.cpp"   "src/sha1_avx2.cpp"   "src/sha256_avx2.cpp"   "src/sha512_avx2.cpp"
    "src/md4_avx512.cpp" "src/md5_avx512.cpp" "src/sha1_avx512.cpp" "src/sha256_avx512.cpp" "src/sha512_avx512.cpp"
)
if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(FSC PRIVATE -O3 -DNDEBUG)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(FSC PRIVATE -fomit-frame-pointer -O3 -DNDEBUG)
elseif(MSVC)
    target_compile_options(FSC PRIVATE /O2 /DNDEBUG)
endif()
target_include_directories(FSC INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(FSC PROPERTIES CXX_STANDARD 20 INTERPROCEDURAL_OPTIMIZATION TRUE)

# Warning level 4 and all warnings as errors
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    cmake_policy(SET CMP0135 NEW) # Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24
    set_property(TARGET FSC PROPERTY COMPILE_WARNING_AS_ERROR ON)
else()
    if(MSVC)
        target_compile_options(FSC PRIVATE /W4 /WX)
        target_link_options(FSC PRIVATE /W4 /WX)
    else()
        target_compile_options(FSC PRIVATE -Wall -Wextra -pedantic -Werror -Wl,--fatal-warnings)
    endif()
endif()

###############################################################################################################
# Testing
###############################################################################################################
include(FetchContent)
if(FSC_BUILD_TESTS)
    SET(BUILD_GMOCK OFF)
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
    FetchContent_Declare(wy URL https://github.com/alainesp/wy/archive/refs/heads/main.zip)
if(MSVC)
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
    FetchContent_MakeAvailable(googletest wy)

    enable_testing()

    add_executable(runUnitTests "tests/general.cpp" "tests/md4.cpp" "tests/md5.cpp" "tests/sha1.cpp" "tests/sha256.cpp" "tests/sha512.cpp" "tests/aes.cpp")
    target_compile_definitions(runUnitTests PRIVATE TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/tests/")
    set_target_properties(runUnitTests PROPERTIES CXX_STANDARD 20 INTERPROCEDURAL_OPTIMIZATION TRUE)
    target_link_libraries(runUnitTests PRIVATE FSC gtest_main wy)

    include(GoogleTest)
    gtest_discover_tests(runUnitTests)
endif()

###############################################################################################################
# Executables
###############################################################################################################
#if(FSC_BUILD_EXAMPLE)
#    add_executable(fsc-examples "example.cpp")
#    set_property(TARGET fsc-examples PROPERTY CXX_STANDARD 20)	 # C++ language to use
#    target_link_libraries(fsc-examples PRIVATE FSC)
#endif()

if(FSC_BUILD_BENCHMARK)
    add_executable(fsc-benchmark "benchmark/md4.cpp" "benchmark/md5.cpp" "benchmark/sha1.cpp" "benchmark/sha256.cpp" "benchmark/sha512.cpp" "benchmark/aes.cpp")
    set_target_properties(fsc-benchmark PROPERTIES CXX_STANDARD 20 INTERPROCEDURAL_OPTIMIZATION TRUE)

    FetchContent_Declare(benchmark URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip)
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(benchmark)
    target_link_libraries(fsc-benchmark PRIVATE FSC benchmark::benchmark benchmark::benchmark_main)
endif()
