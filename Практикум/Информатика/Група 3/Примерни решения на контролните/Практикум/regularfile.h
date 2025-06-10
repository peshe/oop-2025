#pragma once

#include "file.h"

class RegularFile : public File {
public:
  RegularFile(const String &name, const String &extension, size_t size = 0,
              bool hidden = false, bool system = false,
              bool forArchival = false, bool readOnly = false);
  RegularFile(const String &name, size_t size = 0, bool hidden = false,
              bool system = false, bool forArchival = false,
              bool readOnly = false);

  virtual File *clone() const override;

  virtual void print() const override;

  RegularFile &operator+=(const String &s);
  RegularFile operator+(const String &s);
};
