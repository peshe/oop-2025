#include <limits>

#include <iostream>



int readNumber();



int main() {
    const int number1   =   readNumber();
    const int number2   =   readNumber();
    const int number3   =   readNumber();

    const int minNumber =   (number1 < number2) ? (number1 < number3 ? number1 : number3) : (number2 < number3 ? number2 : number3);
    const int maxNumber =   (number1 > number2) ? (number1 > number3 ? number1 : number3) : (number2 > number3 ? number2 : number3);
    const int avgNumber =   (number1 + number2 + number3) - (minNumber + maxNumber);

    std::cout << "Min Number is: " << minNumber << std::endl;
    std::cout << "Max Number is: " << maxNumber << std::endl;
    std::cout << "Avg Number is: " << avgNumber << std::endl;
    

    return 0;
}



int readNumber() {
    int number = 0;

    while (true) {
        std::cout << "Enter the number: ";

        std::cin >> number;

        if (std::cin.fail()) {
            std::cin.clear  ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
            
            return number;
        }
    }
}
