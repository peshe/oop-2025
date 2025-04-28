#pragma once

#include <cstddef>

#include "book.hpp"

class BookVector
{
	Book** books;
	std::size_t sz;
	std::size_t cap;

	static constexpr std::size_t initial_capacity = 16;
	static_assert(initial_capacity != 0, "initial_capacity cannot be 0");

	void reserve(std::size_t new_cap);
public:
	BookVector(): books(new Book*[initial_capacity]), sz(0), cap(initial_capacity) {}
	BookVector(const BookVector&) = delete;
	BookVector& operator=(const BookVector&) = delete;
	~BookVector() { delete[] books; }

	Book* operator[](std::size_t ind) { return books[ind]; }
	const Book* operator[](std::size_t ind) const { return books[ind]; }

	void push_back(Book* b);
	void pop_back();
	void erase(std::size_t ind);
};

class BookShelfRow
{
	BookVector books;
	std::size_t current_pages = 0;
	std::size_t max_pages = 0;
public:
	void change_capacity(std::size_t new_capacity)
	{
		while(current_pages > new_capacity)
		{
			books.pop_back();
			// todo: notify book
		}
		max_pages = new_capacity;
	}
};

class BookShelf
{
	BookShelfRow* rows;
	const std::size_t rows_cnt;
public:
	BookShelf(std::size_t rows_cnt, std::size_t pages_per_row): rows(new BookShelfRow[rows_cnt]), rows_cnt(rows_cnt)
	{
		change_capacity(pages_per_row);
	}
	BookShelf(const BookShelf&) = delete;
	~BookShelf() { delete[] rows; }

	void change_capacity(std::size_t pages_per_row)
	{
		for(std::size_t i = 0; i < rows_cnt; i++)
			rows[i].change_capacity(pages_per_row);
	}
};