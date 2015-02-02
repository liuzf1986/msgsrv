#pragma once

#include <unistd.h>

class LogFile {
 public:
  LogFile(const char* baseName);
  ~LogFile();
  void applyFileName(const char* fileName);
  void recreateFD();
 private:
  char _path[256];
  int _fd;
};


