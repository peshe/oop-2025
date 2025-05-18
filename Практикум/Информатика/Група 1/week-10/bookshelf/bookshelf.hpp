#pragma once

#include <cstddef>

#include "book.hpp"

constexpr std::size_t invalid_pos = -1;

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

	std::size_t size() const { return sz; }
	Book* operator[](std::size_t ind) { return books[ind]; }
	const Book* operator[](std::size_t ind) const { return books[ind]; }

	void push_back(Book* b);
	Book* pop_back();
	Book* erase(std::size_t ind);
};

class BookShelfRow
{
	BookVector books;
	std::size_t current_pages = 0;
	std::size_t max_pages = 0;
public:
	void change_capacity(std::size_t new_capacity);
	std::size_t find(const Book* b) const;
	bool remove(Book* b);
	bool add(Book *b);
	const Book* find(const NonemptyString& title) const;
};

class BookShelf
{
	BookShelfRow* rows;
	const std::size_t rows_cnt;
public:
	struct Position
	{
		std::size_t row, ind;
	};

	Position find(const Book& b) const;
	bool contains(const Book& b) const;

	BookShelf(std::size_t rows_cnt, std::size_t pages_per_row);
	BookShelf(const BookShelf&) = delete;
	~BookShelf() { delete[] rows; }

	void change_capacity(std::size_t pages_per_row);
	void remove(Book & b);
	void add(Book& b);

	const Book* find(const NonemptyString& title) const;
	Book* find(const NonemptyString& title);
};