// std lib includes
#include <iostream>

// boost includes

//Qt includes
#include <QStringList>

// my includes
#include "Exit.h"
#include "utils.h"

using namespace std;

namespace utils
{
  int find_or_exit(const QStringList& args, const char* key, const char* funcname)
  {
    int index = args.indexOf(key);
    std::string err = std::string("ERROR!!! ") + funcname + std::string(": invalid value for ") + std::string(key);
    if((index == -1) || (args.size() <= index + 1))
    {
      cerr << err << std::endl;
      usage();
      Exit(err, -1);
    }
    int retval = args.at(args.indexOf(key) + 1).toInt();
    return retval;
  }
}
