#pragma once
#include "Book.hpp"
#include <algorithm>
class Bookshelf
{
private:
    Book ***b;
    unsigned int *bookShelf;
    unsigned int *bookOffset;
    long unsigned maxX;
    long unsigned maxY;

public:
    Bookshelf(unsigned int N, unsigned int M) : maxX(N), maxY(M)
    {
        b = new Book **[N];
        bookShelf = new unsigned int[N]{0};
        bookOffset = new unsigned int[N]{0};
        for (size_t i = 0; i < N; i++)
        {
            b[i] = new Book *[M]
            { nullptr };
        }
    }

    Bookshelf(const Bookshelf &b) = delete;
    Bookshelf &operator=(const Bookshelf &b) = delete;

    bool bookExists(const char *name)
    {
        for (size_t i = 0; i < maxX; i++)
        {
            for (size_t j = 0; j < bookOffset[i]; j++)
            {
                if (strncmp(name, this->b[i][j]->getTitle(), 1000) == 0)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool bookRemove(const char *name)
    {
        for (size_t i = 0; i < maxX; i++)
        {
            for (size_t j = 0; j < bookOffset[i]; j++)
            {
                if (strncmp(name, this->b[i][j]->getTitle(), 1000) == 0)
                {
                    for (size_t k = j; k < bookOffset[i] - 1; k++)
                    {
                        this->b[i][k] = this->b[i][k + 1];
                    }
                    this->b[i][bookOffset[i] - 1] = nullptr;
                    this->bookOffset[i] -= 1;
                    return true;
                }
            }
        }
        return false;
    }

    void insertBook(Book *b)
    {
        for (size_t i = 0; i < maxX; i++)
        {
            if (bookShelf[i] + b->getPages() <= maxY)
            {
                this->b[i][bookOffset[i]] = b;
                bookOffset[i]++;
                bookShelf[i] += b->getPages();
                break;
            }
        }
    }

    void resizeBookshelf(unsigned long int M)
    {
        for (size_t i = 0; i < maxX; i++)
        {
            Book **temp = new Book *[M]
            { nullptr };
            unsigned newVal = 0;
            unsigned newPages = 0;
            for (size_t j = 0; j < bookOffset[i]; j++)
            {
                if (newPages + this->b[i][j]->getPages() > M)
                {
                    break;
                }
                temp[newVal++] = this->b[i][j];
                newPages += this->b[i][j]->getPages();
            }
            delete[] this->b[i];
            this->b[i] = temp;
            bookOffset[i] = newVal;
            bookShelf[i] = newPages;
        }
        this->maxY = M;
    }

    ~Bookshelf()
    {
        for (size_t i = 0; i < maxX; ++i)
            delete[] b[i];
        delete[] b;
        delete[] bookShelf;
        delete[] bookOffset;
    }
};