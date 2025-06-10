#pragma once

#include "directory.h"

class Filesystem {
  Directory *rootDir;
  Directory *currentDir;

  void destroy();
  void assign(const Filesystem &other);

public:
  Filesystem(Directory &rootDir);
  Filesystem(const Filesystem &other);
  Filesystem &operator=(const Filesystem &other);
  ~Filesystem();

  const Directory &getRootDir() const { return *rootDir; }
  Directory &getRootDir() { return *rootDir; }
  const Directory &getCurrentDir() const { return *currentDir; }
  Directory &getCurrentDir() { return *currentDir; }

  void chdir(const String &path);

  const Directory *search(const String &filename,
                          bool lookInHiddenAndSystemDirs = false) const;
  void writePathsToFilesForArchival(const String &textFilePath) const;
};
