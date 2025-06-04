#pragma once
#include "shape.h"

//#include <cmath>

class Circle : public Shape {
private:
	static const double PI;
	double *r = nullptr; // Да тъпо е, ама за демострация

public:
	Circle(double r);
	Circle(const Circle &o);
	virtual ~Circle();

	Circle& operator=(const Circle& o);

	virtual double perimeter() const override;
	virtual double area() const override;
};

