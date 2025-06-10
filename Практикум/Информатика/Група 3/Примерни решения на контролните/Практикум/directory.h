#pragma once

#include "file.h"

class Directory : public File {
  size_t numOfFiles, capacityOfFiles;
  File **files{nullptr};

  void destroy();
  void assign(const Directory &other);

  File *getFile(const String &filename) const;
  File *getFile(size_t index) const;

  void addFile(File &file);

public:
  Directory(const String &name = "", bool hidden = false, bool system = false,
            bool forArchival = false, bool readOnly = false);
  Directory(const Directory &other);
  Directory &operator=(const Directory &other);
  ~Directory();

  virtual File *clone() const override;

  virtual size_t getSize() const override;
  size_t getNumberOfFiles() const { return numOfFiles; }

  virtual void print() const override;

  const File *operator[](const String &filename) const;
  File *operator[](const String &filename);
  const File *operator[](size_t index) const;
  File *operator[](size_t index);

  Directory &operator+=(File &file);
  Directory operator+(File &file);
  Directory &operator+=(const String &filename);
  Directory operator+(const String &filename);
};
