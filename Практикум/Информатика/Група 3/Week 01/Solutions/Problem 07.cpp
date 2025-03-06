#include <limits>

#include <cassert>

#include <cstring>

#include <iostream>



#define MAX 1024



unsigned int    readSize();



char**  buildStrings(                               unsigned int size);
void    clearStrings(char**& strings,               unsigned int size);
void    printStrings(const char* const* strings,    unsigned int size);



void reverseString(char*& string, unsigned int size);



int main() {
    unsigned int size = readSize();


    char** strings = buildStrings(size);

    if (strings == nullptr) {
        std::cout << "Allocating Memory... ERROR!" << std::endl;

        return 1;
    }


    printStrings(strings, size);


    for (unsigned int i = 0; i < size; ++i) {
        reverseString(strings[i], strlen(strings[i]));
    }

    printStrings(strings, size);


    clearStrings(strings, size);


    return 0;
}



unsigned int readSize() {
    unsigned int size = 0;

    while (true) {
        std::cout << "Enter the size: ";

        std::cin >> size;

        if (std::cin.fail()) {
            std::cin.clear  ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            if (size == 0) {
                continue;
            } else {
                return size;
            }             
        }
    }
}



char** buildStrings(unsigned int size) {
    assert(size !=  0);

    char** strings = new (std::nothrow) char*[size];

    std::cin.ignore();

    if (strings != nullptr) {
        for (unsigned int i = 0; i < size; ++i) {
            strings[i] = new (std::nothrow) char[MAX];

            if (strings[i] == nullptr) {
                clearStrings(strings, i);

                return nullptr;
            } else {
                std::cin.getline(strings[i], MAX, '\n');
            }
        }
    }

    return strings;
}

void clearStrings(char**& strings, unsigned int size) {
    assert(strings  !=  nullptr );
    assert(size     !=  0       );

    for (unsigned int i = 0; i < size; ++i) {
        delete[] strings[i];
    }

    delete[] strings;

    strings = nullptr;
}

void printStrings(const char* const* strings, unsigned int size) {
    assert(strings  !=  nullptr );
    assert(size     !=  0       );

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "The strings are: " << std::endl;

    for (unsigned int i = 0; i < size; ++i) {
        std::cout << strings[i] << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}



void reverseString(char*& string, unsigned int size) {
    assert(string   !=  nullptr );
    assert(size     !=  0       );

    for (unsigned int i = 0; i < size / 2; ++i) {
        std::swap(string[i], string[size - i - 1]);
    }
}
