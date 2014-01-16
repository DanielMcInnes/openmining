#ifndef save_h
#define save_h

// boost includes
#include <boost/archive/text_oarchive.hpp>

namespace utils
{ 
  template <class T>
  void save(T& object, const std::string& filename)
  {
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa (ofs);
    oa << object;
  }
}

#endif
