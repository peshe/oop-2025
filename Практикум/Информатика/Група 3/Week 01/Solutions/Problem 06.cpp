#include <limits>

#include <cassert>

#include <iostream>



int     inputSide1();
double  inputSide2();



int findPerimeter   (int a, int b);
int findArea        (int a, int b);



double findPerimeter(double a, double b);
double findArea     (double a, double b);



int main() {
    int side11 = inputSide1();
    int side12 = inputSide1();

    int perimeter1  =   findPerimeter   (side11, side12);
    int area1       =   findArea        (side11, side12);

    std::cout << "The PERIMETER of the rectangle is: "  << perimeter1   << std::endl;
    std::cout << "The AREA      of the rectangle is: "  << area1        << std::endl;
    

    double side21 = inputSide2();
    double side22 = inputSide2();

    double perimeter2   =   findPerimeter   (side21, side22);
    double area2        =   findArea        (side21, side22);

    std::cout << "The PERIMETER of the rectangle is: "  << perimeter2   << std::endl;
    std::cout << "The AREA      of the rectangle is: "  << area2        << std::endl;


    return 0;
}



int inputSide1() {
    int side = 0;

    while (true) {
        std::cout << "Enter the side of the rectangle: ";

        std::cin >> side;

        if (std::cin.fail()) {
            std::cin.clear  ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            if (side <= 0) {
                continue;
            } else {
                return side;
            }
        }
    }
}

double inputSide2() {
    double side = 0.0;

    while (true) {
        std::cout << "Enter the side of the rectangle: ";

        std::cin >> side;

        if (std::cin.fail()) {
            std::cin.clear  ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            if (side <= 0.0) {
                continue;
            } else {
                return side;
            }
        }
    }
}



int findPerimeter(int a, int b) {
    assert(a > 0);
    assert(b > 0);

    return 2 * (a + b);
}

int findArea(int a, int b) {
    assert(a > 0);
    assert(b > 0);

    return a * b;
}



double findPerimeter(double a, double b) {
    assert(a > 0);
    assert(b > 0);

    return 2 * (a + b);
}

double findArea(double a, double b) {
    assert(a > 0);
    assert(b > 0);

    return a * b;
}
