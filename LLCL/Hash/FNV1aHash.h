#pragma once

#include <LLCL/Namespace.h>

#include <cstdint>
#include <string_view>

LLCL_NAMESPACE_BEGIN

namespace details
{

template<typename T>
struct FNV1aHashTraits;

template<>
struct FNV1aHashTraits<std::uint32_t>
{
	using T = std::uint32_t;
	static constexpr T Offset = 2166136261U;
	static constexpr T Prime = 16777619U;
};

template<>
struct FNV1aHashTraits<std::uint64_t>
{
	using T = std::uint64_t;
	static constexpr T Offset = 14695981039346656037ULL;
	static constexpr T Prime = 1099511628211ULL;
};

template<typename T>
constexpr T StringHashSeedFNV1a(T seed, const char* str, std::size_t n) noexcept
{
	using Traits = details::FNV1aHashTraits<T>;

	T value = seed;
	for (std::size_t i = 0; i < n; ++i)
	{
		value = (value ^ static_cast<typename Traits::T>(str[i])) * Traits::Prime;
	}

	return value;
}

}

template<typename T>
constexpr T StringHashFNV1a(const char* str, std::size_t n) noexcept
{
	using Traits = details::FNV1aHashTraits<T>;
	return details::StringHashSeedFNV1a<T>(Traits::Offset, str, n);
}

template<typename T>
constexpr T StringHashFNV1a(std::string_view sv) noexcept
{
	return StringHashFNV1a<T>(sv.data(), sv.size());
}

LLCL_NAMESPACE_END