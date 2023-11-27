#pragma once

#include "SD_MMC.h"
#include "FS.h"

#include "pin_config.h"

namespace FileManager {
  bool start();
  bool writeFile(const char* path, const char* data);
  bool fileExists(const char* path);
  bool deleteFile(const char* path);
  String readFile(const char* path);
  String listDir(const char* dir);
};
