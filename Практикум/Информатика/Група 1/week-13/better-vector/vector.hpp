#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <iterator>
#include <cstddef>
#include <new>


// just noticed that my Vector does not behave correctly if the destructor of T throws, oops :))
template<class T>
class Vector
{
	T* arr;
	std::size_t sz, cap;
	void destroyAll()
	{
		destroy(0, sz);
	}
	void destroy(std::size_t ind, std::size_t cnt)
	{
		for(std::size_t i = 0; i < cnt; ++i)
			arr[ind + i].~T();
	}
	static T* allocate(std::size_t cnt)
	{
		return reinterpret_cast<T*>(operator new[](cnt * sizeof(T)));
	}
	static void deallocate(T* arr)
	{
		operator delete[](arr);
	}
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	Vector(): arr(nullptr), sz(0), cap(0) {}
	Vector(std::size_t cnt): sz(cnt), cap(cnt)
	{
		arr = allocate(cnt);
		std::size_t i;
		try
		{
			for(i = 0; i < cnt; ++i)
				new(arr + i) T();
		}
		catch(...)
		{
			destroy(0, i);
			deallocate(arr);
			throw;
		}
	}
	Vector(std::size_t cnt, const T& val): sz(cnt), cap(cnt)
	{
		arr = allocate(cnt);
		std::size_t i;
		try
		{
			for(i = 0; i < cnt; ++i)
				new(arr + i) T(val);
		}
		catch(...)
		{
			destroy(0, i);
			deallocate(arr);
			throw;
		}
	}
	Vector(const Vector& v): sz(v.sz), cap(v.sz)
	{
		arr = allocate(v.sz);
		std::size_t i;
		try
		{
			for(i = 0; i < v.sz; ++i)
				new(arr + i) T(v[i]);
		}
		catch(...)
		{
			destroy(0, i);
			deallocate(arr);
			throw;
		}
	}
	Vector(Vector&& v) noexcept: arr(std::exchange(v.arr, nullptr)), sz(std::exchange(v.sz, 0)), cap(std::exchange(v.cap, 0)) {}
	~Vector()
	{
		destroyAll();
		deallocate(arr);
	}
	Vector& operator=(const Vector& v)
	{
		if(this != &v)
		{
			std::size_t i;
			if(cap < v.cap)
			{
				T* temp = allocate(v.cap);
				try
				{
					for(i = 0; i < v.sz; ++i)
						new(temp + i) T(v[i]);
				}
				catch(...)
				{
					for(std::size_t j = 0; j < i; ++j)
						temp[j].~T();
					deallocate(temp);
					throw;
				}
				destroyAll();
				deallocate(arr);
				arr = temp;
				cap = v.cap;
			}
			else
			{
				for(i = 0; i < v.sz && i < sz; ++i)
					arr[i] = v[i];
				try
				{
					for(; i < v.sz; ++i)
						new(arr + i) T(v[i]);
				}
				catch(...)
				{
					sz = i;
					throw;
				}
				for(; i < sz; ++i)
					arr[i].~T();
			}
			sz = v.sz;
		}
		return *this;
	}
	Vector& operator=(Vector&& v) noexcept
	{
		destroyAll();
		std::swap(arr, v.arr);
		std::swap(cap, v.cap);
		sz = std::exchange(v.sz, 0);
		return *this;
	}
	void reserve(std::size_t newCap)
	{
		if(newCap <= cap) return;
		T* temp = allocate(newCap);
		std::size_t i;
		try
		{
			for(i = 0; i < sz; ++i)
				new(temp + i) T(std::move_if_noexcept(arr[i]));
		}
		catch(...)
		{
			for(std::size_t j = 0; j < i; ++j)
				temp[j].~T();
			deallocate(temp);
			throw;
		}
		destroyAll();
		deallocate(arr);
		arr = temp;
		cap = newCap;
	}
	T& operator[](std::size_t n)
	{
		return arr[n];
	}
	const T& operator[](std::size_t n) const
	{
		return arr[n];
	}
	const T& at(std::size_t n) const
	{
		if(n >= sz) throw std::out_of_range("out of range");
		return arr[n];
	}
	T& at(std::size_t n)
	{
		if(n >= sz) throw std::out_of_range("out of range");
		return arr[n];
	}
	std::size_t size() const noexcept
	{
		return sz;
	}
	std::size_t capacity() const noexcept
	{
		return cap;
	}
	bool empty() const noexcept
	{
		return !sz;
	}
	iterator begin() noexcept
	{
		return iterator(arr);
	}
	const_iterator begin() const noexcept
	{
		return const_iterator(arr);
	}
	const_iterator cbegin() const noexcept
	{
		return const_iterator(arr);
	}
	iterator end() noexcept
	{
		return iterator(arr + sz);
	}
	const_iterator end() const noexcept
	{
		return const_iterator(arr + sz);
	}
	const_iterator cend() const noexcept
	{
		return const_iterator(arr + sz);
	}
	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(end());
	}
	const_reverse_iterator rbegin() const noexcept
	{
		return const_reverse_iterator(end());
	}
	const_reverse_iterator crbegin() const noexcept
	{
		return const_reverse_iterator(end());
	}
	reverse_iterator rend() noexcept
	{
		return reverse_iterator(begin());
	}
	const_reverse_iterator rend() const noexcept
	{
		return const_reverse_iterator(begin());
	}
	const_reverse_iterator crend() const noexcept
	{
		return const_reverse_iterator(begin());
	}
	void clear()
	{
		destroyAll();
		sz = 0;
	}
	void push_back(const T& val)
	{
		insert(end(), val);
	}
	void push_back(T&& val)
	{
		insert(end(), std::move(val));
	}
	void pop_back()
	{
		erase(end() - 1);
	}
	iterator insert(const_iterator pos, const T& val)
	{
		std::size_t p = pos - begin();
		if(sz == cap) reserve(cap ? 2 * cap : 1);
		if(p == sz)
		{
			new(arr + sz) T(val);
			return begin() + sz++;
		}
		new(arr + sz) T(std::move(arr[sz - 1]));
		for(std::size_t i = sz - 1; i > p; --i)
			arr[i] = std::move(arr[i - 1]);
		arr[p] = val;
		++sz;
		return begin() + p;
	}
	iterator insert(const_iterator pos, T&& val)
	{
		std::size_t p = pos - begin();
		if(sz == cap) reserve(cap ? 2 * cap : 1);
		if(p == sz)
		{
			new(arr + sz) T(std::move(val));
			return begin() + sz++;
		}
		new(arr + sz) T(std::move(arr[sz - 1]));
		for(std::size_t i = sz - 1; i > p; --i)
			arr[i] = std::move(arr[i - 1]);
		arr[p] = std::move(val);
		++sz;
		return begin() + p;
	}
	template<class... Args>
	void emplace_back(Args&&... args)
	{
		if(sz == cap) reserve(cap ? 2 * cap : 1);
		new(arr + sz++) T(std::forward<Args>(args)...);
	}
	void erase(const_iterator pos)
	{
		std::size_t p = pos - begin();
		for(std::size_t i = p + 1; i < sz; ++i)
			arr[i - 1] = std::move(arr[i]);
		arr[--sz].~T();
	}
	void resize(std::size_t cnt)
	{
		while(sz > cnt) pop_back();
		if(cap < cnt) reserve(cnt);
		std::size_t i;
		try
		{
			for(i = sz; i < cnt; ++i)
				new(arr + i) T();
		}
		catch(...)
		{
			destroy(sz, i - sz);
			throw;
		}
		sz = cnt;
	}
	void resize(std::size_t cnt, const T& val)
	{
		while(sz > cnt) pop_back();
		if(cap < cnt) reserve(cnt);
		std::size_t i;
		try
		{
			for(i = sz; i < cnt; ++i)
				new(arr + i) T(val);
		}
		catch(...)
		{
			destroy(sz, i - sz);
			throw;
		}
		sz = cnt;
	}
	bool operator<(const Vector& r) const
	{
		for(std::size_t i = 0; i < sz && i < r.sz; ++i)
			if(arr[i] < r.arr[i]) return true;
		return sz < r.sz;
	}
	bool operator>(const Vector& r) const
	{
		return r < *this;
	}
	bool operator<=(const Vector& r) const
	{
		return !(r < *this);
	}
	bool operator>=(const Vector& r) const
	{
		return !(*this < r);
	}
	bool operator==(const Vector& r) const
	{
		if(sz != r.sz) return false;
		for(std::size_t i = 0; i < sz; ++i)
			if(!(arr[i] == r.arr[i])) return false;
		return true;
	}
	bool operator!=(const Vector& r) const
	{
		return !(*this == r);
	}
};
