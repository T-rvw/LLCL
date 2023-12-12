#pragma once

#include <LLCL/Namespace.h>
#include <LLCL/Delegates/Delegate.h>

#include <list>

LLCL_NAMESPACE_BEGIN

template<typename T>
class MulticastDelegate
{
private:
	static_assert("MulticastDelegate class should accept more than one parameter. Void should also pass through.");
};

template<typename RetVal, typename... Args>
class MulticastDelegate<RetVal(Args...)>
{
public:
	MulticastDelegate() = default;
	MulticastDelegate(const MulticastDelegate&) = delete;
	MulticastDelegate& operator=(const MulticastDelegate&) = delete;
	MulticastDelegate(MulticastDelegate&&) = default;
	MulticastDelegate& operator=(MulticastDelegate&&) = default;
	~MulticastDelegate() = default;

	template<RetVal(*Function)(Args...)>
	void Bind()
	{
		Delegate<RetVal(Args...)> delegate;
		delegate.template Bind<Function>();
		m_delegates.emplace_back(std::move(delegate));
	}

	template<typename C, RetVal(C::*Function)(Args...)>
	void Bind(C* pInstance)
	{
		Delegate<RetVal(Args...)> delegate;
		delegate.template Bind<C, Function>(pInstance);
		m_delegates.emplace_back(std::move(delegate));
	}

	template<typename C, RetVal(C::*Function)(Args...) const>
	void Bind(const C* pInstance)
	{
		Delegate<RetVal(Args...)> delegate;
		delegate.template Bind<C, Function>(pInstance);
		m_delegates.emplace_back(std::move(delegate));
	}

	void Invoke(Args... args) const
	{
		for(const auto& delegate : m_delegates)
		{
			delegate.Invoke(args...);
		}
	}

private:
	std::list<Delegate<RetVal(Args...)>> m_delegates;
};

LLCL_NAMESPACE_END