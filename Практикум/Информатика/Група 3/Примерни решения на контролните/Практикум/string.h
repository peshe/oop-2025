#pragma once

class String {
  char *data{nullptr};

  void destroy();
  void assign(const char *value);

public:
  String();
  String(const char *value);
  String(const String &other);
  String &operator=(const String &other);
  ~String();

  const char *getData() const { return data; }
  char *getData() { return data; }

  bool contains(char c) const;

  String &operator+=(const String &appendStr);
};

bool operator==(const String &lhs, const String &rhs);
