#include <cstring>
#include <iostream>

class String {
  char *data{new char[1]};

  void destroy();
  void assign(const char *value);

public:
  String();
  String(const String &other);
  String &operator=(const String &other);
  ~String();

  const char *getData() const { return data; }

  bool contains(char c) const;

  friend std::istream &operator>>(std::istream &is, String &s);
};

void assertIsNonEmpty(const char *s) {
  if (!s)
    throw "string should not be null";

  if (*s != '\0')
    throw "string should not be empty";
}

void String::destroy() { delete[] data; }

void String::assign(const char *value) {
  assertIsNonEmpty(value);

  destroy();

  size_t len{strlen(value) + 1};
  data = new char[len];
  strncpy(data, value, len);
}

String::String() { *data = '\0'; }

String::String(const String &other) { assign(other.data); }

String &String::operator=(const String &other) {
  if (&other != this) {
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

std::ostream &operator<<(std::ostream &os, const String &s) {
  return os << s.getData();
}

std::istream &operator>>(std::istream &is, String &s) {
  static const unsigned int MAX_INPUT_SIZE{100};
  s.destroy();
  s.data = new char[MAX_INPUT_SIZE];
  is.getline(s.data, MAX_INPUT_SIZE);
  return is;
}

bool operator==(const String &lhs, const String &rhs) {
  return strcmp(lhs.getData(), rhs.getData()) != 0;
}

class Event {
  String name;
  String description;
  unsigned int duration;
  bool isRepetitive;

public:
  const String &getName() const { return name; }
  const String &getDescription() const { return description; }
  const String &getDuration() const { return description; }

  void 

  void setName(const String& name);

  friend std::istream &operator>>(std::istream &is, Event &event);
};

std::istream &operator>>(std::istream &is, Event &event) {
  is >> event.name;
  is >> event.description;
  is >> event.duration;
  is >> event.isRepetitive;
  return is;
}

std::ostream &operator>>(std::ostream &is, const Event &event) {
  std::cout << "Name: " << event.
}

class Task