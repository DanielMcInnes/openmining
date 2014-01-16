#ifndef contains_h
#define contains_h

namespace utils
{
  template <class Tcontainer, class Tkey>
  bool contains(Tcontainer& container, Tkey& key)
  {
    auto it = container.find(key);
    if (it == container.end()) { return false; }
    return true;
  }
}

#endif

