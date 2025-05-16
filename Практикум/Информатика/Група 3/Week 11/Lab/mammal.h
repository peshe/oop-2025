#pragma once

#include "animal.h"

class Mammal : public Animal {
protected:
  int gestationDays;

public:
  Mammal(const String &name, int gestationDays)
      : Animal{name}, gestationDays{gestationDays} {}

  int getGestationDays() const { return gestationDays; }
};