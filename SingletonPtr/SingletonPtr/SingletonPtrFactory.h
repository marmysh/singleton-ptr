#pragma once

template<typename T, typename H, typename E>
class SingletonPtrFactory
{
public:
	SingletonPtrFactory()
	{
		_instances.emplace(_default);
	}

public:
	const T* GetDefault() const
	{
		return &_default;
	}

	const T* GetOrCreate(const T& key)
	{
		const T* result = TryGet(key);
		if (nullptr == result)
		{
			result = Ensure(key);
		}
		return result;
	}

private:
	const T* TryGet(const T& key)
	{
		std::shared_lock<std::shared_mutex> lock(_synchronizer);
		const auto it = _instances.find(key);
		if (_instances.end() != it)
		{
			return &*it;
		}
		return nullptr;
	}

	const T* Ensure(const T& key)
	{
		std::lock_guard<std::shared_mutex> lock(_synchronizer);
		auto it = _instances.find(key);
		if (_instances.end() != it)
		{
			return &*it;
		}

		const auto it2 = _instances.emplace(key);
		it = it2.first;
		const T* result = &*it;
		return result;
	}

private:
	T _default;
	std::shared_mutex _synchronizer;
	std::unordered_set<T, H, E> _instances;
};
