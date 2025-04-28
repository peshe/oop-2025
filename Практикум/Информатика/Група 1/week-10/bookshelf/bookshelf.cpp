#include "bookshelf.hpp"

void BookVector::reserve(std::size_t new_cap)
{
	if(new_cap <= cap) return;
	Book** tmp = new Book * [new_cap];
	for(std::size_t i = 0; i < sz; i++) //std::copy(books, books+sz, tmp);
		tmp[i] = books[i];
	delete[] books;
	books = tmp;
	cap = new_cap;
}

void BookVector::push_back(Book* b)
{
	if(sz == cap)
		reserve(2 * cap);
	books[sz] = b;
	sz++;
}

void BookVector::pop_back()
{
	erase(sz - 1);
}

void BookVector::erase(std::size_t ind)
{
	std::swap(books[ind], books[--sz]);
}