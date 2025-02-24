#include <iostream>
#include <cstdlib> // For malloc and free

/*
Basic steps of dynamic memory allocation in C++ and C:
    1. Try to allocate the memory
    2. Check if the allocation is successfull
    3. Use the memory
    4. Delete the allocated memory
*/

void allocateIntInCpp();
void allocateIntInC();

void fillArray(int* array, std::size_t size, int multiplier);
void printArray(int* array, std::size_t size);

void allocateArrayInCpp();
void allocateArrayInC();

void differenceBetweenNullAndNullptr();

int main() {
    allocateIntInCpp();
    allocateIntInC();

    allocateArrayInCpp();
    allocateArrayInC();

    differenceBetweenNullAndNullptr();    

    return 0;
}

void allocateIntInCpp() {
    /* Dynamic memory allocation in C++
     * Allocate memory for an integer with nothrow
        * nothrow is used to return a null pointer if the memory allocation fails.
        * If nothrow is not used, the program will throw an exception (we will discuss this later in the course)
        * if the memory allocation fails and the program will terminate.
    */
    int* ptr = new (std::nothrow) int;

    if (ptr == nullptr) {
        std::cerr << "Memory allocation failed" << std::endl;
        
        return;
    }

    *ptr = 10; // Assign value to the allocated memory

    std::cout << "Value at ptr: " << *ptr << std::endl; // Output the value

    delete ptr; // Deallocate the memory
    ptr = nullptr; // Set the pointer to null
}

void allocateIntInC() {
    // Dynamic memory allocation in C
    int* cPtr = (int*)malloc(sizeof(int)); // Allocate memory for an integer
    
    if (cPtr == nullptr) {
        std::cerr << "Memory allocation failed" << std::endl;
        return;
    }
    
    *cPtr = 20; // Assign value to the allocated memory
    
    std::cout << "Value at cPtr: " << *cPtr << std::endl; // Output the value

    free(cPtr); // Deallocate the memory
    cPtr = NULL; // Set the pointer to null
}

void fillArray(int* array, std::size_t size, int multiplier) {
    for (std::size_t i = 0; i < size; ++i) {
        array[i] = i * multiplier; // Assign values to the array
    }
}

void printArray(int* array, std::size_t size) {
    std::cout << "Array values: ";

    for (std::size_t i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }

    std::cout << std::endl;
}

void allocateArrayInCpp() {
    // Dynamic memory allocation for an array in C++
    int* arr = new(std::nothrow) int[5]; // Allocate memory for an array of 5 integers with nothrow

    if (arr == nullptr) {
        std::cerr << "Memory allocation failed" << std::endl;
        return;
    }

    fillArray(arr, 5, 2); // Fill the array with values
    printArray(arr, 5); // Output the array values

    delete[] arr; // Deallocate the array memory

    arr = nullptr; // Set the pointer to null
}

void allocateArrayInC() {
     // Dynamic memory allocation for an array in C
    int* cArr = (int*)malloc(5 * sizeof(int)); // Allocate memory for an array of 5 integers
    
    if (cArr == nullptr) {
        std::cerr << "Memory allocation failed" << std::endl;
        return;
    }
    
    fillArray(cArr, 5, 3); // Fill the array with values
    printArray(cArr, 5); // Output the array values

    free(cArr); // Deallocate the array memory
    cArr = NULL; // Set the pointer to null
}

void differenceBetweenNullAndNullptr() {
    // Difference between NULL and nullptr
    /*
    * nullptr is a keyword introduced in C++11 to represent a null pointer
    * - nullptr is type-safe and can be implicitly converted to any pointer type
    * - nullptr is preferred over NULL in modern C++ code
    * NULL is a macro defined in C to represent a null pointer
    * - NULL is not type-safe and can cause issues in C++ code
    * - NULL is still used in C code and older C++ code
    */
    int* ptr = nullptr; // nullptr is a keyword introduced in C++11 to represent a null pointer
    int* cPtr = NULL; // NULL is a macro defined in C to represent a null pointer

    int x = NULL; // NULL has a value of 0 (or (void*)0) and beacuse of that it can be assigned to variables. This can cause problems.
    // int y = nullptr; // nullptr cannot be assigned to normal variables because it is a pointer type.
}
