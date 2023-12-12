#pragma once

#include <LLCL/NameOf.h>
#include <LLCL/Namespace.h>

#include <type_traits>

LLCL_NAMESPACE_BEGIN

// Avoid unused warning.
template<typename T>
void Unused(const T&)
{
}

// Move temp rvalue.
template<typename T>
[[nodiscard]] constexpr std::remove_reference_t<T>&& MoveTemp(T&& value) noexcept
{
	using CastType = std::remove_reference_t<T>;
	static_assert(std::is_lvalue_reference_v<T>, "T is lvalue reference object.");
	static_assert(!std::is_same_v<CastType&, const CastType&>, "For a const object, MoveTemp doesn't take effect.");
	return static_cast<CastType&&>(value);
}

// Calculate enum count.
template <typename E>
[[nodiscard]] constexpr auto enum_count() noexcept
{
	return nameof::detail::count_v<std::decay_t<E>>;
}

template <typename T>
[[nodiscard]] constexpr auto bitsof() noexcept
{
	return sizeof(T) * sizeof(uint8);
}

LLCL_NAMESPACE_END