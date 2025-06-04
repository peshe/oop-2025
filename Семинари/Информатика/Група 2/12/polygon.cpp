#include "polygon.h"

Polygon::Polygon(unsigned numSides)
	: numSides(numSides), Shape("Polygon")
{}

unsigned Polygon::getNumSides() const {
	return this->numSides;
}
