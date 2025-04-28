#include <cstring>
#include <iostream>

// TODO: split class definition into header file and only leave method
// implementations in this file

const unsigned int MAX_NAME_LEN{100};

class Person {
  // we have an abstraction of a person with the following two characteristics
  char name[MAX_NAME_LEN]; // private (hidden) member
  unsigned int age;        // private (hidden) member
  // member variables (fields) are usually supposed to be accessed through
  // accessors (getters and setters) - in these cases, they are supposed to be
  // declared as private

public:
  // getters are `const`-qualified (mutating) member functions
  // setters are NOT `const`-qualified (non-mutating) member functions

  const char *getName() const;    // getter for the `name` member variable
  bool setName(const char *name); // setter for the `name` member variable
  void printName() const;         // `const`-qualified member function
  bool readName();

  unsigned int getAge() const;   // getter for the `age` member variable
  void setAge(unsigned int age); // setter for the `age` member variable
  void printAge() const;         // `const`-qualified member function
  bool readAge();

  void assign(const char *name, unsigned int age);
  void print() const; // `const`-qualified member function
  bool read();
};

const char *Person::getName() const {
  return this->name;
  // setName("Ivan Ivanov"); // won't compile, thus preventing us from
  // modifying the object in an immutable context
}

bool Person::setName(const char *name) {
  // if the `name` argument is null or empty, fail to set it
  if (name == nullptr || *name == '\0')
    return false;

  // if the `name` argument contains an invalid character, fail to set it
  for (const char *c{name}; *c; c++) {
    if (!(*c >= 'A' && *c <= 'Z' || *c >= 'a' && *c <= 'z' || *c == '-' ||
          *c == ' '))
      return false;
  }

  // copy the `name` argument into the member variable of the same name
  strncpy(this->name, name, MAX_NAME_LEN);
  return true;
}

void Person::printName() const {
  std::cout << "Person name: " << getName() << std::endl;
  // setName("Peter Petrov"); // won't compile
}

bool Person::readName() {
  std::cout << "Enter person name: ";
  char name[MAX_NAME_LEN];
  std::cin.getline(name, MAX_NAME_LEN);
  // check if input was too long for the `name` member variable (>
  // MAX_NAME_LEN), or if some other (system-related) issue occurred with the
  // input
  if (std::cin.fail())
    return false;

  // use the setter for the `name` member variable
  return setName(name);
}

unsigned int Person::getAge() const {
  return this->age;
  // setAge(42); // won't compile
}

void Person::setAge(unsigned int age) {
  // no need to validate `age` because all non-negative integers are valid ages
  this->age = age;
}

void Person::printAge() const {
  std::cout << "Person age: " << getAge() << std::endl;
  // setAge(42); // won't compile
}

bool Person::readAge() {
  std::cout << "Enter person age: ";
  // use `int` as the type in order to be able to verify whether a negative
  // number was entered if `unsigned int` is used as the type here and a
  // negative number is entered, its two's complement representation would be
  // interpreted as an unsigned (positive) value, and the `age < 0` check
  // wouldn't discard it
  int age;
  std::cin >> age;
  // check if input was not a valid integer, or if it was negative, or if some
  // other (system-related) issue occurred with the input
  if (std::cin.fail() || age < 0)
    return false;

  // use the setter for the `age` member variable
  setAge(age);
  return true;
}

void Person::assign(const char *name, unsigned int age) {
  setName(name);
  setAge(age);
}

void Person::print() const {
  printName();
  printAge();
}

bool Person::read() {
  if (!readName())
    return false;

  if (!readAge())
    return false;

  return true;
}

int main() {
  Person p;

  if (!p.readAge()) {
    std::cerr << "error: could not read person age or it is an invalid one!"
              << std::endl;
    return 1;
  }

  std::cin.ignore();
  if (!p.readName()) {
    std::cerr << "error: could not read person name or it is an invalid one!"
              << std::endl;
    return 1;
  }

  const Person &cs{p};
  cs.printAge();
  cs.printName();
  // cs.setAge(42); // won't compile, thus preventing us from modifying the
  // object through an immutable reference

  p.setName("John Doe");
  p.printName();

  p.setAge(32);
  p.printAge();

  p.assign("Jane Doe", 33);
  p.print();

  if (!p.read()) {
    std::cerr << "error: could not read person successfully!" << std::endl;
    return 1;
  }
  p.print();

  return 0;
}
