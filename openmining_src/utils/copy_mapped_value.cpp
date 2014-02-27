// standard library includes
#include <string>

// boost includes

// Qt includes
//#include <QString>
//#include <QStringList>

// my includes
#include "utils.h"
#include "copy_mapped_value.h"

using namespace std;

namespace utils
{
  QString valueForKey(const QStringList& args, const char* key)
  {
    int index = args.indexOf(key);
    QString str = "";
    if ((index != -1) && (args.size() >= index +1)) 
      str = (args.at(args.indexOf(key) + 1));
    return (str);
  }

  QString valueForKey(const QStringList& args, const char* key, const char* caller)
  {
    QString str = valueForKey(args, key);
    if (str == "") 
    {
      cerr << "ERROR! " << caller << ": " << key << " not specified " << endl;
      exit (-1);
    }

    return (str);
  }  // variant 'A'
  bool copy_mapped_value(const QStringList& args, const std::string& key, QString& dest)
  {
    QString value = valueForKey(args, key.c_str());
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

}
