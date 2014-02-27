#ifndef check_argv_h
#define check_argv_h

// my includes
#include "utils.h"
#include "Exit.h"

namespace utils
{
  template<class Tcmdline_keys, class Trequired_keys>
  void check_argv(const Tcmdline_keys& cmdline_keys, const char* funcname, const Trequired_keys& required_keys)
  {
    for (auto str : required_keys)
    {
      if (valueForKey(cmdline_keys, str.c_str()) == "")
      {
        Exit(str, -1);
      }
    }
  }
}



#endif
