#include "file.h"

#include <iostream>

File::File(const String &name, size_t size, bool hidden, bool system,
           bool forArchival, bool readOnly)
    : name{name}, size{size}, hidden{hidden}, system{system},
      forArchival{forArchival}, readOnly{readOnly} {}

void File::print() const {
  std::cout << "Name: " << name.getData() << std::endl;
  std::cout << "Size: " << size << std::endl;
  std::cout << "Hidden: " << (hidden ? "yes" : "no") << std::endl;
  std::cout << "System: " << (system ? "yes" : "no") << std::endl;
  std::cout << "For archival: " << (forArchival ? "yes" : "no") << std::endl;
  std::cout << "Read-only: " << (readOnly ? "yes" : "no") << std::endl;
  std::cout << std::endl;
}
