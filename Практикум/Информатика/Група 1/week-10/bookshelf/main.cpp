#include <iostream>
#include <fstream>

#include "bookshelf.hpp"
#include "book.hpp"

class BookLoader
{
public:
	BookVector books;
	BookLoader(std::istream& is)
	{
		while(true) try
		{
			books.push_back(new Book(Book::read_book(is)));
		}
		catch(...) { break; }
	}
	~BookLoader()
	{
		while(books.size() > 0)
			delete books.pop_back();
	}
	std::ostream& print(std::ostream& os) const
	{
		for(std::size_t i = 0; i < books.size(); i++)
			books[i]->print(os);
		return os;
	}
};

void try_add_to_bookshelf(BookShelf& bs, BookVector& books)
{
	std::cout << "Not added:\n";
	for(std::size_t i = 0; i < books.size(); i++) try
	{
		bs.add(*books[i]);
	}
	catch(...)
	{
		books[i]->print(std::cout);
	}
}

int main() try
{
	std::size_t rows_cnt, max_pages_per_row;
	std::cin >> rows_cnt >> max_pages_per_row;
	std::cin.ignore();
	BookShelf bs(rows_cnt, max_pages_per_row);
	constexpr std::size_t max_path_len = 256;
	char path[max_path_len];
	std::cin.getline(path, max_path_len);

	std::ifstream ifs(path);
	if(!ifs)
		throw std::runtime_error("could not open file");

	BookLoader store(ifs);

	try_add_to_bookshelf(bs, store.books);
	std::cout << "======================\n";
	std::cout << "After adding to bookshelf:\n";
	store.print(std::cout);

	std::cout << "======================\n";
	Book* rana = bs.find("Рана");
	std::cout << "Book 'Рана' " << (rana ? "" : "not ") << "found\n";

	if(rana)
		bs.remove(*rana); // or equivalently, `rana->remove_from_shelf()`

	std::cout << "======================\n";
	std::cout << "After removing 'Рана':\n";
	store.print(std::cout);

	return 0;
}
catch(const std::exception& e)
{
	std::cerr << e.what() << '\n';
	return 1;
}