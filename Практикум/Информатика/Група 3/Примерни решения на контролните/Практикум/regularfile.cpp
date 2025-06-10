#include "regularfile.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

RegularFile::RegularFile(const String &name, const String &extension,
                         size_t size, bool hidden, bool system,
                         bool forArchival, bool readOnly)
    : File{name, size, hidden, system, forArchival, readOnly} {
  if (*extension.getData() == '\0')
    throw std::invalid_argument{"extension may not be an empty string"};

  this->name += ".";
  this->name += extension;
}

RegularFile::RegularFile(const String &name, size_t size, bool hidden,
                         bool system, bool forArchival, bool readOnly)
    : File{name, size, hidden, system, forArchival, readOnly} {
  if (*name.getData() == '\0')
    throw std::invalid_argument{"filename may not be an empty string"};

  if (!name.contains('.'))
    throw std::invalid_argument{"no extension in filename"};
}

File *RegularFile::clone() const { return new RegularFile{*this}; }

void RegularFile::print() const {
  std::cout << "Regular file" << std::endl;
  File::print();
}

RegularFile &RegularFile::operator+=(const String &s) {
  if (readOnly)
    throw std::logic_error{"file is read-only"};

  size += strlen(s.getData());

  return *this;
}

RegularFile RegularFile::operator+(const String &s) {
  RegularFile newFile{*this};
  newFile += s;
  return newFile;
}
