#include "filesystem.h"

#include "directory.h"

#include <cstring>
#include <fstream>
#include <stdexcept>

void Filesystem::destroy() { delete rootDir; }

void Filesystem::assign(const Filesystem &other) {
  rootDir = new Directory{*other.rootDir};
  currentDir = rootDir;
}

Filesystem::Filesystem(Directory &rootDir)
    : rootDir{&rootDir}, currentDir{&rootDir} {}

Filesystem::Filesystem(const Filesystem &other) { assign(other); }

Filesystem &Filesystem::operator=(const Filesystem &other) {
  if (&other != this) {
    destroy();
    assign(other);
  }

  return *this;
}

Filesystem::~Filesystem() { destroy(); }

void Filesystem::chdir(const String &path) {
  if (path == "")
    return;

  String pathCopy{path};
  char *childDirName{strtok(pathCopy.getData(), "/")};
  if (childDirName == nullptr) {
    currentDir = rootDir;
    return;
  }

  Directory *dir;
  if (*childDirName == '\0') {
    dir = rootDir;
    childDirName++;
    childDirName = strtok(nullptr, "/");
  } else {
    dir = currentDir;
  }

  do {
    File *childFile{(*dir)[childDirName]};
    if (childFile == nullptr)
      throw std::invalid_argument{"directory component does not exist"};

    Directory *childDir = dynamic_cast<Directory *>(childFile);
    if (!childDir)
      throw std::invalid_argument{"component name does not refer to directory"};

    dir = childDir;
    childDirName += strlen(childDirName);
    childDirName = strtok(nullptr, "/");
  } while (childDirName != nullptr);

  currentDir = dir;
}

const Directory *searchRec(const String &filename,
                           bool lookInHiddenAndSystemDirs,
                           const Directory *dir) {
  if (!lookInHiddenAndSystemDirs && (dir->isHidden() || dir->isSystem()))
    return nullptr;

  const File *file{(*dir)[filename]};
  if (file != nullptr)
    return dir;

  size_t numOfFilesInDir{dir->getNumberOfFiles()};
  for (size_t i{0}; i < numOfFilesInDir; i++) {
    const File *file{(*dir)[i]};
    const Directory *dir{dynamic_cast<const Directory *>(file)};
    if (dir == nullptr)
      continue;

    dir = searchRec(filename, lookInHiddenAndSystemDirs, dir);
    if (dir != nullptr)
      return dir;
  }

  return nullptr;
}

const Directory *Filesystem::search(const String &filename,
                                    bool lookInHiddenAndSystemDirs) const {
  return searchRec(filename, lookInHiddenAndSystemDirs, currentDir);
}

void writePathsToFilesForArchivalRec(std::ostream &output, const File *file,
                                     const String &path) {
  if (file->isForArchival())
    output << path.getData() << ' ' << file->getSize() << std::endl;

  const Directory *dir{dynamic_cast<const Directory *>(file)};
  if (dir == nullptr)
    return;

  size_t numOfFilesInDir{dir->getNumberOfFiles()};
  for (size_t i{0}; i < numOfFilesInDir; i++) {
    const File *file{(*dir)[i]};

    String filePath{path};
    filePath += "/";
    filePath += file->getName();

    writePathsToFilesForArchivalRec(output, file, filePath);
  }
}

void Filesystem::writePathsToFilesForArchival(
    const String &textFilePath) const {
  std::ofstream textFile{textFilePath.getData()};
  if (!textFile.is_open())
    throw std::runtime_error{"could not open text file"};

  writePathsToFilesForArchivalRec(textFile, rootDir, "/");
}
