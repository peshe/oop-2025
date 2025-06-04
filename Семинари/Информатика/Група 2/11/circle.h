#pragma once
#include "shape.h"

#include <cmath>

class Circle : public Shape {
private:
	static const double PI;
	double *r = nullptr; // Да тъпо е, ама за демострация

public:
	Circle(double r);
	Circle(const Circle &o);
	~Circle();

	Circle& operator=(const Circle& o);

	double perimeter() const;
	double area() const;
};
