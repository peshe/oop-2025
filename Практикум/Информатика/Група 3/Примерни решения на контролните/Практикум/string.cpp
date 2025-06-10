#include "string.h"

#include <cstring>
#include <stdexcept>

void String::destroy() {
  delete[] data;
  data = nullptr;
}

void String::assign(const char *value) {
  if (!value)
    throw std::invalid_argument{"string may not be null"};

  size_t len{strlen(value) + 1};
  data = new char[len];
  strncpy(data, value, len);
}

String::String() : data{new char[1]} { *data = '\0'; }

String::String(const char *value) { assign(value); }

String::String(const String &other) : String{other.data} {}

String &String::operator=(const String &other) {
  if (&other != this) {
    destroy();
    assign(other.data);
  }

  return *this;
}

String::~String() { destroy(); }

bool String::contains(char c) const {
  char *it{data};
  while (*it != '\0' && *it != c)
    it++;

  return *it == c;
}

String &String::operator+=(const String &appendStr) {
  size_t oldStrLen{strlen(data)};
  size_t appendStrLen{strlen(appendStr.data)};
  size_t newStrLenWithTermZero{oldStrLen + appendStrLen + 1};
  char *newStr{new char[newStrLenWithTermZero]};
  strncpy(newStr, data, oldStrLen + 1);
  strncpy(newStr + oldStrLen, appendStr.data, appendStrLen + 1);

  destroy();
  data = newStr;

  return *this;
}

bool operator==(const String &lhs, const String &rhs) {
  return strcmp(lhs.getData(), rhs.getData()) != 0;
}
