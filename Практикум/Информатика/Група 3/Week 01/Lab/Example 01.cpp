#include <iostream>



/**
 * C++ Input Output
 *  - `std::cout`:  Used for output.    It is part of the C++ Standard Library.     Instance of the `ostream` class.
 *  - `std::cin` :  Used for input.     It is part of the C++ Standard Library.     Instance of the `istream` class.
 *  - `std::endl`:  Used for inserting a newline character and flush the stream.
 *  - `std::cout` and `std::cin` are type-safe.
 * C++ streams handle different data types automatically, reducing the risk of errors.
 * 
 * C Input Output
 *  - `printf`  :   Used for output.    It is part of the C Standard Library.       It is a function.
 *  - `scanf`   :   Used for input.     It is part of the C Standard Library.       It is a function.
 *  - `printf` and `scanf` use format specifiers to determine the type of data being processed.
 *  C I/O functions are not type-safe and require explicit format specifiers, which can lead to errors if not used correctly.
 *  C I/O functions are generally faster than C++ streams because they are less complex and do ot perform type checking.
 *  C I/O functions are more suitable for low-level programming where performance is critical.
 */



int main() {
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
