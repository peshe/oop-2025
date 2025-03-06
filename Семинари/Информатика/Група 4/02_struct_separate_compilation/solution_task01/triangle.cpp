#include "triangle.hpp"
#include <iostream>

void printTriangle(const Triangle &tri) {
    std::cout << "Triangle with points:" << std::endl;
    printPoint(tri.p1);
    printPoint(tri.p2);
    printPoint(tri.p3);
}

double getPerimeter(const Triangle &triangle) {
    const double a = getDistance(triangle.p1, triangle.p2);
    const double b = getDistance(triangle.p2, triangle.p3);
    const double c = getDistance(triangle.p3, triangle.p1);

    return a + b + c;
}

double getArea(const Triangle &triangle) {
    return 0.5 * std::abs(
               triangle.p1.x * (triangle.p2.y - triangle.p3.y) + triangle.p2.x * (triangle.p3.y - triangle.p1.y) +
               triangle.p3.x * (triangle.p1.y - triangle.p2.y));
}
