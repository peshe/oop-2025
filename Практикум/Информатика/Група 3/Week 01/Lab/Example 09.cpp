#include <iostream>



void print(int          number);
void print(double       number);
void print(std::string  number);



int sum(int a = 2,  int b = 2,  int c = 2);



int main() {
    print(13);
    print(7.9);
    print("1379");


    std::cout << "Sum 1 is: " << sum(1, 2, 3)   << std::endl;
    std::cout << "Sum 2 is: " << sum(1, 2   )   << std::endl;
    std::cout << "Sum 3 is: " << sum(1      )   << std::endl;
    std::cout << "Sum 4 is: " << sum(       )   << std::endl;


    return 0;
}



void print(int number) {
    std::cout << "Integer number: " << number << std::endl;
}

void print(double number) {
    std::cout << "Double number: " << number << std::endl;
}

void print(std::string number) {
    std::cout << "String number: " << number << std::endl;
}



int sum(int a, int b, int c) {
    return a + b + c;
}
