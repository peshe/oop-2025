#ifndef POINT_HPP
#define POINT_HPP

struct Point {
    double x;
    double y;
};

void printPoint(const Point &point);

double getDistance(const Point &a, const Point &b);

#endif //POINT_HPP
