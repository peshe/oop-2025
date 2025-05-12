#include "bookshelf.hpp"

// BookVector member functions:

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

Book* BookVector::pop_back()
{
	return erase(sz - 1);
}

// BookShelfRow member functions:

Book* BookVector::erase(std::size_t ind)
{
	std::swap(books[ind], books[--sz]);
	return books[sz];
}

void BookShelfRow::change_capacity(std::size_t new_capacity)
{
	while(current_pages > new_capacity)
	{
		Book* b = books.pop_back();
		b->remove_from_shelf();
		current_pages -= b->Pages();
	}
	max_pages = new_capacity;
}

std::size_t BookShelfRow::find(const Book* b) const
{
	for(std::size_t i = 0; i < books.size(); i++)
		if(books[i] == b)
			return i;
	return invalid_pos;
}

bool BookShelfRow::remove(Book* b)
{
	std::size_t ind = find(b);
	if(ind == invalid_pos) return false;
	books.erase(ind);
	b->remove_from_shelf();
	current_pages -= b->Pages();
	return true;
}

bool BookShelfRow::add(Book *b)
{
	if(current_pages + b->Pages() > max_pages)
		return false;
	books.push_back(b);
	current_pages += b->Pages();
	return true;
}

const Book* BookShelfRow::find(const NonemptyString& title) const
{
	for(std::size_t i = 0; i < books.size(); i++)
		if(title == books[i]->Title())
			return books[i];
	return nullptr;
}

// BookShelf member functions:

BookShelf::Position BookShelf::find(const Book& b) const
{
	for(std::size_t i = 0; i < rows_cnt; i++)
		if(std::size_t ind = rows[i].find(&b); ind != invalid_pos)
			return {i, ind};
	return {invalid_pos, invalid_pos};
}

bool BookShelf::contains(const Book& b) const
{
	return find(b).row != invalid_pos;
}

BookShelf::BookShelf(std::size_t rows_cnt, std::size_t pages_per_row): rows(new BookShelfRow[rows_cnt]), rows_cnt(rows_cnt)
{
	change_capacity(pages_per_row);
}

void BookShelf::change_capacity(std::size_t pages_per_row)
{
	for(std::size_t i = 0; i < rows_cnt; i++)
		rows[i].change_capacity(pages_per_row);
}

void BookShelf::remove(Book& b)
{
	if(!contains(b)) return;
	for(std::size_t i = 0; i < rows_cnt; i++)
		if(rows[i].remove(&b))
			return;
}

void BookShelf::add(Book& b)
{
	if(b.Placed_on() == this) return;
	if(b.Placed_on()) throw std::runtime_error("cannot add book to shelf: already in another");
	if(contains(b)) return;
	for(std::size_t i = 0; i < rows_cnt; i++)
		if(rows[i].add(&b))
		{
			b.place_on(*this);
			return;
		}
	throw std::runtime_error("could not add the book to any row");
}

const Book* BookShelf::find(const NonemptyString& title) const
{
	for(std::size_t i = 0; i < rows_cnt; i++)
		if(const Book *b = rows[i].find(title))
			return b;
	return nullptr;
}
Book* BookShelf::find(const NonemptyString& title)
{
	return const_cast<Book*>(const_cast<const BookShelf*>(this)->find(title));
}