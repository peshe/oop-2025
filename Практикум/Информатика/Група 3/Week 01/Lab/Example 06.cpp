#include <iostream>



enum Color {
    RED,    // 0
    BLACK,  // 1
    WHITE,  // 2
};

enum Card {
    RED_CARD    = 3,
    BLACK_CARD  = 2,
    WHITE_CARD  = 1,
};

// warning: comma at end of enumerator list [-Wpedantic]



const char* colors[3] = { "RED", "BLACK", "WHITE" };



int main() {
    std::cout << "Color Values: "       << std::endl;
    std::cout << "RED   : " << RED      << std::endl;
    std::cout << "BLACK : " << BLACK    << std::endl;
    std::cout << "WHITE : " << WHITE    << std::endl;

    std::cout << "Card Values: "                << std::endl;
    std::cout << "RED   CARD: " << RED_CARD     << std::endl;
    std::cout << "BLACK CARD: " << BLACK_CARD   << std::endl;
    std::cout << "WHITE CARD: " << WHITE_CARD   << std::endl;


    Color redColor      =   Color::RED  ;
    Color blackColor    =   Color::BLACK;
    Color whiteColor    =   Color::WHITE;


    if (redColor == Color::RED) {
        std::cout << "We are RED!" << std::endl;
    }

    if (blackColor != Color::WHITE) {
        std::cout << "We are BLACK!" << std::endl;
    }

    if (whiteColor != Color::BLACK) {
        std::cout << "We are WHITE!" << std::endl;
    }


    Color color = static_cast<Color>(1);

    std::cout << "Dummy Color: " << color << std::endl;
    
    // std::cin >> color;

    std::cout << "Color Name: " << colors[color] << std::endl;


    return 0;
}
