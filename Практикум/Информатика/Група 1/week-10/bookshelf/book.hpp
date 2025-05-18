#pragma once

#include <iostream>
#include <utility>
#include <limits>

#include "nonemptyString.hpp"

class BookShelf;

class Book
{
private:
	NonemptyString title, author;
	unsigned page_cnt;

	static constexpr char id_prefix[] = "IS-INF-";
	static constexpr std::size_t id_digits_cnt = 4;
	char id[(sizeof(id_prefix) - 1) + id_digits_cnt + 1];
	static unsigned next_id;

	static constexpr unsigned max_alive = 500;
	static unsigned books_alive;

	BookShelf* placed_on = nullptr;

	void createId();
	void objectCreated();
	Book(): Book("0", "0", 0) {}
public:
	Book(NonemptyString title, NonemptyString author, unsigned page_cnt);
	Book(const Book& b): Book(b.title, b.author, b.page_cnt) {}
	Book(Book&& b) noexcept: Book(std::move(b.title), std::move(b.author), b.page_cnt) {}
	Book& operator=(Book b);
	~Book();

	NonemptyString& Title() { return title; }
	const NonemptyString& Title() const { return title; }
	NonemptyString& Author() { return author; }
	const  NonemptyString& Author() const { return author; }
	unsigned Pages() const { return page_cnt; }
	BookShelf* Placed_on() { return placed_on; }
	const BookShelf* Placed_on() const { return placed_on; }

	std::ostream& print(std::ostream& os) const;
	std::istream& read(std::istream& is);

	static Book read_book(std::istream& is);

	void remove_from_shelf();
	void place_on(BookShelf& bs);
};
