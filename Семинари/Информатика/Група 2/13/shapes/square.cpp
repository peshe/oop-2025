#include "square.h"

Square::Square(double a) 
	: Shape("Square"), Rectangle(a, a), Polygon(4) 
{}