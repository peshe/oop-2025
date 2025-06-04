#pragma once

#include "shape.h"

class Rectangle : public Shape {
private:
	double a, b;

public:
	Rectangle(double a, double b);
	Rectangle(const Rectangle &o);
	~Rectangle();

	Rectangle &operator=(const Rectangle& o);

	double perimeter() const;
	double area() const;
};
