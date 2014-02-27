#ifndef Exit_h
#define Exit_h

#include <iostream>

namespace utils
{
  template<class T>
  void Exit(T& msg, int32_t error_code)
  {
    std::cerr << msg << std::endl;
    exit (error_code);
  }

  template<class T>
  void Exit(T& msg1, T& msg2, int32_t error_code)
  {
    std::cerr << "Error! " << msg1 << ": " << msg2 << std::endl;
    exit (error_code);
  }}
#endif
