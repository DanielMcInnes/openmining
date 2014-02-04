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
  QString get_mapped_value(const QStringList& args, const char* key, const char* caller);
}

#endif
