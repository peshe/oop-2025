#include <limits>

#include <cassert>

#include <iostream>



int         readElem();
std::size_t readSize();



void scenarioDynamicMemory1();
void scenarioDynamicMemory2();



int* buildArray(                        std::size_t  size                       );
void reszeArray(        int*&   array,  std::size_t& size1, std::size_t size2   );
void clearArray(        int*&   array                                           );

void inputArray(        int*    array,  std::size_t  size                       );
void printArray(const   int*    array,  std::size_t  size                       );



int main() {
    scenarioDynamicMemory1();
    scenarioDynamicMemory2();



    std::size_t size = readSize();


    int* array = buildArray(size);

    if (array == nullptr) {
        std::cout << "Allocating Memory... ERROR!" << std::endl;

        return 1;
    }


    reszeArray(array, size, size + 3);
    printArray(array, size          );


    clearArray(array);



    return 0;
}



int readElem() {
    int elem            =   0;

    while (true) {
        std::cin >> elem;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return elem;
        }
    }

    return elem;
}

std::size_t readSize() {
    std::size_t size    =   0;

    while (size == 0) {
        std::cout << "Enter the size of the array: ";

        std::cin >> size;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return size;
        }
    }

    return size;
}



void scenarioDynamicMemory1() {
    int* ptr = new (std::nothrow) int;

    if (ptr == nullptr) {
        std::cerr << "Allocating Memory... ERROR!" << std::endl;

        return;
    }

    *ptr = 1379;

    std::cout << "Pointer Value is: " << *ptr << std::endl;

    delete ptr;

    ptr = nullptr;
}

void scenarioDynamicMemory2() {
    int* ptr = new (std::nothrow) int(1379);

    if (ptr == nullptr) {
        std::cerr << "Allocating Memory... ERROR!" << std::endl;

        return;
    }

    std::cout << "Pointer Value is: " << *ptr << std::endl;

    delete ptr;

    ptr = nullptr;
}



int* buildArray(std::size_t size) {
    int* array = new (std::nothrow) int[size];

    if (array != nullptr) {
        inputArray(array, size);
        printArray(array, size);
    }

    return array;
}

void reszeArray(int*& array, std::size_t& size1, std::size_t size2) {
    assert(array    !=  nullptr );
    assert(size1    !=  0       );
    assert(size2    !=  0       );

    int* temporary = new (std::nothrow) int[size2]();

    if (temporary == nullptr) {
        return;
    }

    for (std::size_t i = 0; i < size1; ++i) {
        temporary[i] = array[i];
    }

    delete[] array;

    array = temporary   ;
    size1 = size2       ;
}

void clearArray(int*& array) {
    assert(array    !=  nullptr );

    delete[] array;

    array = nullptr;
}



void inputArray(int* array, std::size_t size) {
    assert(array    !=  nullptr );
    assert(size     !=  0       );

    std::cout << "Enter the elements of the array: ";

    for (std::size_t i = 0; i < size; ++i) {
        std::cin >> array[i];
    }
}

void printArray(const int* array, std::size_t size) {
    assert(array    !=  nullptr );
    assert(size     !=  0       );

    std::cout << "The elements of the array are: ";

    for (std::size_t i = 0; i < size; ++i) {
        std::cout << array[i] << ' ';
    }

    std::cout << std::endl;
}
