#include "person.hpp"

class Family {
  Person mother, father;
  Person *child1{nullptr};
  Person *child2{nullptr};

public:
  Family(const Person &mother, const Person &father);
  Family(const Family &) = delete;
  Family &operator=(const Family &) = delete;
  ~Family();

  const Person &getMother() const { return mother; }
  const Person &getFather() const { return father; }
  const Person *getFirstChild() const { return child1; }
  const Person *getSecondChild() const { return child2; }

  const Person *getGrandmother() const { return mother.mother; }
  const Person *getGrandfather() const { return mother.father; }

  void addChild(const Person &child);
};