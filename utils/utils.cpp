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
#include "copy_mapped_value.h"
#include "Exit.h"


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
 
  void exit_if_no_cachefile_specified(const QStringList& args, const string& key, string& dest, const string& functionName)
  {
    copy_mapped_value(args, key, dest);
    if (dest == "")
    {
      cerr << functionName << " *** Error: You need to specify a filename for the cache file in the command line arguments via '" << key << " somefilename.txt' . We build the object from a db query the first time, and save the result to a cache file. Next time we create the object, we restore it from the cache file to improve performance." << endl;
      usage();
      Exit(functionName, -1);
    }
  }

/*
  bool Exit(const char* msg, int32_t error_code)
  {
    std::cerr << msg << std::endl;
    exit(error_code);
    return true;
  }
*/
} //namespace
