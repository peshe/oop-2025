#pragma once

#include "bird.h"

class Eagle : public Bird {
public:
  Eagle(const String &name) : Bird{name, 2.0} {}

  void makeSound() const override { std::cout << "screech!" << std::endl; }
  void move() const override { std::cout << "eagle glides" << std::endl; }

  void fly() const override { std::cout << "eagle flies" << std::endl; }
};