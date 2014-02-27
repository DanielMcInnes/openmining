
#include <QString>

#include "get_mapped_value.h"
namespace utils
{
  QString get_mapped_value(const QStringList& args, const char* key, const char* caller)
  {
    QString retval;
    std::string errorMessage = std::string("ERROR!!! In function '") + caller + "': '" + key + "' not specified correctly in the command line arguments.";
    if (! copy_mapped_value(args, key, retval)) Exit(errorMessage, -1);
    return retval;
  }
}
