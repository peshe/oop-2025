#pragma once

#include "shape.h"

class Polygon : public Shape {
private:
	unsigned numSides;

public:
	Polygon(unsigned numSides);
	virtual ~Polygon() = default;

	unsigned getNumSides() const;
};

