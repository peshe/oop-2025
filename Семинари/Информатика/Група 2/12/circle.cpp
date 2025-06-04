#include "circle.h"

#include <iostream>

const double Circle::PI = 3.1415;

Circle::Circle(double r) 
	: Shape("Circle")
{
	this->r = new double;
	*this->r = r;
}

Circle::Circle(const Circle &o)
	: Shape(o)
{
	this->r = new double;
	*this->r = *o.r;
}

Circle::~Circle() {
	delete this->r;
	std::cout << "Circle ~dtor()" << std::endl;
}

Circle &Circle::operator=(const Circle &o) {
	*this->r = *o.r;
	Shape::operator=(o);

	return *this;
}

double Circle::perimeter() const {
	return 2 * Circle::PI * *this->r;
}

double Circle::area() const {
	return Circle::PI * *this->r * *this->r;
}