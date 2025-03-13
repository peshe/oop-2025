#include <iostream>



inline bool isDigit(const char& letter) { return letter >= '0' && letter <= '9';    }
inline bool isLower(const char& letter) { return letter >= 'a' && letter <= 'z';    }
inline bool isUpper(const char& letter) { return letter >= 'A' && letter <= 'Z';    }



inline int operation1(const int& number)    { return number + 1;    }
inline int operation2(const int& number)    { return number + 3;    }
inline int operation3(const int& number)    { return number + 7;    }
inline int operation4(const int& number)    { return number + 9;    }



inline void showLove()  { std::cout << "Teo LOVES Jess" << std::endl;   }   // Inline Without Effect!
inline void showHate()  { std::cout << "John HATES Teo" << std::endl;   }   // Inline Without Effect!



int main() {
    char letter = '\0';

    std::cout << "Enter the letter: ";

    std::cin >> letter;

    if (isDigit(letter)) {
        std::cout << "The letter is digit!" << std::endl;
    } else if (isLower(letter)) {
        std::cout << "The letter is lower!" << std::endl;
    } else if (isUpper(letter)) {
        std::cout << "The letter is upper!" << std::endl;
    } else {
        std::cout << "The letter is other!" << std::endl;
    }


    int number1 = operation1(666);
    int number2 = operation2(666);
    int number3 = operation3(666);
    int number4 = operation4(666);

    std::cout << "Number 1 is: " << number1 << std::endl;
    std::cout << "Number 2 is: " << number2 << std::endl;
    std::cout << "Number 3 is: " << number3 << std::endl;
    std::cout << "Number 4 is: " << number4 << std::endl;


    showLove();
    showHate();


    return 0;
}



// https://www.geeksforgeeks.org/inline-functions-cpp/
