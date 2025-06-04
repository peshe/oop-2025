
#include <iostream>

#include "shapes/rectangle.h"
#include "shapes/square.h"
#include "shapes/circle.h"

// Това не можем да го направим (все още),
// защото се викат функциите на класа Shape,
// А не на децата.
// 
//void printShape(const Shape &r) {
//	std::cout << "-----------------\n";
//	std::cout << r.getName() << ":" << std::endl;
//	std::cout << "Area: " << r.area() << std::endl;
//	std::cout << "Perimeter: " << r.perimeter() << std::endl;
//}

void print(const Rectangle &r) {
	// Тук можем да подаваме и Square,
	// защтото не сме променяли поведението на функциите.
	// Обаче викат на Rectanle фунцкиите.
	std::cout << "-----------------\n";
	std::cout << r.getName() << ":" << std::endl;
	std::cout << "Area: " << r.area() << std::endl;
	std::cout << "Perimeter: " << r.perimeter() << std::endl;
}

void print(const Circle &r) {
	std::cout << "-----------------\n";
	std::cout << r.getName() << ":" << std::endl;
	std::cout << "Area: " << r.area() << std::endl;
	std::cout << "Perimeter: " << r.perimeter() << std::endl;
}

int main() {
	for (int i = 0; i < 1000; i++) {
		std::cout << "***************************\n";
		/*Rectangle r1(5, 6);
		print(r1);

		Square r2(5);
		print(r2);
		*/

		// Не освобождаваме паметта заделена от Circle,
		// защото се вика деструктора на Shape, а не на Circle
		Circle *r3 = new Circle(5);
		print(*r3);

		Shape *r4 = r3;
		delete r4;
	}
}

