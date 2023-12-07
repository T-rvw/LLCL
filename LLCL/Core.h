#pragma once

//////////////////////////////////////////////////////////
// Platform
//////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(_WIN64)
	#include <winapifamily.h>
	#if WINAPI_FAMILY == WINAPI_FAMILY_APP
		#define LLCL_PLATFORM_UWP
	#else
		#define LLCL_PLATFORM_WINDOWS
	#endif
#elif defined(__ANDROID__)
	#define LLCL_PLATFORM_ANDROID
#elif defined(__linux__)
	#define LLCL_PLATFORM_LINUX
#elif defined(__APPLE__)
	#include <TargetConditionals.h>
	#if defined(TARGET_OS_IPHONE) && !TARGET_OS_IPHONE
		#define LLCL_PLATFORM_MACOS
	#else
		#define LLCL_PLATFORM_IOS
	#endif
#elif defined(__EMSCRIPTEN__)
	#define LLCL_PLATFORM_WASM
#else
	#error Unknown platform type
#endif

//////////////////////////////////////////////////////////
// Compiler
//////////////////////////////////////////////////////////
// Type
#if defined(__clang__)
	#define LLCL_COMPILER_CLANG
#elif defined(__GNUC__)
	#define LLCL_COMPILER_GCC
#elif defined(_MSC_VER)
	#define LLCL_COMPILER_MSVC
#elif defined(__MINGW64__) || defined (__MINGW32__)
	#define LLCL_COMPILER_MINGW
#else
	#error Unknown compiler type
#endif

//////////////////////////////////////////////////////////
// CPU
//////////////////////////////////////////////////////////
// Arch and Address bits
#if defined(__i386__) || defined(_M_IX86)
	#define LLCL_CPU_ARCH_X86
	#define LLCL_CPU_ADDRESS_BITS 32
#elif defined(__x86_64__) || defined(_M_X64)
	#define LLCL_CPU_ARCH_X64
	#define LLCL_CPU_ADDRESS_BITS 64
#elif defined(__arm__) || defined(_M_ARM)
	#define LLCL_CPU_ARCH_ARM32
	#define LLCL_CPU_ADDRESS_BITS 32
#elif defined(__aarch64__) || defined(_M_ARM64)
	#define LLCL_CPU_ARCH_ARM64
	#define LLCL_CPU_ADDRESS_BITS 64
#else
	#error Unknown cpu architecture
#endif
static_assert(sizeof(void*) == (LLCL_CPU_ADDRESS_BITS / 8));

// SIMD instruction sets
// AVX
#if defined(__AVX512F__) && defined(__AVX512VL__) && defined(__AVX512DQ__)
	#define LLCL_CPU_IS_AVX512
#endif

#if defined(__AVX2__) || defined(LLCL_CPU_IS_AVX512)
	#define LLCL_CPU_IS_AVX2
#endif

#if defined(__AVX__) || defined(LLCL_CPU_IS_AVX2)
	#define LLCL_CPU_IS_AVX
#endif

// Float16 Conversion to Float32
#if defined(__F16C__) || defined(LLCL_CPU_IS_AVX2)
	#define LLCL_CPU_IS_F16C
#endif

// Leading Zero CouNT
#if defined(__LZCNT__) || defined(LLCL_CPU_IS_AVX2)
	#define LLCL_CPU_IS_LZCNT
#endif

// Trailing Zero CouNT
#if defined(__BMI__) || defined(LLCL_CPU_IS_AVX2)
	#define LLCL_CPU_IS_TZCNT
#endif

// Fused Multiply Add
#if defined(LLCL_COMPILER_CLANG) || defined(LLCL_COMPILER_GCC) 
	#if defined(__FMA__)
		#define LLCL_CPU_IS_FMADD
	#endif
#elif defined(LLCL_COMPILER_MSVC)
	#if defined(LLCL_CPU_IS_AVX2)
		#define LLCL_CPU_IS_FMADD
	#endif
#endif

// SSE
#if defined(LLCL_CPU_ARCH_X86) || defined(LLCL_CPU_ARCH_X64)
	#define LLCL_CPU_IS_SSE
#endif

#if defined(__SSE4_2__)
	#define LLCL_CPU_IS_SSE4_2
#endif

#if defined(__SSE4_1__) || defined(LLCL_CPU_IS_SSE4_2)
	#define LLCL_CPU_IS_SSE4_1
#endif

// NEON
#if defined(LLCL_CPU_ARCH_ARM32) || defined(LLCL_CPU_ARCH_ARM64)
	#define LLCL_CPU_IS_NEON
#endif

//////////////////////////////////////////////////////////
// Language
//////////////////////////////////////////////////////////
// Symbol Import/Export
#ifdef LLCL_COMPILER_MSVC
	#define API_EXPORT __declspec(dllexport)
	#define API_IMPORT __declspec(dllimport)
#else
	#define API_EXPORT __attribute__((visibility("default")))
	#define API_IMPORT
#endif

// Inline
#ifdef LLCL_COMPILER_MSVC
	#define FORCEINLINE __forceinline
	#define NOINLINE __declspec(noinline)
#else
	#define FORCEINLINE inline __attribute__((always_inline))
	#define NOINLINE __attribute__((noinline))
#endif

//////////////////////////////////////////////////////////
// Namespace
//////////////////////////////////////////////////////////
#ifndef LLCL_NAME
	// No namespace by default.
#define LLCL_NAMESPACE_BEGIN
#define LLCL_NAMESPACE_END
#else
	// Use customized name for namespace.
#define LLCL_NAMESPACE_BEGIN \
		namespace LLCL_NAME \
		{

#define LLCL_NAMESPACE_END \
		}
#endif

//////////////////////////////////////////////////////////
// Types
//////////////////////////////////////////////////////////
#include <cstdint>

LLCL_NAMESPACE_BEGIN

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
static_assert(1 == sizeof(uint8));
static_assert(2 == sizeof(uint16));
static_assert(4 == sizeof(uint32));
static_assert(8 == sizeof(uint64));

LLCL_NAMESPACE_END