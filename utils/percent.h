#ifndef percent_h
#define percent_h

namespace utils
{
  template<class T>
  T percent(T numerator, T denominator) 
  {
    return ( (100 * numerator) / denominator); 
  }
}

#endif
