#pragma once

#include <LLCL/Namespace.h>

#include <cassert>
#include <functional>

LLCL_NAMESPACE_BEGIN

template<typename T>
class Delegate
{
private:
	static_assert("Delegate class should accept more than one parameter. Void should also pass through.");
};

template<typename RetVal, typename... Args>
class Delegate<RetVal(Args...)>
{
private:
	// The ProxyFunction is a function pointer which keeps a same signature
	// for different kinds of function calls.
	using ProxyFuncPtr = RetVal(*)(void*, Args...);

	// Basic function
	template<RetVal(*Function)(Args...)>
	static RetVal FunctionProxy(void*, Args... args)
	{
		return Function(std::forward<Args>(args)...);
	}

	// Non-const method
	template<typename C, RetVal(C::*Function)(Args...)>
	static RetVal MethodProxy(void* pInstance, Args... args)
	{
		return (static_cast<C*>(pInstance)->*Function)(std::forward<Args>(args)...);
	}

	// Const method
	template<typename C, RetVal(C::*Function)(Args...) const>
	static RetVal ConstMethodProxy(void* pInstance, Args... args)
	{
		return (static_cast<const C*>(pInstance)->*Function)(std::forward<Args>(args)...);
	}

public:
	Delegate() = default;
	Delegate(const Delegate&) = delete;
	Delegate& operator=(const Delegate&) = delete;
	Delegate(Delegate&&) = default;
	Delegate& operator=(Delegate&&) = default;
	~Delegate() = default;

	template<RetVal(*Function)(Args...)>
	void Bind()
	{
		m_pInstance = nullptr;
		m_pProxyFunc = &FunctionProxy<Function>;
	}

	template<typename C, RetVal(C::*Function)(Args...)>
	void Bind(C* pInstance)
	{
		m_pInstance = pInstance;
		m_pProxyFunc = &MethodProxy<C, Function>;
	}

	template<typename C, RetVal(C::*Function)(Args...) const>
	void Bind(const C* pInstance)
	{
		m_pInstance = const_cast<C*>(pInstance);
		m_pProxyFunc = &ConstMethodProxy<C, Function>;
	}

	RetVal Invoke(Args... args) const
	{
		if constexpr (std::is_same_v<RetVal, void>)
		{
			if (m_pProxyFunc != nullptr)
			{
				m_pProxyFunc(m_pInstance, std::forward<Args>(args)...);
			}
		}
		else
		{
			return m_pProxyFunc != nullptr ? m_pProxyFunc(m_pInstance, std::forward<Args>(args)...) : RetVal{};
		}
	}

private:
	void* m_pInstance = nullptr;
	ProxyFuncPtr m_pProxyFunc = nullptr;
};

LLCL_NAMESPACE_END