#pragma once

#include <iostream>

#include "string.h"

class Animal {
protected:
  String name;

public:
  Animal(const String &name) : name{name} {}
  virtual ~Animal() {}

  virtual void makeSound() const = 0;
  virtual void move() const = 0;

  void eat() const {
    std::cout << name.getData() << " is eating." << std::endl;
  }

  void breathe() const {
    std::cout << name.getData() << " is breathing." << std::endl;
  }

  const String &getName() const { return name; }
};