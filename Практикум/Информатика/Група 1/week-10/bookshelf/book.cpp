#include "book.hpp"
#include "bookshelf.hpp"

unsigned Book::books_alive = 0;
unsigned Book::next_id = 0;

void Book::createId()
{
	std::sprintf(id, "%s%0*u", id_prefix, (int)id_digits_cnt, next_id++);
}

void Book::objectCreated()
{
	if(books_alive >= max_alive)
		throw std::runtime_error("max books amount reached");
	books_alive++;
}

Book::Book(NonemptyString title, NonemptyString author, unsigned page_cnt):
	title(std::move(title)), author(std::move(author)), page_cnt(page_cnt)
{
	createId();
	objectCreated();
}

Book& Book::operator=(Book b)
{
	remove_from_shelf();
	std::swap(title, b.title);
	std::swap(author, b.author);
	std::swap(page_cnt, b.page_cnt);
	return *this;
}

Book::~Book()
{
	books_alive--;
	remove_from_shelf();
}

std::ostream& Book::print(std::ostream& os) const
{
	title.print(os);
	author.print(os);
	os << page_cnt << '\n';
	os << id << '\n';
	if(placed_on)
	{
		BookShelf::Position pos = placed_on->find(*this);
		os << "placed on row: " << pos.row << "; ind: " << pos.ind;
	}
	else os << "Not placed on a bookshelf";
	os << '\n';
	return os;
}

std::istream& Book::read(std::istream& is)
{
	Book tmp;
	tmp.title.read(is);
	tmp.author.read(is);
	is >> tmp.page_cnt;
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // '\n' after page_cnt
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // id
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // info for bookshelf
	*this = std::move(tmp);
	return is;
}

void Book::remove_from_shelf()
{
	if(!placed_on) return;
	BookShelf* was_placed_on = placed_on;
	placed_on = nullptr;
	was_placed_on->remove(*this);
}

void Book::place_on(BookShelf& bs)
{
	if(placed_on == &bs) return;
	if(placed_on) throw std::runtime_error("already on some other bookshelf");
	placed_on = &bs;
	try
	{
		bs.add(*this);
	}
	catch(...)
	{
		placed_on = nullptr;
		throw;
	}
}

Book Book::read_book(std::istream& is)
{
	Book b;
	b.read(is);
	if(!is) throw std::runtime_error("reading book failed");
	return b;
}