#pragma once

#include "mammal.h"

class Dog : public Mammal {
public:
  Dog(const String &name) : Mammal{name, 63} {}

  void makeSound() const override { std::cout << "woof!" << std::endl; }
  void move() const override { std::cout << "dog runs" << std::endl; }
};