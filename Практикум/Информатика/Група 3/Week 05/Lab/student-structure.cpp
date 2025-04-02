#include <cstring>
#include <iostream>

struct Student {
  char *name;
  int age;
};

const char *getStudentName(const Student &s) { return s.name; }

void setStudentName(Student &s, const char *newName) {
  auto size{strlen(newName) + 1};
  s.name = new char[size];
  strncpy(s.name, newName, size);
}

int getStudentAge(const Student &s) { return s.age; }

void setStudentAge(Student &s, int age) { s.age = age; }

void printStudentAge(const Student &s) {
  std::cout << "Student age: " << getStudentAge(s) << std::endl;
  // setStudentAge(42); // won't compile, thus saving us from modifying the
  // object in an immutable context
}

void initStudent(Student &s, const char *name, int age) {
  setStudentName(s, name);
  setStudentAge(s, age);
}

int main() {
  Student s;

  std::cout << "Enter student name: ";
  char name[100];
  std::cin.getline(name, 100);
  setStudentName(s, name);

  std::cout << "Enter student age: ";
  int age;
  std::cin >> age;
  setStudentAge(s, age);

  std::cout << "Student name: " << getStudentName(s) << std::endl;
  printStudentAge(s);
}
