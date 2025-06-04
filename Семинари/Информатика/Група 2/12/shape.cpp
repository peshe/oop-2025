#include "shape.h"

#include <cstring>

#include "not_implemented_exception.h"

#include <iostream>

Shape::Shape(const char* name) {
	this->setName(name);
}

void Shape::setName(const char *name) {
	if (this->name) {
		delete[] this->name;
	}

	int len = strlen(name);
	this->name = new char[len + 1];
	strcpy_s(this->name, len + 1, name);
}

Shape::Shape(const Shape &o) : Shape(o.name) {}

Shape::~Shape() {
	delete[] this->name;
	std::cout << "Shape ~dtor()" << std::endl;
}

Shape &Shape::operator=(const Shape &o) {
	this->setName(o.name);

	return *this;
}

const char *Shape::getName() const {
	return this->name;
}
