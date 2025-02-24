#include <iostream>
#include <iomanip>

/* Function overloading
    - Function overloading allows you to have multiple functions with the same name in the same scope,
        as long as their parameter lists (signatures) are different.
    
    - This lets you perform similar operations on different types or numbers of arguments without having to use different function names.
    
    - Overloaded functions must differ in the number or types of parameters.
        Return type alone cannot distinguish overloaded functions.
    
    - The compiler determines which function to call based on the arguments provided.
        This is resolved at compile time.
*/

/* Function Default Parameters
    - Default parameters allow you to specify default values for function parameters in the function declaration.
    
    - If the caller omits those arguments, the default values are used.
    
    - Default parameter values are typically provided in the function declaration
        (or in the definition if no separate declaration is used). If both declaration and definition are provided,
        the default values should appear only once.
    
    - Left-to-right rule: Once a parameter is given a default value,
        all subsequent parameters in the parameter list must also have default values.

*/

void print(int number);
void print(double number, int precision = 2); // If the caller does not provide a value for the precision parameter, it will default to 2.
void print(std::string text);

int main() {
    print(5);
    print(3.14159); // Here, the default precision of 2 will be used
    print(3.14159, 3);
    print("Hello, World!");

    return 0;
}

void print(int number) {
    std::cout << "Printing integer: " << number << std::endl;
}

void print(double number, int precision) {
    std::cout << "Printing double: " << std::fixed << std::setprecision(precision) << number << std::endl;
}

void print(std::string text) {
    std::cout << "Printing string: " << text << std::endl;
}
