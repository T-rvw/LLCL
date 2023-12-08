#pragma once

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

// Function Name
#if defined(LLCL_COMPILER_CLANG) || defined(LLCL_COMPILER_GCC)
	#define LLCL_FUNCTION_NAME	__PRETTY_FUNCTION__
#elif defined(LLCL_COMPILER_MSVC)
	// TODO : use __FUNCSIG__ ? Seems best match behavior with __PRETTY_FUNCTION__
	#define LLCL_FUNCTION_NAME	__FUNCTION__
#else
	#error Undefined LLCL_FUNCTION_NAME
#endif

// Source File/Line
#define LLCL_SOURCE_FILE __FILE__
#define LLCL_SOURCE_LINE __LINE__

// Call Convention
#define CDECL __cdecl
#define STDCALL __stdcall

LLCL_NAMESPACE_BEGIN

// Avoid unused warning
template<typename T>
void Unused(const T&)
{
}

LLCL_NAMESPACE_END