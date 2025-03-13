#include <iostream>



enum class Day {
    Saturday,   // 0
    Sunday  ,   // 1
};

enum class Color : char {
    RED     =   'r',
    GREEN   =   'g',
    BLUE    =   'b',
};

/*

enum SimpleColor {
    RED     ,
    GREEN   ,
    BLUE    ,
};

enum SpecialColor {
    RED     ,
    BLACK   ,
    WHITE   ,
};

*/



int main() {
    // Color color  =   RED     ;   Error!
    // Color color  =   GREEN   ;   Error!
    // Color color  =   BLUE    ;   Error!

    
    Color color = Color::RED;

    // std::cout << "RED Value is: " << RED << std::endl;

    if (color == Color::RED) {
        std::cout << "Hello, World!" << std::endl;
    }


    // Day day =    0;  Error!
    // Day day =    1;  Error!
    
    Day day = static_cast<Day>(1);

    // std::cout << day;    Error!

    std::cout << static_cast<int>(day) << std::endl;


    return 0;
}
