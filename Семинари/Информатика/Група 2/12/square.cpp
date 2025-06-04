#include "square.h"

Square::Square(double a) : Rectangle(a, a), Polygon(4) {
	Shape::setName("Square");
}