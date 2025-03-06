#include <limits>

#include <cassert>

#include <iostream>



int             readNumb();
unsigned int    readSize();



int*    buildArray(                     unsigned int size   );
void    clearArray(         int*& array                     );

void    inputArray(         int* array, unsigned int size   );
void    printArray(const    int* array, unsigned int size   );



int findMinNumber(const int* array, unsigned int size);
int findMaxNumber(const int* array, unsigned int size);



int findArraySum    (const int* array, unsigned int size);
int findArrayProduct(const int* array, unsigned int size);




int main() {
    unsigned int size = readSize();


    int* array = buildArray(size);

    if (array == nullptr) {
        std::cout << "Allocating Memory... ERROR!" << std::endl;

        return 1;
    }


    int minNumber = findMinNumber(array, size);
    int maxNumber = findMaxNumber(array, size);
    
    int result1 = findArraySum      (array, size);
    int result2 = findArrayProduct  (array, size);


    std::cout << "The MIN number of the array is: " << minNumber << std::endl;
    std::cout << "The MAX number of the array is: " << maxNumber << std::endl;

    std::cout << "The SUM       of the array is: " << result1 << std::endl;
    std::cout << "The PRODUCT   of the array is: " << result2 << std::endl;


    clearArray(array);


    return 0;
}



int readNumb() {
    int number = 0;

    while (true) {
        std::cin >> number;

        if (std::cin.fail()) {
            std::cin.clear  ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            return number;
        }
    }
}

unsigned int readSize() {
    unsigned int size = 0;

    while (size == 0) {
        std::cout << "Enter the size of the array: ";

        std::cin >> size;

        if (std::cin.fail()) {
            std::cin.clear  ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

            size = 0;
        } else {
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

            return size;
        }
    }

    return size;
}



int* buildArray(unsigned int size) {
    assert(size !=  0   );

    int* array = new (std::nothrow) int[size];

    if (array != nullptr) {
        inputArray(array, size);
        printArray(array, size);
    }
    
    return array;
}

void clearArray(int*& array) {
    assert(array    !=  nullptr );
    
    delete[] array;

    array = nullptr;
}



void inputArray(int* array, unsigned int size) {
    assert(array    !=  nullptr );
    assert(size     !=  0       );

    std::cout << "Enter the elements of the array: ";

    for (unsigned int i = 0; i < size; ++i) {
        array[i] = readNumb();
    }
}

void printArray(const int* array, unsigned int size) {
    assert(array    !=  nullptr );
    assert(size     !=  0       );

    std::cout << "The elements of the array are: ";

    for (unsigned int i = 0; i < size; ++i) {
        std::cout << array[i] << ' ';
    }

    std::cout << std::endl;
}



int findMinNumber(const int* array, unsigned int size) {
    assert(array    !=  nullptr );
    assert(size     !=  0       );

    int result = array[0];

    for (unsigned int i = 1; i < size; ++i) {
        result = std::min(result, array[i]);
    }

    return result;
}

int findMaxNumber(const int* array, unsigned int size) {
    assert(array    !=  nullptr );
    assert(size     !=  0       );

    int result = array[0];

    for (unsigned int i = 1; i < size; ++i) {
        result = std::max(result, array[i]);
    }

    return result;
}



int findArraySum(const int* array, unsigned int size) {
    assert(array    !=  nullptr );
    assert(size     !=  0       );

    int result = 0;

    for (unsigned int i = 0; i < size; ++i) {
        result = result + array[i];
    }

    return result;
}

int findArrayProduct(const int* array, unsigned int size) {
    assert(array    !=  nullptr );
    assert(size     !=  0       );

    int result = 1;

    for (unsigned int i = 0; i < size; ++i) {
        result = result * array[i];
    }

    return result;
}
