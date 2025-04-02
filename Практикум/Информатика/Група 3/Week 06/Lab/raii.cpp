#include <cstring>
#include <iostream>

class Student {
  char *name;
  int age;

public:
  Student();
  Student(const char *name, int age);
  Student(const Student &);
  Student &operator=(const Student &);
  ~Student();

  const char *getName() const;
  void setName(const char *name);

  int getAge() const;
  void setAge(int age);

  void printName() const;
  void printAge() const;
};

Student::Student() {
  std::cout << "Enter student name: ";
  char newName[100];
  std::cin.getline(newName, 100);
  setName(newName);

  std::cout << "Enter student age: ";
  unsigned int newAge;
  std::cin >> newAge;

  setAge(newAge);
}

Student::Student(const char *name, int age) {
  setName(name);
  setAge(age);
}

Student::Student(const Student &other) {
  setName(other.name);
  setAge(other.age);
}

Student &Student::operator=(const Student &other) {
  setName(other.name);
  setAge(other.age);
  return *this;
}

Student::~Student() { delete[] name; }

const char *Student::getName() const {
  if (!this->name || *this->name == '\0') {
    throw std::exception{};
  }
  return this->name;
}

void Student::setName(const char *name) {
  auto size{strlen(name) + 1};
  this->name = new char[size];
  strncpy(this->name, name, size);
}

int Student::getAge() const { return this->age; }

void Student::setAge(int age) { this->age = age; }

void printStudentName(const Student &s) {
  std::cout << "Student name: " << s.getName() << std::endl;
}

void printStudentAge(const Student &s) {
  std::cout << "Student age: " << s.getAge() << std::endl;
}

int main() {
  Student s;
  printStudentName(s);
  printStudentAge(s);

  Student s2{s};
  std::cout << "Before modification: " << s2.getName() << std::endl;
  strncpy((char *)s.getName(), "wrong name",
          sizeof("wrong name")); // don't do this at home!
  std::cout << "After modification: " << s2.getName() << std::endl;

  return 0;
}
