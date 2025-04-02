#include <cstring>
#include <iostream>
#include <type_traits>

// TODO: split class definition into header file
class Student {
  // we have an abstraction of a student with the following two characteristics
  char *name; // hidden - encapsulation ensures that memory for the name isn't
              // managed improperly
  int age;

public:
  Student() = default;
  Student(const char *name, int age);

  const char *getName() const;
  void setName(const char *name);

  int getAge() const;
  void setAge(int age);
};

Student::Student(const char *name, int age) {
  setName(name);
  setAge(age);
  const auto l_is_this_of_ptr_type{std::is_pointer_v<decltype(this)>};
  if (l_is_this_of_ptr_type)
    std::cout << "`this` is of a pointer type!" << std::endl;
}

const char *Student::getName() const { return this->name; }

void Student::setName(const char *name) {
  auto size{strlen(name) + 1};
  this->name = new char[size];
  strncpy(this->name, name, size);
}

int Student::getAge() const { return this->age; }

void Student::setAge(int age) { this->age = age; }

void printStudentAge(const Student &s) {
  std::cout << "Student age: " << s.getAge() << std::endl;
  // s.setAge(42); // won't compile, thus saving us from modifying the object in
  // an immutable context
}

int main() {
  Student s;

  std::cout << "Enter student name: ";
  char name[100];
  std::cin.getline(name, 100);
  s.setName(name);

  std::cout << "Enter student age: ";
  int age;
  std::cin >> age;
  s.setAge(age);

  std::cout << "Student name: " << s.getName() << std::endl;
  printStudentAge(s);

  const Student s1{"The Eternal Student", 137};
  std::cout << "Student name: " << s1.getName() << std::endl;
  // s1.setName("Peter Petrov"); // won't compile because s1 is const!
  // s1.setAge(23); // won't compile because s1 is const!
  printStudentAge(s1);
}
