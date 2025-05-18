#include <cstring>

#include "string.h"

void assertIsNonEmpty(const char *value) {
  if (value == nullptr)
    throw "string value may not be null";

  if (*value == '\0')
    throw "string value may not be empty";
}

void String::destroy() {
  delete[] data;
  data = nullptr;
}

void String::assign(const char *value) {
  assertIsNonEmpty(value);

  destroy();

  size_t len{strlen(value) + 1};
  data = new char[len];
  strncpy(data, value, len);
}

String::String(const char *value) { assign(value); }

String::String(const String &other) : String{other.data} {}

String &String::operator=(const String &other) {
  if (&other != this) {
    assign(other.data);
  }
  return *this;
}

String::~String() { destroy(); }