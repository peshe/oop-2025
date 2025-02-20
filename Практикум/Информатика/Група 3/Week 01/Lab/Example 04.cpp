#include <iostream>



void samples();



void swap1(int  a, int  b);
void swap2(int* a, int* b);
void swap3(int& a, int& b);



void scenario1();
void scenario2();
void scenario3();



int main() {
    samples();

    scenario1();
    scenario2();
    scenario3();

    return 0;
}



void samples() {
    int a = 5;

    int& b =  a;
    int* c = &a;

    b = 10;

    std::cout << "A is: " <<  a << std::endl;
    std::cout << "B is: " <<  b << std::endl;
    std::cout << "C is: " << *c << std::endl;
}



void swap1(int a, int b) {
    int c = 0;

    c = a;
    a = b;
    b = c;
}

void swap2(int* a, int* b) {
    int c = 0;

     c = *a;
    *a = *b;
    *b =  c; 
}

void swap3(int& a, int& b) {
    int c = 0;

    c = a;
    a = b;
    b = c;
}



void scenario1() {
    int x = 0;
    int y = 0;

    std::cout << "Enter the number X: ";    std::cin >> x;
    std::cout << "Enter the number Y: ";    std::cin >> y;

    swap1(x, y);

    std::cout << "After the swap X is: " << x << std::endl;
    std::cout << "After the swap Y is: " << y << std::endl;
}

void scenario2() {
    int x = 0;
    int y = 0;

    std::cout << "Enter the number X: ";    std::cin >> x;
    std::cout << "Enter the number Y: ";    std::cin >> y;

    swap2(&x, &y);

    std::cout << "After the swap X is: " << x << std::endl;
    std::cout << "After the swap Y is: " << y << std::endl;
}

void scenario3() {
    int x = 0;
    int y = 0;

    std::cout << "Enter the number X: ";    std::cin >> x;
    std::cout << "Enter the number Y: ";    std::cin >> y;

    swap3(x, y);

    std::cout << "After the swap X is: " << x << std::endl;
    std::cout << "After the swap Y is: " << y << std::endl;
}
