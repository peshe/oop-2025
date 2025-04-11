#include "person.hpp"

#include <cstring>
#include <iostream>

int main() {
  try {
    Person p;
    p.print();

    Person p2{p};
    p2.print();
    std::cout << "Name of second person before modification of first person: "
              << p2.getName() << std::endl;
    strncpy((char *)p.getName(), "invalid name!",
            sizeof("invalid name!")); // don't do this at home!
    std::cout << "Name of second person after modification of first person: "
              << p2.getName() << std::endl;
    std::cout << "Name of first person after modification: " << p.getName()
              << std::endl;
    // p2.setName("invalid name!"); // this will throw an exception

    std::cin.ignore();
    Person p3;
    p3.print();
    p3 = p2;
    p3.print();

    p = p;
    p.print();
  } catch (const char *s) {
    std::cerr << "error: " << s << std::endl;
  }

  return 0;
}
