#ifndef between_h
#define between_h

namespace utils
{
  template<class T>
  bool between(const T& val, const T& minval, const T& maxval)
  {
    bool retval = false;
    if ((val >= minval) && (val <= maxval))
      retval = true;
    return (retval);
  }
}

#endif
