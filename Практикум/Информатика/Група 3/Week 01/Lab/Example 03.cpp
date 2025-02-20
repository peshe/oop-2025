#include <iostream>



int main() {
    bool condition1 = true  ;
    bool condition2 = false ;

    std::cout << "Condition 1: " << condition1 << std::endl;
    std::cout << "Condition 2: " << condition2 << std::endl;

    std::cout << std::boolalpha << "Condition 1: " << condition1 << std::endl;
    std::cout << std::boolalpha << "Condition 2: " << condition2 << std::endl;

    return 0;
}
