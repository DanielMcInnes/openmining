#ifndef get_mapped_value_h
#define get_mapped_value_h

// standard lib includes
#include <string>

// boost includes

// Qt includes
#include <QString>
#include <QStringList>

// my includes
#include "copy_mapped_value.h"
#include "Exit.h"

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

#endif
