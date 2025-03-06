#include <iostream>



void print(const int&           );
void print(const double&        );
void print(const std::string&   );



int sum(int a = 1,  int b = 2,  int c = 3);



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



void print(const int& number) {
    std::cout << "Integer number: " << number << std::endl;
}

void print(const double& number) {
    std::cout << "Double number: " << number << std::endl;
}

void print(const std::string& number) {
    std::cout << "String number: " << number << std::endl;
}



int sum(int a, int b, int c) {
    return a + b + c;
}
