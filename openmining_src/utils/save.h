#ifndef save_h
#define save_h

//std includes
#include <fstream>
#include <iostream>

// boost includes
#include <boost/archive/text_oarchive.hpp>
#include "utils/utils.h"

namespace utils
{ 
  template <class T>
  void save(T& object, const std::string& filename)
  {
    std::cout << FN << " : " << filename << std::endl;
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa (ofs);
    oa << object;
  }

  template <class T>
  void save(T* object, const std::string& filename)
  {
    save(*object, filename);
  }

  template <class T>
  bool saveIfUpdated(T& object, const char* filename)
  {
    bool retval = false;
    if (object.m_changesNotSaved)
    {
      std:: cout << FN << "changesNotSaved == true" << std::endl;
      retval = true;
      save(object, filename);
      object.m_changesNotSaved = false;
    }
    else
    {
      std:: cout << FN << "changesNotSaved == false" << std::endl;
    }
    return retval;
  }
  template <class T>
  bool saveIfUpdated(T* object, const char* filename)
  {
    return saveIfUpdated(*object, filename);
  }
}

#endif
