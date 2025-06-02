#pragma once

#include <algorithm>
#include <cstddef>

template<class T>
class Vector
{
	T* data;
	std::size_t sz, cap;
	static constexpr std::size_t initial_capacity = 16;
public:
	Vector(): data(new T[initial_capacity]), sz(0), cap(initial_capacity) {}
	Vector(const Vector& other): data(new T[other.cap]), sz(other.sz), cap(other.cap)
	{
		try
		{
			for(std::size_t i = 0; i < other.sz; i++)
				data[i] = other.data[i];
		}
		catch(...)
		{
			delete[] data;
			throw;
		}
	}
	Vector(Vector&& other) noexcept: data(other.data), sz(other.sz), cap(other.cap)
	{
		other.data = nullptr;
		other.sz = 0;
		other.cap = 0;
	}
	~Vector()
	{
		delete[] data;
	}
	Vector& operator=(const Vector& other)
	{
		if(this != &other)
		{
			if(cap < other.sz)
			{
				T* tmp = new T[other.sz];
				delete[] data;
				data = tmp;
				cap = other.sz;
				sz = 0;
			}
			for(std::size_t i = 0; i < other.sz; i++)
				data[i] = other.data[i];
			sz = other.sz;
		}
		return *this;
	}
	Vector& operator=(Vector&& other) noexcept
	{
		std::swap(data, other.data);
		std::swap(sz, other.sz);
		std::swap(cap, other.cap);
		return *this;
	}

	std::size_t size() const noexcept
	{
		return sz;
	}
	bool empty() const noexcept
	{
		return size() == 0;
	}

	void push_back(const T& val)
	{
		if(sz == cap) reserve(std::max(2 * cap, initial_capacity));
		data[sz] = val;
		sz++;
	}

	void push_back(T&& val)
	{
		if(sz == cap) reserve(std::max(2 * cap, initial_capacity));
		data[sz] = std::move(val);
		sz++;
	}
	void pop_back()
	{
		sz--;
	}

	T& back()
	{
		return data[sz - 1];
	}
	const T& back() const
	{
		return data[sz - 1];
	}

	T& operator[](std::size_t ind)
	{
		return data[ind];
	}
	const T& operator[](std::size_t ind) const
	{
		return data[ind];
	}

	T& at(std::size_t ind)
	{
		if(ind >= sz)
			throw std::invalid_argument("index out of range");
		return data[ind];
	}
	const T& at(std::size_t ind) const
	{
		if(ind >= sz)
			throw std::invalid_argument("index out of range");
		return data[ind];
	}

	void reserve(std::size_t new_cap)
	{
		if(new_cap <= cap) return;
		T* tmp = new T[new_cap];
		try
		{
			for(std::size_t i = 0; i < sz; i++)
				tmp[i] = std::move(data[i]);
		}
		catch(...)
		{
			delete[] tmp;
			throw;
		}
		delete[] data;
		data = tmp;
		cap = new_cap;
	}
};