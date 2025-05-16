#pragma once

#include "bird.h"

class Penguin : public Bird {
public:
  Penguin(const String &name) : Bird{name, 0.5} {}

  void makeSound() const override { std::cout << "honk!" << std::endl; }
  void move() const override { std::cout << "penguin waddles" << std::endl; }

  void fly() const override { throw "penguins can't fly!"; }
};