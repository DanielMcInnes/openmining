#ifndef update_progress_h
#define update_progress_h

#include <iostream>

namespace utils
{
  template<class Tnewval, class Toldval>
  bool update_progress(Tnewval& newval, Toldval& oldval)
  {
    bool retval = false;
    if (oldval != newval)
    {
      oldval = newval;
      retval = true;
    }
    return (retval);
  }

  template<class T>
  bool update_progress(const T& newval, T&oldval, const char* fn)
  {
    bool retval = update_progress(newval, oldval);
    if (retval)
    {
      std::cout << fn << ": " << newval << "% complete."  << std::endl;      
    }
    return retval;
  }
}

#endif
