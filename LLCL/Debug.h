#pragma once

#include <LLCL/Namespace.h>
#include <LLCL/Platform.h>
#include <LLCL/Types.h>

LLCL_NAMESPACE_BEGIN

static void DebugBreakPoint()
{
#if defined(LLCL_PLATFORM_WINDOWS)
	__debugbreak();
#elif defined(LLCL_PLATFORM_MACOS) || defined(LLCL_PLATFORM_IOS)
	#if defined(LLCL_CPU_ARCH_X86) || defined(LLCL_CPU_ARCH_X64)
		__asm__("int $3");
	#else
		__builtin_trap();
	#endif
#elif defined(LLCL_PLATFORM_LINUX) || defined(LLCL_PLATFORM_ANDROID)
	raise(SIGTRAP);
#else
	int32* int3 = (int32*)3L;
	*int3 = 3;
#endif
}

static void DebugCrash()
{
	int32* p = nullptr;
	*p = 0;
}

LLCL_NAMESPACE_END