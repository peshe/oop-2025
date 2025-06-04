#pragma once
#include "polygon.h"
#include "rectangle.h"

class Square : public Rectangle, public Polygon {
public:
	Square(double a);
	virtual ~Square() = default;
};
