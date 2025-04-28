#include "family.hpp"

const Person *getGreatGrandmother(const Person &p) {
  if (p.mother == nullptr)
    return nullptr;

  if (p.mother->mother == nullptr)
    return nullptr;

  return p.mother->mother->mother;
}

int main() {
  // Person p;

  // std::cout << "Species of person: " << Person::species << std::endl;
  // std::cout << "Number of people: " << Person::getNumberOfPeople() <<
  // std::endl;

  Person adam{"Adam", 99999};
  adam.print();

  Person eve{"Eve", 99999};
  eve.print();

  Person abel{"Abel", 99900, &eve, &adam};
  abel.print();

  Person cain{"Cain", 99800, &eve, &adam};
  cain.print();

  std::cout << "Family:" << std::endl;

  Family f{eve, adam};
  f.addChild(abel);
  f.addChild(cain);

  f.getMother().print();
  f.getFather().print();

  const Person *firstChild{f.getFirstChild()};
  if (firstChild)
    firstChild->print();
  const Person *secondChild{f.getSecondChild()};
  if (secondChild)
    secondChild->print();

  const Person *grandmother{f.getGrandmother()};
  if (grandmother)
    grandmother->print();

  const Person *grandfather{f.getGrandmother()};
  if (grandfather)
    grandfather->print();

  const Person *greatGrandmother{getGreatGrandmother(abel)};
  if (greatGrandmother)
    greatGrandmother->print();

  return 0;
}