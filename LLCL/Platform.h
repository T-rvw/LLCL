#pragma once

#if defined(_WIN32) || defined(_WIN64)
	#define LLCL_PLATFORM_WINDOWS
#elif defined(__linux__)
	#define LLCL_PLATFORM_LINUX
#elif defined(__ANDROID__)
	#define LLCL_PLATFORM_ANDROID
#elif defined(__APPLE__)
	#include <TargetConditionals.h>
	#if defined(TARGET_OS_IPHONE) && !TARGET_OS_IPHONE
		#define LLCL_PLATFORM_MACOS
	#else
		#define LLCL_PLATFORM_IOS
	#endif
#elif defined(__EMSCRIPTEN__)
	#define LLCL_PLATFORM_WASM
#elif defined(__ORBIS__)
	#define LLCL_PLATFORM_PS4
#elif defined(__PROSPERO__)
	#define LLCL_PLATFORM_PS5
#elif defined(_DURANGO) || defined(_XBOX_ONE)
	#define LLCL_PLATFORM_XBOX
#else
	#error Unknown platform type
#endif

// Header files
#if defined(LLCL_PLATFORM_LINUX) || defined(LLCL_PLATFORM_ANDROID)
#include <signal.h>
#endif

LLCL_NAMESPACE_BEGIN

enum class PlatformCategory
{
	Console,
	Mobile,
	PC,
	Web
};

static inline PlatformCategory GetPlatformCategory()
{
#if defined(LLCL_PLATFORM_ANDROID) || defined(LLCL_PLATFORM_IOS)
	return PlatformCategory::Mobile;
#elif defined(LLCL_PLATFORM_LINUX) || defined(LLCL_PLATFORM_WINDOWS) || defined(LLCL_PLATFORM_MACOS)
	return PlatformCategory::PC;
#elif defined(LLCL_PLATFORM_PS4) || defined(LLCL_PLATFORM_PS5) || defined(LLCL_PLATFORM_XBOX)
	return PlatformCategory::Console;
#elif defined(LLCL_PLATFORM_WASM)
	return PlatformCategory::Web;
#else
	#error Unknown platform category
#endif
}

LLCL_NAMESPACE_END