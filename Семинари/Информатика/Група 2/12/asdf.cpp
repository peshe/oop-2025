#include <iostream>

#include "shapes/rectangle.h"
#include "shapes/square.h"
#include "shapes/circle.h"

void print(const Shape &r) {
	std::cout << "-----------------\n";
	std::cout << r.getName() << ":" << std::endl;
	std::cout << "Area: " << r.area() << std::endl;
	std::cout << "Perimeter: " << r.perimeter() << std::endl;
}

void printCircle(const Circle &r) {
	std::cout << "----CIRCLE-------\n";
	std::cout << r.getName() << ":" << std::endl;
	std::cout << "Area: " << r.area() << std::endl;
	std::cout << "Perimeter: " << r.perimeter() << std::endl;
}

// Компилатора се сърди, защото имаме диамантен проблем.
// Следващия път ще видим как да го решим
// Сега за да тръгне, трябва да изтриете нещата с Polygon

int main() {
	Shape **shapes = new Shape*[5];
	shapes[0] = new Circle(15);
	shapes[1] = new Rectangle(15, 2);
	shapes[2] = new Square(3);
	shapes[3] = new Circle(1);
	shapes[4] = new Square(9);

	for (int i = 0; i < 5; i++) {
		print(*shapes[i]);
	}

	std::cout << std::endl;
	Circle *zerothShape = dynamic_cast<Circle *>(shapes[0]);
	if (zerothShape != nullptr) {
		printCircle(*zerothShape);
	} else {
		std::cout << "0th shape is not a Circle" << std::endl;
	}
	std::cout << std::endl;

	Rectangle r(100, 1);
	// Тва е unsafe...
	r = *dynamic_cast<Square*>(shapes[2]);

	print(r);

	IPrintable* blq = dynamic_cast<IPrintable*>(shapes[2]);
	if (blq != nullptr) {
		blq->print();
	}
	else {
		std::cout << "can't print blq" << std::endl;
	}

	for (int i = 0; i < 5; i++) {
		delete shapes[i];
	}
	delete[] shapes;
}