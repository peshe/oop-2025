#include <cstring>
#include <fstream>
#include <iostream>

static const size_t MAX = 100;

int main() {
  std::fstream f("hello.txt", std::ios::in | std::ios::out | std::ios::ate);
  if (!f.is_open()) {
    std::cerr << "failed to open file" << std::endl;
    return 1;
  }

  f.seekg(0, std::ios::beg);

  char line[MAX];
  f.getline(line, MAX);
  if (!f.good()) {
    std::cerr << "failed to read from file" << std::endl;
    return 1;
  }

  char *line_iter{line};
  while (*line_iter) {
    *line_iter += 13;
    line_iter++;
  }

  f.seekg(0, std::ios::beg);
  f.write(line, strlen(line));

  return 0;
}
