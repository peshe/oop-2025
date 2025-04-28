#include "family.hpp"

Family::Family(const Person &mother, const Person &father)
    : mother{mother}, father{father} {}

Family::~Family() {
  delete child1;
  delete child2;
}

void Family::addChild(const Person &child) {
  if (child1 == nullptr) {
    child1 = new Person{child};
  } else if (child2 == nullptr) {
    child2 = new Person{child};
  } else {
    throw "too many children";
  }
}
