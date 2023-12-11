#pragma once

#include <LLCL/Compiler.h>
#include <LLCL/Namespace.h>

LLCL_NAMESPACE_BEGIN

enum class Endian
{
	Little,
	Big
};

static inline Endian GetNativeEndian()
{
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
	return Endian::Little;
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
	return Endian::Big;
#elif defined(LLCL_COMPILER_CLANG) && __LITTLE_ENDIAN__
	return Endian::Little;
#elif defined(LLCL_COMPILER_CLANG) && __BIG_ENDIAN__
	return Endian::Big;
#elif defined(LLCL_COMPILER_MSVC)
	return Endian::Little;
#else
	// Actually, runtime check is the best choice to detect endian because endian is based on CPU Arch at first.
	// But some CPUs such as ARM are able to switch different endian modes for different platforms...
	union
	{
		uint32_t i;
		char c[4];
	} bint = { 0x04030201 };
	return bint.c[0] == 0x01 ? Endian::Little : Endian::Big;
#endif
}

LLCL_NAMESPACE_END