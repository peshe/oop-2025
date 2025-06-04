#pragma once

#include "shape.h"

class Polygon : public virtual Shape {
private:
	unsigned numSides;

public:
	Polygon(unsigned numSides);
	virtual ~Polygon() = default;

	unsigned getNumSides() const;
};

