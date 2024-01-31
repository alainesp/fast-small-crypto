﻿###############################################################################################################
# This file is part of 'Fast-Small-Crypto'
# 
# Copyright (c) 2024 by Alain Espinosa.
###############################################################################################################
cmake_minimum_required (VERSION 3.12)

project (fast-small-crypto VERSION 1.0.0.0 DESCRIPTION "Fast crypto implementations for small data"
			HOMEPAGE_URL https://github.com/alainesp/fast-small-crypto LANGUAGES C CXX)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

###############################################################################################################
# Library configuration
###############################################################################################################
option(FSC_BUILD_EXAMPLE "Build the example" OFF)
option(FSC_BUILD_PERFORMANCE "Build the performance testing" OFF)
option(FSC_BUILD_TESTS "Build the tests" ON)

add_library(FSC STATIC "md4.c" "md4.h")
target_include_directories(FSC INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET FSC PROPERTY CXX_STANDARD 20) # C++ language to use

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
# Executables
###############################################################################################################
#if(FSC_BUILD_EXAMPLE)
#    add_executable(fsc-examples "example.cpp")
#    set_property(TARGET fsc-examples PROPERTY CXX_STANDARD 20)	 # C++ language to use
#    target_link_libraries(fsc-examples PRIVATE FSC)
#endif()
#
#if(FSC_BUILD_PERFORMANCE)
#    add_executable(fsc-performance "performance.cpp")
#    set_property(TARGET fsc-performance PROPERTY CXX_STANDARD 20)	 # C++ language to use
#    target_link_libraries(fsc-performance PRIVATE FSC)
#endif()

###############################################################################################################
# Testing
###############################################################################################################
if(FSC_BUILD_TESTS)
    include(FetchContent)
    SET(BUILD_GMOCK OFF)
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
    FetchContent_Declare(wy URL https://github.com/alainesp/wy/archive/refs/heads/main.zip)
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest wy)

    enable_testing()

    add_executable(runUnitTests "tests.cpp")
    set_property(TARGET runUnitTests PROPERTY CXX_STANDARD 20) # C++ language to use
    target_link_libraries(runUnitTests PRIVATE FSC gtest_main wy)

    include(GoogleTest)
    gtest_discover_tests(runUnitTests)
endif()