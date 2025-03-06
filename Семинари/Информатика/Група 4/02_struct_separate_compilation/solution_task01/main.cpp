#include <iostream>
#include "triangle.hpp"

int main() {
    Triangle triangle;
    triangle.p1 = Point{0, 0};
    triangle.p2 = Point{1, 5};
    triangle.p3 = Point{3, 4};

    const double perimeter = getPerimeter(triangle);
    const double area = getArea(triangle);
    std::cout << "Perimeter: " << perimeter << std::endl;
    std::cout << "Area: " << area << std::endl;

    return 0;
}
