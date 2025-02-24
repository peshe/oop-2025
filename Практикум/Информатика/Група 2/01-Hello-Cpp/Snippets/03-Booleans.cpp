#include <iostream>

int main() {
    // In C, we typically use integers to represent boolean values
    int c_true = 1;  // true in C
    int c_false = 0; // false in C

    // In C++, we have a dedicated bool type
    bool cpp_true = true;  // true in C++
    bool cpp_false = false; // false in C++

    // Output the values
    std::cout << "C true: " << c_true << std::endl; // Outputs 1
    std::cout << "C false: " << c_false << std::endl; // Outputs 0

    std::cout << "C++ true: " << cpp_true << std::endl; // Outputs 1
    std::cout << "C++ false: " << cpp_false << std::endl; // Outputs 0

    // Demonstrating boolean expressions
    int a = 5, b = 10;

    // In C, we use integers for boolean expressions
    int c_result = (a < b); // true, so c_result is 1
    std::cout << "C result of (a < b): " << c_result << std::endl; // Outputs 1

    // In C++, we use bool for boolean expressions
    bool cpp_result = (a < b); // true, so cpp_result is true
    std::cout << "C++ result of (a < b): " << cpp_result << std::endl; // Outputs 1

    // Using std::boolalpha to print bool values as true/false
    std::cout << std::boolalpha; // Enable boolalpha

    std::cout << "C++ true with boolalpha: " << cpp_true << std::endl; // Outputs true
    std::cout << "C++ false with boolalpha: " << cpp_false << std::endl; // Outputs false

    // Resetting to default (1/0) representation
    std::cout << std::noboolalpha;

    std::cout << "C++ true without boolalpha: " << cpp_true << std::endl; // Outputs 1
    std::cout << "C++ false without boolalpha: " << cpp_false << std::endl; // Outputs 0

    return 0;
}