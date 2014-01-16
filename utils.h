/*
  Copyright 2014 Daniel McInnes

  This file is part of NineMops.

  NineMops is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  NineMops is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with NineMops.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef UTILS_H
#define UTILS_H

// standard library includes
#include <fstream>
#include <string>
#include <iostream>

// boost includes
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>

// Qt includes
#include <QSqlQuery>
#include <QString>
#include <QStringList>

// my includes
#include "location.h"
//#include "elevation.h"

#define FN __PRETTY_FUNCTION__

class Location;

namespace utils{
  std::string timestamp(void);
  bool containsKey(const QStringList& args, const char* key);
  QString valueForKey(const QStringList& args, const char* key);
  void csl_2_vec(QSqlQuery& query, int index, const char* separator, std::vector<int>& vec, int& val);

  bool copy_mapped_value(const QStringList& args, const std::string& key, QString& dest);
  bool copy_mapped_value(const QStringList& args, const std::string& key, std::string& dest);
  bool copy_mapped_value(const QStringList& args, const char* key,        std::string& dest);
  bool copy_mapped_value(const QStringList& args, const char* key,        int32_t& dest);
  bool copy_mapped_value(const QStringList& args, const char* key,        uint32_t& dest);
  bool copy_mapped_value(const QStringList& args, const char* key,        float& dest);

  template<class T>
  bool sameSize(const T& container1, const T& container2, const T& container3)
  {
    bool retval = false;
    size_t size = container1.size();
    if ((size == container2.size()) && (size == container3.size())) retval = true;
    return (retval);
  }

  template<class T>
  bool between(const T& val, const T& minval, const T& maxval)
  {
    bool retval = false;
    if ((val >= minval) && (val <= maxval))
      retval = true;
    return (retval);
  }

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
  
  template <class T>
  void save(T& object, const std::string& filename)
  {
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa (ofs);
    oa << object;
  }

  void exit_if_no_cachefile_specified(const QStringList& args, const std::string& key, std::string& dest, const std::string& functionName);

  bool Exit(const char* msg, int32_t error_code);

  template <class T>
  void exit_if_not_specified(QStringList& args, T& object, const std::string& key, const char* msg, const int32_t error_code)
  {
    if (!copy_mapped_value(args, key, object))
    {
      Exit(msg, error_code);
    }
  }

  void usage();

  template<class T>
  T percent(T numerator, T denominator) 
  {
    return ( (100 * numerator) /denominator); 
  }

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
  
} // namespace
#endif
