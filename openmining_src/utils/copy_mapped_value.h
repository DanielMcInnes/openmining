#ifndef copy_mapped_value_h
#define copy_mapped_value_h

// standard library includes
#include <string>

// boost includes

// Qt includes
#include <QStringList>
//#include <QString>

// my includes
//#include "utils/utils.h"

//class QStringList;

namespace utils
{
QString valueForKey(const QStringList& args, const char* key);
QString valueForKey(const QStringList& args, const char* key, const char* caller);

  bool copy_mapped_value(const QStringList& args, const std::string& key, QString& dest);
  bool copy_mapped_value(const QStringList& args, const std::string& key, std::string& dest);
  bool copy_mapped_value(const QStringList& args, const char* key,        std::string& dest);
  bool copy_mapped_value(const QStringList& args, const char* key,        int32_t& dest);
  bool copy_mapped_value(const QStringList& args, const char* key,        uint32_t& dest);
  bool copy_mapped_value(const QStringList& args, const char* key,        float& dest);

}
#endif

