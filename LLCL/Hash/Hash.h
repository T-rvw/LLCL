#pragma once

#include <LLCL/Namespace.h>
#include <LLCL/Hash/FNV1aHash.h>

LLCL_NAMESPACE_BEGIN

// Combines two hash values to get a third. Not commutative.
template<typename T>
constexpr T HashCombine(T a, T b)
{
	return a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2));
}

LLCL_NAMESPACE_END