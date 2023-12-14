#pragma once

#include <LLCL/Types.h>

#include <cassert>
#include <string>
#include <string_view>
#include <type_traits>

LLCL_NAMESPACE_BEGIN

namespace
{

// Traits.
struct CStringTraits
{
	using iterator = char*;
	using const_iterator = const char*;
};

}

//
// C-style Compile-time String ends with '\0'.
// Helpful in template meta programing or compile-time calculation.
//
template<size_t N>
class [[nodiscard]] CString
{
public:
	// STL style iterators.
	using iterator = CStringTraits::iterator;
	using const_iterator = CStringTraits::const_iterator;
	using const_iterator = CStringTraits::const_iterator;

public:
	constexpr CString() = delete;
	constexpr explicit CString(std::string_view sv) noexcept : CString{ sv, std::make_integer_sequence<size_t, N>{} } { assert(sv.size() > 0 && sv.size() == N); }
	constexpr CString(const CString&) = default;
	CString& operator=(const CString&) = default;
	constexpr CString(CString&&) = default;
	CString& operator=(CString&&) = default;
	~CString() = default;

	// STL style APIs.
	[[nodiscard]] constexpr char* data() noexcept { return Data; }
	[[nodiscard]] constexpr const char* data() const noexcept { return data(); }
	[[nodiscard]] constexpr char* c_str() noexcept { return data(); }
	[[nodiscard]] constexpr const char* c_str() const noexcept { return data(); }
	[[nodiscard]] constexpr size_t size() const noexcept { return N; }
	[[nodiscard]] constexpr size_t length() const noexcept { return size(); }
	[[nodiscard]] constexpr bool empty() const noexcept { return false; }
	[[nodiscard]] constexpr iterator begin() noexcept { return data(); }
	[[nodiscard]] constexpr iterator end() noexcept { return data() + size(); }
	[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return data(); }
	[[nodiscard]] constexpr const_iterator cend() const noexcept { return data() + size(); }
	[[nodiscard]] constexpr const char& operator[](size_t i) const noexcept { assert(i < size()); return Data[i]; }
	[[nodiscard]] constexpr int compare(std::string_view sv) const noexcept { return operator std::string_view().compare(sv); }

	// Conversions to const char*/std::string_view/std::string
	[[nodiscard]] constexpr operator const char*() const noexcept { return data(); }
	[[nodiscard]] constexpr operator std::string_view() const noexcept { return { data(), size() }; }
	[[nodiscard]] explicit operator std::string() const { return { begin(), end() }; }
	
private:
	template<size_t... I>
	constexpr CString(std::string_view sv, std::integer_sequence<size_t, I...>) noexcept : Data{ sv[I]..., '\0' } {}

	char Data[static_cast<size_t>(N) + 1];
};

template<>
class [[nodiscard]] CString<0>
{
public:
	// STL style iterators.
	using iterator = CStringTraits::iterator;
	using const_iterator = CStringTraits::const_iterator;
	using const_iterator = CStringTraits::const_iterator;

public:
	constexpr CString() = delete;
	constexpr explicit CString(std::string_view sv) noexcept { assert(sv.size() == 0); }
	constexpr CString(const CString&) = default;
	CString& operator=(const CString&) = default;
	constexpr CString(CString&&) = default;
	CString& operator=(CString&&) = default;
	~CString() = default;

	// STL style APIs.
	[[nodiscard]] constexpr char* data() noexcept { return nullptr; }
	[[nodiscard]] constexpr const char* data() const noexcept { return data(); }
	[[nodiscard]] constexpr char* c_str() noexcept { return data(); }
	[[nodiscard]] constexpr const char* c_str() const noexcept { return data(); }
	[[nodiscard]] constexpr size_t size() const noexcept { return 0; }
	[[nodiscard]] constexpr size_t length() const noexcept { return size(); }
	[[nodiscard]] constexpr bool empty() const noexcept { return true; }
	[[nodiscard]] constexpr iterator begin() noexcept { return data(); }
	[[nodiscard]] constexpr iterator end() noexcept { return data() + size(); }
	[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return data(); }
	[[nodiscard]] constexpr const_iterator cend() const noexcept { return data() + size(); }
	[[nodiscard]] constexpr int compare(std::string_view sv) const noexcept { return operator std::string_view().compare(sv); }

	// Conversions to const char*/std::string_view/std::string
	[[nodiscard]] constexpr operator const char* () const noexcept { return data(); }
	[[nodiscard]] constexpr operator std::string_view() const noexcept { return { data(), size() }; }
	[[nodiscard]] explicit operator std::string() const { return {}; }
};

LLCL_NAMESPACE_END