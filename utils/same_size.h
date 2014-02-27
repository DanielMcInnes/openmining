#ifndef same_size_h
#define same_size_h

namespace utils
{
  template<class T>
  bool same_size(const T& container1, const T& container2, const T& container3)
  {
    bool retval = false;
    size_t size = container1.size();
    if ((size == container2.size()) && (size == container3.size())) retval = true;
    return (retval);
  }
}
#endif
