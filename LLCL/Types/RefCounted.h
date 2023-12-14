#pragma once

#include <LLCL/Namespace.h>
#include <LLCL/Types.h>

#include <atomic>

LLCL_NAMESPACE_BEGIN

class RefCounted
{
public:
	RefCounted() = default;
	RefCounted(const RefCounted&) = delete;
	RefCounted& operator=(const RefCounted&) = delete;
	RefCounted(RefCounted&&) = default;
	RefCounted& operator=(RefCounted&&) = default;
	~RefCounted() = default;

	// TODO : memory order optimization
	uint32_t AddRef() const { return m_refCount.fetch_add(1); }
	uint32_t ReleaseRef() const { return m_refCount.fetch_sub(1); }
	bool IsReferenced() const { return m_refCount > 0; }
	uint32_t GetRefCount() const { return m_refCount; }

private:
	mutable std::atomic<uint32_t> m_refCount = 0;
};

LLCL_NAMESPACE_END