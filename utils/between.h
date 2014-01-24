#ifndef between_h
#define between_h

/*!
 @file between.h
*/
namespace utils
{
/*!
 * returns true if val >= minval and <= maxval
 * @param val 
 * @param minval
 * @param maxval
 * @return true if val >= minval and <= maxval, false otherwise
 */
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
