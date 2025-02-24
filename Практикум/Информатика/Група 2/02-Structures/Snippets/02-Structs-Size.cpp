#include <iostream>

/* Struct size
    * Typically, the size of a struct is the sum of the size of all its members, but not always!
    
    * We can only say that the size of a struct will be at least as large as the size of all the variables it contains. 
    * But it could be larger!
    * For performance reasons, the compiler will sometimes add gaps into structures (this is called padding).
    * 
    * Padding is used to align the members of a struct to improve memory access performance.
    * You can minimize padding by defining your members in decreasing order of size.
    * 
    * You can read more here: https://en.wikipedia.org/wiki/Data_structure_alignment
*/


struct Foo {
    short a{};
    int b{};
    double c{};
};

struct BigFoo {
    short a{}; // will have 2 bytes of padding after a
    int b{};
    short c{}; // will have 2 bytes of padding after c
};

struct SmallFoo {
    int b{};
    short a{};
    short c{};
};

int main() {
    std::cout << "The size of short is " << sizeof(short) << " bytes\n"; // 2 bytes
    std::cout << "The size of int is " << sizeof(int) << " bytes\n"; // 4 bytes
    std::cout << "The size of double is " << sizeof(double) << " bytes\n"; // 8 bytes

    std::cout << "The size of Foo is " << sizeof(Foo) << " bytes\n"; // 16 bytes

    std::cout << "---------------------------------" << std::endl;

    std::cout << "The size of BigFoo is " << sizeof(BigFoo) << " bytes\n"; // 12 bytes
    std::cout << "The size of SmallFoo is " << sizeof(SmallFoo) << " bytes\n"; // 8 bytes

    return 0;
}
