#pragma once

#include "mammal.h"

class Bat : public Mammal {
public:
  Bat(const String &name) : Mammal{name, 60} {}

  void makeSound() const override { std::cout << "screech!" << std::endl; }
  void move() const override { std::cout << "bat flies" << std::endl; }
};