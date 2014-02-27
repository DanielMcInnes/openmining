#ifndef find_or_exit_h
#define find_or_exit_h

// standard library includes
#include <string>

// my includes
#include "utils.h"
#include "Exit.h"

namespace utils
{
  int find_or_exit(const QStringList& args, const char* key, const char* funcname);
}
#endif
