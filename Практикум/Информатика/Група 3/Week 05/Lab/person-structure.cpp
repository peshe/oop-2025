#include <cstring>
#include <iostream>

const unsigned int MAX_NAME_LEN{100};

struct Person {
  char name[MAX_NAME_LEN];
  unsigned int age;
};

const char *getPersonName(const Person &p) {
  // setPersonName(p, "Ivan Ivanov"); // won't compile, thus preventing us from
  // modifying the object through an immutable reference
  return p.name;
}

void setPersonName(Person &p, const char *name) {
  strncpy(p.name, name, MAX_NAME_LEN);
}

void printPersonName(const Person &p) {
  // setPersonName(p, "Peter Petrov"); // won't compile, thus preventing us from
  // modifying the object through an immutable reference
  std::cout << "Person name: " << getPersonName(p) << std::endl;
}

void readPersonName(Person &p) {
  std::cout << "Enter person name: ";
  std::cin.getline(p.name, MAX_NAME_LEN);
}

unsigned int getPersonAge(const Person &p) {
  // setPersonAge(p, 42); // won't compile, thus preventing us from modifying
  // the object through an immutable reference
  return p.age;
}

void setPersonAge(Person &p, unsigned int age) { p.age = age; }

void printPersonAge(const Person &p) {
  std::cout << "Person age: " << getPersonAge(p) << std::endl;
  // setPersonAge(p, 42); // won't compile, thus preventing us from modifying
  // the object through an immutable reference
}

void readPersonAge(Person &p) {
  std::cout << "Enter person age: ";
  std::cin >> p.age;
}

void assignPerson(Person &p, const char *name, unsigned int age) {
  setPersonName(p, name);
  setPersonAge(p, age);
}

void readPerson(Person &p) {
  readPersonName(p);
  readPersonAge(p);
}

void printPerson(const Person &p) {
  printPersonName(p);
  printPersonAge(p);
}

int main() {
  Person p;

  readPersonAge(p);
  std::cin.ignore();
  readPersonName(p);

  printPersonAge(p);
  printPersonName(p);

  setPersonName(p, "John Doe");
  printPersonName(p);

  setPersonAge(p, 32);
  printPersonAge(p);

  assignPerson(p, "Jane Doe", 33);
  printPerson(p);

  readPerson(p);
  printPerson(p);

  return 0;
}
