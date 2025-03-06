#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "point.hpp"

struct Triangle {
    Point p1;
    Point p2;
    Point p3;
};

void printTriangle(const Triangle &tri);

double getPerimeter(const Triangle &triangle);

double getArea(const Triangle &triangle);


#endif //TRIANGLE_HPP
