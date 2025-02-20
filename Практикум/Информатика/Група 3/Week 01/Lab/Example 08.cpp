#include <iostream>



void scenarioDynamicMemory();



int* buildArray(                        std::size_t  size                       );
void reszeArray(        int*&   array,  std::size_t& size1, std::size_t size2   );
void clearArray(        int*&   array                                           );

void inputArray(        int*    array,  std::size_t  size                       );
void printArray(const   int*    array,  std::size_t  size                       );



int main() {
    scenarioDynamicMemory();



    std::size_t size = 0;

    do {
        std::cout << "Enter the size of the array: ";

        std::cin >> size;
    } while (size == 0);


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



void scenarioDynamicMemory() {
    int* ptr = new (std::nothrow) int;

    if (ptr == nullptr) {
        std::cerr << "Allocating Memory... ERROR!" << std::endl;

        return;
    }

    *ptr = 10;

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
    delete[] array;

    array = nullptr;
}



void inputArray(int* array, std::size_t size) {
    std::cout << "Enter the elements of the array: ";

    for (std::size_t i = 0; i < size; ++i) {
        std::cin >> array[i];
    }
}

void printArray(const int* array, std::size_t size) {
    std::cout << "The elements of the array are: ";

    for (std::size_t i = 0; i < size; ++i) {
        std::cout << array[i] << ' ';
    }

    std::cout << std::endl;
}
