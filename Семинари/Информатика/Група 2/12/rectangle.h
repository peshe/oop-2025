#pragma once

#include "i_printable.h"
#include "shape.h"


class Square;

class Rectangle : public Shape, public IPrintable {
private:
	double a, b;

public:
	Rectangle(double a, double b);
	Rectangle(const Rectangle &o);
	virtual ~Rectangle();

	Rectangle &operator=(const Rectangle &o);
	Rectangle &operator=(const Square &o);

	virtual double perimeter() const override;
	virtual double area() const override;

	virtual void print() const override;
};

#include "square.h"
