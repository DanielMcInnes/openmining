// Qt includes
#include <QString>
#include <QStringList>

namespace utils
{
  bool contains_key(const QStringList& args, const char* key)
  {
    bool retval = false;
    if (args.indexOf(key) != -1) retval = true;
    return (retval);
  }
}
