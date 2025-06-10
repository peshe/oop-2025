#pragma once

#include "string.h"

#include <cstddef>

class File {
protected:
  String name;
  size_t size;
  bool hidden : 1;
  bool system : 1;
  bool forArchival : 1;
  bool readOnly : 1;

public:
  File(const String &name, size_t size = 0, bool hidden = false,
       bool system = false, bool forArchival = false, bool readOnly = false);
  virtual ~File() {}

  virtual File *clone() const = 0;

  const String &getName() const { return name; }
  virtual size_t getSize() const { return size; }
  bool isHidden() const { return hidden; }
  bool isSystem() const { return system; }
  bool isForArchival() const { return forArchival; }
  bool isReadOnly() const { return readOnly; }

  void setName(const String &name) { this->name = name; }

  virtual void print() const;
};
