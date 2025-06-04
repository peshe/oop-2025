#pragma once

#include <exception>
#include <sstream>

template<typename T>
class DynamicArray
{
private:
	static const size_t defaultCap;
	T* elems;
	size_t cnt;
	size_t cap;

public:
	class Iterator
	{
	private:
		const DynamicArray* arr = nullptr;
		size_t curr;
		Iterator();

		friend class DynamicArray;

	public:
		T& next();
		bool hasNext() const;
	};

	DynamicArray();
	DynamicArray(const DynamicArray& o);
	~DynamicArray();

	DynamicArray& operator=(const DynamicArray& o);

	DynamicArray& operator*=(unsigned n);
	DynamicArray operator*(unsigned n) const;

	T& operator[](size_t ind) const;

	void add(const T& el);
	void append(const DynamicArray& o);
	size_t getSize() const;

	Iterator getIterator() const;
};

template<typename T>
const size_t DynamicArray<T>::defaultCap = 2;

template<typename T>
std::ostream& operator<<(std::ostream& s, const DynamicArray<T>& arr)
{
	s << "[";
	for (size_t i = 0; i < arr.getSize(); i++)
	{
		s << arr[i] << ", ";
	}
	s << "]";

	return s;
}

template<typename T>
DynamicArray<T>::DynamicArray()
{
	this->cap = DynamicArray<T>::defaultCap;
	this->cnt = 0;
	this->elems = new T[cap];
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& o)
{
	this->cap = o.cap;
	this->cnt = o.cnt;
	this->elems = new T[this->cap];

	for (size_t i = 0; i < o.cnt; i++)
	{
		this->elems[i] = o.elems[i];
	}
}

template<typename T>
DynamicArray<T>::~DynamicArray()
{
	delete this->elems;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& o)
{
	if (this == &o)
	{
		return *this;
	}

	delete[] this->elems;

	this->cap = o.cap;
	this->cnt = o.cnt;
	this->elems = new T[this->cap];

	for (size_t i = 0; i < o.cnt; i++)
	{
		this->elems[i] = o.elems[i];
	}

	return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator*=(unsigned n)
{
	DynamicArray cpy = *this;

	delete[] this->elems;
	size_t newCap = this->cnt * n;
	if (newCap == 0) 
	{
		newCap = DynamicArray<T>::defaultCap;
	}

	this->elems = new T[newCap];
	this->cnt = 0;
	this->cap = newCap;

	for (unsigned i = 0; i < n; i++) 
	{
		this->append(cpy);
	}

	return *this;
}

template<typename T>
DynamicArray<T> DynamicArray<T>::operator*(unsigned n) const
{
	DynamicArray<T> res = *this;
	res *= n;

	return res;
}

template<typename T>
T& DynamicArray<T>::operator[](size_t ind) const
{
	if (ind >= this->cnt)
	{
		std::ostringstream s;
		s << "Index out of range. Accessing " << ind << " but count is " << this->cnt << ".";
		throw std::out_of_range(s.str());
	}

	return this->elems[ind];
}

template<typename T>
void DynamicArray<T>::add(const T& el)
{
	if (this->cnt == this->cap)
	{
		this->cap *= 2;
		T* newElems = new T[this->cap];

		for (size_t i = 0; i < this->cnt; i++)
		{
			newElems[i] = this->elems[i];
		}

		delete[] this->elems;
		this->elems = newElems;
	}

	this->elems[this->cnt++] = el;
}

template<typename T>
void DynamicArray<T>::append(const DynamicArray& o)
{
	for (size_t i = 0; i < o.cnt; i++) 
	{
		this->add(o[i]);
	}
}

template<typename T>
size_t DynamicArray<T>::getSize() const
{
	return this->cnt;
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::getIterator() const
{
	DynamicArray<T>::Iterator it;
	it.arr = this;
	it.curr = 0;
	return it;
}

template<typename T>
DynamicArray<T>::Iterator::Iterator() {}

template<typename T>
T &DynamicArray<T>::Iterator::next()
{
	return (*this->arr)[this->curr++];
}

template<typename T>
bool DynamicArray<T>::Iterator::hasNext() const
{
	return this->curr < this->arr->cnt;
}