#ifndef load_h
#define load_h

#include <iostream>
#include <fstream>

// boost includes
#include <boost/archive/text_iarchive.hpp>

namespace utils
{
  template <class Tobject, class Tfilename>
  bool load(Tobject& object, Tfilename& filename)
  {
    bool retval = false;
    if (filename == "")
    {
      std::cerr << "Error: trying to restore an object from a nameless file" << std::endl;
    }
    else
    {
      std::ifstream ifs (filename);
  
      if (ifs.good())
      {
        std::cout << __PRETTY_FUNCTION__ <<  "loading object from file '" << filename << "'" << std::endl;
        boost::archive::text_iarchive ia(ifs);
        ia >> object;
        retval = true;
      }
    }
    return (retval);
  }
  
  template <class Tobject, class Tfilename>
  bool load(Tobject* object, Tfilename& filename)
  {
    return (load (*object, filename));
  }
}

#endif
