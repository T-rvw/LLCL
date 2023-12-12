#pragma once

#include <LLCL/Namespace.h>
#include <LLCL/Hash/Hash.h>

#include <functional>

LLCL_NAMESPACE_BEGIN

template<typename T>
class TStringCrc final
{
public:
	TStringCrc() = default;
	explicit constexpr TStringCrc(std::string_view sv) : m_hashValue(StringHashFNV1a<T>(sv)) {}
	explicit constexpr TStringCrc(const char* str, size_t n) : m_hashValue(StringHashFNV1a<T>(str, n)) {}
	TStringCrc(const TStringCrc&) = default;
	TStringCrc& operator=(const TStringCrc&) = default;
	TStringCrc(TStringCrc&&) = default;
	TStringCrc& operator=(TStringCrc&&) = default;
	~TStringCrc() = default;

	constexpr T Value() const { return m_hashValue; }
	bool operator<(const TStringCrc& other) const { return m_hashValue < other.m_hashValue; }
	bool operator>(const TStringCrc& other) const { return m_hashValue > other.m_hashValue; }
	bool operator==(const TStringCrc& other) const { return m_hashValue == other.m_hashValue; }
	bool operator!=(const TStringCrc& other) const { return m_hashValue != other.m_hashValue; }

private:
	T m_hashValue;
};

using StringCrc = TStringCrc<uint32_t>;

LLCL_NAMESPACE_END

namespace std
{

// Compatiable to use in STL containers directly.
template<>
struct hash<NAME_PREFIX_NAMESPACE(StringCrc)>
{
	uint64_t operator()(const NAME_PREFIX_NAMESPACE(StringCrc)& key) const
	{
		return static_cast<uint32_t>(key.Value());
	}
};

}