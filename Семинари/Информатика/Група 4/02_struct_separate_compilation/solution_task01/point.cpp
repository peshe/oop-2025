#include "point.hpp"

#include <cmath>
#include <iostream>

void printPoint(const Point &point) {
    std::cout << "Point: " << point.x << " " << point.y << std::endl;
}

double getDistance(const Point &a, const Point &b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}
