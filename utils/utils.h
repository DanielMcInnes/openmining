/*
  Copyright 2014 Daniel McInnes

  This file is part of OpenMining.

  OpenMining is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenMining is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenMining.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef UTILS_H
#define UTILS_H

// standard library includes
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
//#include "location.h"
//#include "elevation.h"

#define FN __PRETTY_FUNCTION__
#define CLASS typeid(*this).name() 
//#define CLASS (const std::string(typeid(*this).name()))
class Location;

namespace utils{
  std::string timestamp(void);
  bool contains_key(const QStringList& args, const char* key);
  void csl_2_vec(QSqlQuery& query, int index, const char* separator, std::vector<int>& vec, int& val);

  void exit_if_no_cachefile_specified(const QStringList& args, const std::string& key, std::string& dest, const std::string& functionName);

/*
  bool Exit(const char* msg, int32_t error_code);*/
  void usage();
  
} // namespace
#endif
