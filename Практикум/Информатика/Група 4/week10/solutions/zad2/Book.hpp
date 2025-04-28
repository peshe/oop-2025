#pragma once
#include <cstring>
#include <ostream>
#include <istream>
#include <iostream>
#include <new>

class Book
{
private:
    char *title;
    char *author;
    unsigned pages;
    unsigned short int isbn;
    static unsigned id;

protected:
    void setIsbn(unsigned short int isbn)
    {
        this->isbn = isbn;
    };

public:
    Book(char *title, char *author, unsigned pages) : title(nullptr), author(nullptr)
    {
        if (id > 500 || title == nullptr || author == nullptr)
        {
            throw std::exception();
        }
        setTitle(title);
        setIsbn(id++);
        setAuthor(author);
        setPages(pages);
    }
    Book(const Book &book) : title(nullptr), author(nullptr)
    {
        setTitle(book.title);
        setIsbn(book.id);
        setAuthor(book.author);
        setPages(book.pages);
    }
    Book &operator=(const Book &book)
    {
        this->title = nullptr;
        this->author = nullptr;
        setTitle(book.title);
        setIsbn(book.id);
        setAuthor(book.author);
        setPages(book.pages);
    }
    ~Book()
    {
        delete[] author;
        delete[] title;
    }

    unsigned getPages() const
    {
        return this->pages;
    };
    char *getAuthor() const
    {
        return this->author;
    };
    char *getTitle() const
    {
        return this->title;
    };
    unsigned short int getIsbn() const
    {
        return this->isbn;
    };

    void setPages(unsigned page)
    {
        this->pages = page;
    };
    void setAuthor(char *string)
    {

        if (this->author != nullptr)
        {
            delete[] this->author;
        }
        this->author = new (std::nothrow) char[1000];
        if (this->author == nullptr)
            throw std::exception();
        strncpy(this->author, string, 1000);
    };
    void setTitle(char *string)
    {
        if (this->title != nullptr)
        {
            delete[] this->title;
        }
        this->title = new (std::nothrow) char[1000];
        if (this->title == nullptr)
            throw std::exception();
        strncpy(this->title, string, 1000);
    };

    bool operator>(const Book &b) const
    {
        return this->pages > b.pages;
    }
    bool operator<(const Book &b) const
    {
        return this->pages < b.pages;
    }
    bool operator>=(const Book &b) const
    {
        return !(*this < b);
    }
    bool operator<=(const Book &b) const
    {
        return !(this->pages > b.pages);
    }
    bool operator==(const Book &b) const
    {
        return !((*this > b) || (*this < b));
    }

    std::ostream &printValue(std::ostream &stream)
    {
        if (!stream)
        {
            throw std::exception();
        }
        stream << "Book {\n\t title: ";
        stream << this->title;
        stream << "\n\tauthor: " << this->author << "\n\tpages: " << this->pages << "\n\tisbn: IS-INF" << this->isbn << "}\n";
        return stream;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Book &b)
    {
        if (!stream)
        {
            throw std::exception();
        }
        stream << b.title << "\n"
               << b.author << "\n"
               << b.pages << "\n"
               << b.isbn << "\n";
        return stream;
    }
    friend std::istream &operator>>(std::istream &stream, Book &b)
    {
        if (!stream)
        {
            throw std::exception();
        }
        if (b.title != nullptr)
        {
            delete[] b.title;
        }
        if (b.author != nullptr)
        {
            delete[] b.author;
        }
        b.title = new (std::nothrow) char[1000];
        if (b.title == nullptr)
            throw std::exception();

        b.author = new (std::nothrow) char[1000];
        if (b.author == nullptr)
        {
            delete[] b.title;
            throw std::exception();
        }

        stream.getline(b.title, 1000);
        stream.getline(b.author, 1000);
        stream >> b.pages;
        stream >> b.isbn;
        return stream;
    }
};

unsigned Book::id = 0;