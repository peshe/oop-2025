#include <cstdint>
#include <iostream>

struct alignment1 {
  uint8_t small;
  uint64_t large;
};

struct alignment2 {
  uint64_t large;
  uint8_t small;
};

struct alignment3 {
  char a;
  int b;
  double c;
  char d;
};

struct alignment4 {
  double c;
  int b;
  char a;
  char d;
};

int main() {
  std::cout << sizeof(alignment1) << std::endl;
  alignment1 a1;
  a1.small = 1;
  a1.large = 2;
  for (size_t i{0}; i < sizeof(a1); i++)
    std::cout << std::hex << (int)((const uint8_t *)&a1)[0];
  std::cout << std::endl;

  std::cout << sizeof(alignment2) << std::endl;
  alignment2 a2;
  a2.small = 1;
  a2.large = 2;
  for (size_t i{0}; i < sizeof(a2); i++)
    std::cout << std::hex << (int)((const uint8_t *)&a2)[0];
  std::cout << std::endl;

  std::cout << sizeof(alignment3) << std::endl;
  std::cout << sizeof(alignment4) << std::endl;

  return 0;
}
