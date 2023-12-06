#pragma once

//////////////////////////////////////////////////////////
// Header
//////////////////////////////////////////////////////////
#include <cstdint>

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

LLCL_NAMESPACE_BEGIN

//////////////////////////////////////////////////////////
// Platform
//////////////////////////////////////////////////////////
enum class PlatformType
{
	Windows,
	UWP,
	Android,
	Linux,
	MacOS,
	IOS,
	WASM
};

#if defined(_WIN32) || defined(_WIN64)
	#include <winapifamily.h>
	#if WINAPI_FAMILY == WINAPI_FAMILY_APP
		static constexpr auto Platform = PlatformType::UWP;
	#else
		static constexpr auto Platform = PlatformType::Windows;
	#endif
#elif defined(__ANDROID__)
	static constexpr auto Platform = PlatformType::Android;
#elif defined(__linux__)
	static constexpr auto Platform = PlatformType::Linux;
#elif defined(__APPLE__)
	#include <TargetConditionals.h>
	#if defined(TARGET_OS_IPHONE) && !TARGET_OS_IPHONE
		static constexpr auto Platform = PlatformType::MacOS;
	#else
		static constexpr auto Platform = PlatformType::IOS;
	#endif
#elif defined(__EMSCRIPTEN__)
	static constexpr auto Platform = PlatformType::WASM;
#else
	#error Unknown platform type
#endif

//////////////////////////////////////////////////////////
// Compiler
//////////////////////////////////////////////////////////
enum class CompilerType
{
	Clang,
	GCC,
	MSVC,
	MINGW
};

// Type
#if defined(__clang__)
	static constexpr auto Compiler = CompilerType::Clang;
#elif defined(__GNUC__)
	static constexpr auto Compiler = CompilerType::GCC;
#elif defined(_MSC_VER)
	static constexpr auto Compiler = CompilerType::MSVC;
#elif defined(__MINGW64__) || defined (__MINGW32__)
	static constexpr auto Compiler = CompilerType::MINGW;
#else
	#error Unknown compiler type
#endif

// Symbol Import/Export
#ifdef _MSC_VER
	#define API_EXPORT __declspec(dllexport)
	#define API_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
	#define API_EXPORT __attribute__((visibility("default")))
	#define API_IMPORT
#else
	#define API_EXPORT
	#define API_IMPORT
#endif

// Inline
#ifdef _MSC_VER
#	define FORCEINLINE __forceinline
#	define NOINLINE __declspec(noinline)
#else
#	define FORCEINLINE inline __attribute__((always_inline))
#	define NOINLINE __attribute__((noinline))
#endif

//////////////////////////////////////////////////////////
// CPU
//////////////////////////////////////////////////////////
enum class CPUArchType
{
	X86,
	X64,
	ARM32,
	ARM64
};

// Arch and Address bits
#if defined(__i386__) || defined(_M_IX86)
	static constexpr auto CPUArch = CPUArchType::X86;
	static constexpr int CPUAddressBits = 32;
#elif defined(__x86_64__) || defined(_M_X64)
	static constexpr auto CPUArch = CPUArchType::X64;
	static constexpr int CPUAddressBits = 64;
#elif defined(__arm__) || defined(_M_ARM)
	static constexpr auto CPUArch = CPUArchType::ARM32;
	static constexpr int CPUAddressBits = 32;
#elif defined(__aarch64__) || defined(_M_ARM64)
	static constexpr auto CPUArch = CPUArchType::ARM64;
	static constexpr int CPUAddressBits = 64;
#else
	#error Unknown cpu architecture
#endif
static_assert(sizeof(void*) == (CPUAddressBits / 8));

// SIMD instruction sets
#if defined(__AVX512F__) && defined(__AVX512VL__) && defined(__AVX512DQ__)
	static constexpr bool CPUIS_AVX512 = true;
#else
	static constexpr bool CPUIS_AVX512 = false;
#endif

#if defined(__AVX2__)
	static constexpr bool CPUIS_AVX2 = true;
#else
	static constexpr bool CPUIS_AVX2 = false;
#endif

#if defined(__AVX__)
	static constexpr bool CPUIS_AVX = true;
#else
	static constexpr bool CPUIS_AVX = false;
#endif

#if defined(__SSE4_1__)
	static constexpr bool CPUIS_SSE4_1 = true;
#else
	static constexpr bool CPUIS_SSE4_1 = false;
#endif

#if defined(__SSE4_2__)
	static constexpr bool CPUIS_SSE4_2 = true;
#else
	static constexpr bool CPUIS_SSE4_2 = false;
#endif

//////////////////////////////////////////////////////////
// Data Type
//////////////////////////////////////////////////////////
using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
static_assert(1 == sizeof(uint8));
static_assert(2 == sizeof(uint16));
static_assert(4 == sizeof(uint32));
static_assert(8 == sizeof(uint64));

LLCL_NAMESPACE_END