#pragma once

#include "animal.h"

class Bird : public Animal {
protected:
  double wingSpan;

public:
  Bird(const String &name, double wingSpan)
      : Animal{name}, wingSpan{wingSpan} {}

  double getWingSpan() const { return wingSpan; }

  virtual void fly() const = 0;
};