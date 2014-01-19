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

// standard includes
#include <string>

// Qt includes
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>

// my includes
#include "utils.h"

using namespace std;
//using namespace utils;

namespace utils{
  std::string timestamp(void)
  {
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime); 
    return std::string(asctime(timeinfo));
  }

  bool containsKey(const QStringList& args, const char* key)
  {
    bool retval = false;
    if (args.indexOf(key) != -1) retval = true;
    return (retval);
  }
  
  QString valueForKey(const QStringList& args, const char* key)
  {
    int index = args.indexOf(key);
    QString str = "";
    if ((index != -1) && (args.size() >= index +1)) 
      str = (args.at(args.indexOf(key) + 1));
    return (str);
  }
  
  void csl_2_vec(QSqlQuery& query, int index, const char* separator, std::vector<int>& vec, int& val)
  {
    QStringList stringList = query.value(index).toString().split(separator);
    for (auto iter : stringList) {
      val += iter.toInt();
      vec.push_back(val);        
    }
  }
  
  // variant 'A'
  bool copy_mapped_value(const QStringList& args, const std::string& key, QString& dest)
  {
    QString value = utils::valueForKey(args, key.c_str());
    if ((value) == "") { return false;}
    dest = value;
    return (true);
  }
  
  // variant 'B', calls variant 'A'
  bool copy_mapped_value(const QStringList& args, const char* key, string& dest)
  {
    QString value;
    if (copy_mapped_value(args, key, value))
    {
      dest = value.toStdString();
      return (true);
    }
  
    return (false);
  }
  
  // variant 'C', calls variant 'B'
  bool copy_mapped_value(const QStringList& args, const std::string& key, std::string& dest)
  {
    return (copy_mapped_value(args, key.c_str(), dest));
  }
  
  // variant 'D'
  bool copy_mapped_value(const QStringList& args, const char* key, int32_t& dest)
  {
    QString value = utils::valueForKey(args, key);
    if (value == "") { return false; }
    dest = value.toInt();
    return (true);
  }

  // variant 'E'
  bool copy_mapped_value(const QStringList& args, const char* key, uint32_t& dest)
  {
    QString value = utils::valueForKey(args, key);
    if (value == "") { return false; }
    dest = value.toUInt();
    return (true);
  }

  // variant 'F'
  bool copy_mapped_value(const QStringList& args, const char* key, float& dest)
  {
    QString value = utils::valueForKey(args, key);
    if (value == "") { return false; }
    dest = value.toFloat();
    return (true);
  }

  void exit_if_no_cachefile_specified(const QStringList& args, const string& key, string& dest, const string& functionName)
  {
    copy_mapped_value(args, key, dest);
    if (dest == "")
    {
      cout << functionName << " *** Error: You need to specify a filename for the cache file in the command line arguments via '" << key << " somefilename.txt' . We build the object from a db query the first time, and save the result to a cache file. Next time we create the object, we restore it from the cache file to improve performance." << endl;
      usage();
    }
  }

  void usage()
  {
    cout << FN << "Usage: ninemops -host localhost -database mydbname -username myname -password mypassword" << endl;
    cout << FN << "[-minlat -117000000 -maxlat -116000000 -minlong 543000000 -maxlong 544000000 -minel 0 -maxel 100000]" << endl;
    cout << "eg. ./ninemops -host localhost -database db123 -username me -password mypassword -minlat -117000000 -maxlat -116000000 -minlong 543000000 -maxlong 544000000 -minel 0 -maxel 100000 --elevations-filename cache/elevations --locations-filename cache/locations --locations-query \"SELECT latitudes, longitudes, elevations from gps_history LIMIT 100;\"";
    exit (-1);
  }

  bool Exit(const char* msg, int32_t error_code)
  {
    std::cerr << msg << std::endl;
    exit(error_code);
    return true;
  }

} //namespace
