#pragma once
#include "SingletonPtrFactory.h"


template<
	typename T,
	typename H = std::hash<T>,
	typename E = std::equal_to<T>>
class SingletonPtr
{
public:
	SingletonPtr(const SingletonPtr&) = default;
	SingletonPtr& operator = (const SingletonPtr&) = default;

public:
	SingletonPtr()
	{
		SingletonPtrFactory<T, H, E>& factory = GetFactory();
		_ptr = factory.GetDefault();
	}

	SingletonPtr(const T& key)
	{
		SingletonPtrFactory<T, H, E>& factory = GetFactory();
		_ptr = factory.GetOrCreate(key);
	}

	SingletonPtr& operator = (const T& key)
	{
		SingletonPtrFactory<T, H, E>& factory = GetFactory();
		_ptr = factory.GetOrCreate(key);
		return *this;
	}

public:
	const T* GetPtr() const
	{
		return _ptr;
	}

	const T& GetRef() const
	{
		return *_ptr;
	}

private:
	static SingletonPtrFactory<T, H, E>& GetFactory()
	{
		static SingletonPtrFactory<T, H, E> result;
		return result;
	}

private:
	const T* _ptr = nullptr;
};


namespace std
{
	template<typename T, typename H, typename E> struct hash<SingletonPtr<T, H, E>>
	{
		size_t operator() (const SingletonPtr<T, H, E>& value) const noexcept
		{
			const hash<const void*> helper;
			const size_t result = helper(&value.GetPtr());
			return result;
		}
	};
}

template<typename T, typename H, typename E>
bool operator == (SingletonPtr<T, H, E> first, SingletonPtr<T, H, E>  second)
{
	return first.GetPtr() == second.GetPtr();
}

template<typename T, typename H, typename E>
bool operator != (SingletonPtr<T, H, E>  first, SingletonPtr<T, H, E>  second)
{
	return first.GetPtr() != second.GetPtr();
}

template<typename T, typename H, typename E>
bool operator <= (SingletonPtr<T, H, E>  first, SingletonPtr<T, H, E>  second)
{
	return first.GetPtr() <= second.GetPtr();
}

template<typename T, typename H, typename E>
bool operator >= (SingletonPtr<T, H, E>  first, SingletonPtr<T, H, E>  second)
{
	return first.GetPtr() >= second.GetPtr();
}

template<typename T, typename H, typename E>
bool operator < (SingletonPtr<T, H, E>  first, SingletonPtr<T, H, E>  second)
{
	return first.GetPtr() < second.GetPtr();
}

template<typename T, typename H, typename E>
bool operator > (SingletonPtr<T, H, E>  first, SingletonPtr<T, H, E>  second)
{
	return first.GetPtr() > second.GetPtr();
}