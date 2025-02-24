#include <iostream> // Include the C++ standard input-output stream library
#include <cstdio>   // Include the C standard input-output library

/**
 * C++ I/O:
 * - `std::cout` is used for output. It is an instance of the `ostream` class and is part of the C++ Standard Library.
 * - `std::cin` is used for input. It is an instance of the `istream` class and is part of the C++ Standard Library.
 * - `std::endl` is used to insert a newline character and flush the stream.
 * - `std::cout` and `std::cin` are type-safe and support operator overloading, which allows for a more intuitive syntax.
 * - C++ streams handle different data types automatically, reducing the risk of errors.
 * - C++ I/O operations can be easily extended by overloading the `<<` and `>>` operators for user-defined types.
 * 
 * C I/O:
 * - `printf` is used for output. It is a function from the C Standard Library.
 * - `scanf` is used for input. It is a function from the C Standard Library.
 * - `printf` and `scanf` use format specifiers to determine the type of data being processed.
 * - C I/O functions are not type-safe and require explicit format specifiers, which can lead to errors if not used correctly.
 * - C I/O functions are generally faster than C++ streams because they are less complex and do not perform type checking.
 * - C I/O functions are more suitable for low-level programming where performance is critical.
 * 
 * 
 * 
 * If you want to only use C++ features, you can use `std::ios_base::sync_with_stdio(false);` to disable synchronization between C and C++ streams, which can improve performance.
 */
int main() {
    // C++ I/O
    std::cout << "Hello, C++ World!" << std::endl; // Output a string followed by a newline using C++ stream
    std::cout << "Enter a number: "; // Prompt the user to enter a number using C++ stream

    int num = 0;

    std::cin >> num; // Read an integer from the user using C++ stream
    std::cout << "You entered: " << num << std::endl; // Output the entered number using C++ stream

    // C I/O
    printf("Hello, C World!\n"); // Output a string followed by a newline using C function
    printf("Enter a number: "); // Prompt the user to enter a number using C function

    int c_num = 0;
    
    scanf("%d", &c_num); // Read an integer from the user using C function
    printf("You entered: %d\n", c_num); // Output the entered number using C function

    return 0;
}