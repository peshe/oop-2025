
#include <iostream>

#include "my_string.h"

class Animal {
protected:
	MyString name;

public:
	Animal() : name("Unnamed") {}
	Animal(const char *name) : name(name) {}

	void walk() {
		std::cout << name << " is walking." << std::endl;
	}

	void sayHello() {
		std::cout << name << " say hello" << std::endl;
	}
};

class Cat : public Animal {
private:
	int hunger;
	int name;

public:
	Cat(const char *name) : Animal(name), hunger(100) {
		std::cout << "Cat ctor " << std::endl;
		this->name = 11;
		std::cout << Animal::name << " " << std::endl;
		std::cout << this->name << std::endl;
	}

	void sayHello() {
		std::cout << "Meow ";
		Animal::sayHello();
	}

	void catchMouse() {
		std::cout << "Murzi me" << std::endl;
	}
};

class Siamese : public Cat {
private:

public:
	Siamese(const char *name) : Cat(name) {}

	void sayHello() = delete;
};

