#include "person.hpp"

#include <cstring>
#include <iostream>

static const unsigned int MAX_NAME_LEN{100};

Person::Person() {
  std::cout << "Creating person using input from stdin..." << std::endl;
  read();
}

Person::Person(const char *name, unsigned int age) : name{nullptr} {
  std::cout << "Creating person using name and age..." << std::endl;
  assign(name, age);
}

// Person::Person(const Person &other) {
//   std::cout << "Creating person using other person..." << std::endl;
//   assign(other.name, other.age);
// }

Person::Person(const Person &other) : Person{other.name, other.age} {
  std::cout << "Creating person using another person..." << std::endl;
}

Person &Person::operator=(const Person &other) {
  if (&other != this) {
    std::cout << "Assigning person to another person..." << std::endl;
    assign(other.name, other.age);
  } else {
    std::cout << "Refusing to assign person to same person instance."
              << std::endl;
  }
  return *this;
}

Person::~Person() {
  std::cout << "Destroying person..." << std::endl;
  destroy();
}

const char *Person::getName() const { return this->name; }

void Person::setName(const char *name) {
  if (name == nullptr) {
    throw "person name is null";
  }
  if (*name == '\0') {
    throw "person name is empty";
  }
  for (const char *c{name}; *c; c++) {
    if (!(*c >= 'A' && *c <= 'Z' || *c >= 'a' && *c <= 'z' || *c == '-' ||
          *c == ' '))
      throw "person name contains a non-alphabetic character which is not a "
            "hyphen or a space";
  }

  if (this->name)
    destroyName();
  copyName(name);
}

void Person::printName() const {
  std::cout << "Person name: " << getName() << std::endl;
}

void Person::readName() {
  std::cout << "Enter person name: ";
  char name[MAX_NAME_LEN];
  std::cin.getline(name, MAX_NAME_LEN);
  // check if input was too long for the `name` member variable (>
  // MAX_NAME_LEN), or if some other (system-related) issue occurred with the
  // input
  if (std::cin.fail())
    throw "failed to read person name from stdin";

  // use the setter for the `name` member variable
  setName(name);
}

unsigned int Person::getAge() const { return this->age; }

void Person::setAge(unsigned int age) {
  // no need to validate `age` because all non-negative integers are valid ages
  this->age = age;
}

void Person::printAge() const {
  std::cout << "Person age: " << getAge() << std::endl;
}

void Person::readAge() {
  std::cout << "Enter person age: ";
  // use `int` as the type in order to be able to verify whether a negative
  // number was entered if `unsigned int` is used as the type here and a
  // negative number is entered, its two's complement representation would be
  // interpreted as an unsigned (positive) value, and the `age < 0` check
  // wouldn't discard it
  int age;
  std::cin >> age;
  // check if input was not a valid integer, or if some other (system-related)
  // issue occurred with the input
  if (std::cin.fail())
    throw "failed to read person age from stdin";
  // check if input was negative
  if (age < 0)
    throw "person age is negative";

  // use the setter for the `age` member variable
  setAge(age);
}

void Person::assign(const char *name, unsigned int age) {
  setName(name);
  setAge(age);
}

void Person::print() const {
  printName();
  printAge();
}

void Person::read() {
  readName();
  readAge();
}

void Person::copyName(const char *name) {
  auto size{strlen(name) + 1};
  // allocate enough memory for the new name
  this->name = new char[size];
  // copy the `name` argument into the member variable of the same name
  strncpy(this->name, name, size);
}

void Person::destroyName() { delete[] name; }

void Person::copy(const Person &other) {
  copyName(other.name);
  this->age = other.age;
}

void Person::destroy() { destroyName(); }
