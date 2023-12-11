#pragma once

#include <LLCL/TypeTraits.h>

#include <cstring> // std::memset

LLCL_NAMESPACE_BEGIN

//
// BitFlags avoid memory management and manipulate operations on bits.
// Convenient to process bits on/off combined with enum class.
//
template<typename T>
class BitFlags
{
public:
	static_assert(std::is_enum_v<T>);
	using StorageType = uint32;
	static constexpr size_t EnumCount = enum_count<T>();
	static constexpr size_t ElementCount = EnumCount / (8 * sizeof(StorageType));
	static constexpr size_t StorageSize = ElementCount * sizeof(StorageType);

public:
	BitFlags() { std::memset(m_options, 0, StorageSize); }
	BitFlags(const BitFlags&) = default;
	BitFlags& operator=(const BitFlags&) = default;
	BitFlags(BitFlags&&) = default;
	BitFlags& operator=(BitFlags&&) = default;
	~BitFlags() = default;

	bool IsEnabled(T e) const
	{
		auto index = static_cast<std::size_t>(e);
		return (m_options[index] & 1) != 0;
	}

	void Enable(T e)
	{
		auto index = static_cast<std::size_t>(e);
		m_options[index] |= 1 << index;
	}

	void Disable(T e)
	{
		auto index = static_cast<std::size_t>(e);
		m_options[index] &= ~(1 << index);
	}

	bool operator==(const BitFlags<T>& rhs)
	{
		return false;
	}

private:
	std::uint32_t m_options[ElementCount];
};

LLCL_NAMESPACE_END