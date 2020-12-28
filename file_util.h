#ifndef SUPERMARIOBROS_FILE_UTIL_H
#define SUPERMARIOBROS_FILE_UTIL_H

#include <string>

std::string findRootDirectory(const std::string& argv0);

bool dirExists(const std::string& path);

#endif  // SUPERMARIOBROS_FILE_UTIL_H
