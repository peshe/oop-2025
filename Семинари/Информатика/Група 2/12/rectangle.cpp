#include "rectangle.h"

#include <iostream>

Rectangle::Rectangle(double a, double b) 
	: a(a), b(b), Shape("Rectangle")
{}

Rectangle::Rectangle(const Rectangle &o)
	: a(o.a), b(o.b), Shape(o)
{}

Rectangle::~Rectangle() {
	std::cout << "Rectangle ~dtor()" << std::endl;
}

Rectangle &Rectangle::operator=(const Rectangle &o) {
	this->a = o.a;
	this->b = o.b;
	Shape::operator=(o);

	return *this;
}

Rectangle &Rectangle::operator=(const Square &o) {
	this->a = o.a;
	this->b = o.b;
	this->setName("Rectangle");

	return *this;
}

double Rectangle::perimeter() const {
	return 2 * (this->a + this->b);
}

double Rectangle::area() const {
	return this->a * this->b;
}

void Rectangle::print() const {
	for (int i = 0; i < this->a; i++) {
		for (int j = 0; j < this->b; j++) {
			std::cout << "$";
		}
		std::cout << std::endl;
	}
}
