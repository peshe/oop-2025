#include "directory.h"

#include "regularfile.h"

#include <iostream>
#include <stdexcept>

void Directory::destroy() {
  for (size_t i{0}; i < numOfFiles; i++)
    delete files[i];
  delete[] files;
  files = nullptr;
}

void Directory::assign(const Directory &other) {
  capacityOfFiles = other.capacityOfFiles;
  numOfFiles = 0;
  files = new File *[capacityOfFiles];

  try {
    for (size_t i{0}; i < other.numOfFiles; i++) {
      files[i] = other.files[i]->clone();
      numOfFiles++;
    }
  } catch (const std::exception &e) {
    for (size_t i{0}; i < numOfFiles; i++)
      delete files[i];
    delete[] files;

    throw e;
  }
}

File *Directory::getFile(const String &filename) const {
  for (size_t i{0}; i < numOfFiles; i++)
    if (files[i]->getName() == filename)
      return files[i];

  return nullptr;
}

File *Directory::getFile(size_t index) const {
  if (index >= numOfFiles)
    return nullptr;

  return files[index];
}

void Directory::addFile(File &file) {
  if (readOnly)
    throw std::logic_error{"directory is read-only"};

  for (size_t i{0}; i < numOfFiles; i++)
    if (files[i]->getName() == file.getName())
      throw std::logic_error{
          "file with the same name already exists in directory"};

  if (numOfFiles == capacityOfFiles) {
    capacityOfFiles *= 2;
    File **newFiles = new File *[capacityOfFiles];
    for (size_t i{0}; i < numOfFiles; i++)
      newFiles[i] = files[i];
    delete[] files;
    files = newFiles;
  }

  files[numOfFiles++] = &file;
}

Directory::Directory(const String &name, bool hidden, bool system,
                     bool forArchival, bool readOnly)
    : File{name, 0, hidden, system, forArchival, readOnly}, numOfFiles{0},
      capacityOfFiles{1}, files{new File *[capacityOfFiles]} {}

Directory::Directory(const Directory &other)
    : File{other.name,   other.size,        other.hidden,
           other.system, other.forArchival, other.readOnly} {
  assign(other);
}

Directory &Directory::operator=(const Directory &other) {
  if (&other != this) {
    File::operator=(other);
    destroy();
    assign(other);
  }

  return *this;
}

Directory::~Directory() { destroy(); }

File *Directory::clone() const { return new Directory{*this}; }

size_t Directory::getSize() const {
  size_t size{0};
  for (size_t i{0}; i < numOfFiles; i++)
    size += files[i]->getSize();
  return size;
}

void Directory::print() const {
  std::cout << "Directory" << std::endl;
  File::print();
  std::cout << "Number of files: " << numOfFiles << std::endl;

  for (size_t i{0}; i < numOfFiles; i++)
    if (!files[i]->isHidden() && !files[i]->isSystem())
      files[i]->print();
}

const File *Directory::operator[](const String &filename) const {
  return getFile(filename);
}

File *Directory::operator[](const String &filename) {
  return getFile(filename);
}

const File *Directory::operator[](size_t index) const { return getFile(index); }

File *Directory::operator[](size_t index) { return getFile(index); }

Directory &Directory::operator+=(File &file) {
  addFile(file);
  return *this;
}

Directory Directory::operator+(File &file) {
  Directory newDir{*this};
  newDir += file;
  return newDir;
}

Directory &Directory::operator+=(const String &filename) {
  File *newFile{new RegularFile{filename}};
  try {
    addFile(*newFile);
  } catch (const std::exception &e) {
    delete newFile;

    throw e;
  }

  return *this;
}

Directory Directory::operator+(const String &filename) {
  Directory newDir{*this};
  newDir += filename;
  return newDir;
}
