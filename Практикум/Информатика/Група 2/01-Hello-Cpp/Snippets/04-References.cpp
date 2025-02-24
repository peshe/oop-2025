#include <iostream>

/**
 * A reference in C++ is an alias for another variable. Once a reference is initialized to a variable,
 * it cannot be changed to refer to another variable. References are often used for parameter passing
 * in functions to avoid copying large objects and to allow functions to modify the arguments passed to them.
 * 
 * In C, pointers are used to achieve similar functionality, but references in C++ provide a more convenient
 * and safer way to work with variables.
 * 
 * Unlike pointers, references cannot be NULL and must be initialized when declared. References are also
 * automatically dereferenced, so you can use them as if they were the original variable.
 * 
 * You cannot have an array of references, but you can have an array of pointers.
 * You cannot have a reference to a reference, but you can have a pointer to a pointer.
 * IMPORTANT: int&& is an rvalue reference, but it is not a reference to a reference. We will discuss rvalue references later.
 */

// Function that uses a reference to modify the original variable
void increment(int& ref) {
    ref++; // Increment the value of the original variable
}

// Function that uses a const reference to read the value without modifying it
void printValue(const int& ref) {
    std::cout << "Value: " << ref << std::endl;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int a = 10;

    // Reference to variable 'a'
    int& refA = a;

    // Output the initial values
    std::cout << "Initial value of a: " << a << std::endl;
    std::cout << "Initial value of refA: " << refA << std::endl;

    // Modify the value using the reference
    refA = 20;

    // Output the modified values
    std::cout << "Modified value of a: " << a << std::endl;
    std::cout << "Modified value of refA: " << refA << std::endl;

    // Call function to increment the value using reference
    increment(a);

    // Output the incremented value
    std::cout << "Value of a after increment: " << a << std::endl;

    // Call function to print the value using const reference
    printValue(a);


    int arr[5] = {1, 2, 3, 4, 5};
    int& refArr = arr[0]; // Reference to the first element of the array. You cannot change the reference to point to another element.


    int val1 = 10;
    int val2 = 20;

    std::cout << "Before swap: val1 = " << val1 << ", val2 = " << val2 << std::endl;

    swap(val1, val2);

    std::cout << "After swap: val1 = " << val1 << ", val2 = " << val2 << std::endl;

    return 0;
}