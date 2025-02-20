#include <iostream>



enum class Day {
    Saturday,
    Sunday  ,
};

enum class Color : char {
    RED     =   'r',
    GREEN   =   'g',
    BLUE    =   'b',
};



int main() {
    // Color color  =   RED     ;   Error!
    // Color color  =   GREEN   ;   Error!
    // Color color  =   BLUE    ;   Error!

    
    Color color = Color::RED;

    if (color == Color::RED) {
        std::cout << "Hello, World!" << std::endl;
    }


    // Day day =    0;  Error!
    // Day day =    1;  Error!
    
    Day day = (Day)(1);

    // std::cout << day;    Error!

    std::cout << (int)(day) << std::endl;


    return 0;
}
