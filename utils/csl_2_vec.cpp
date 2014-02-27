using namespace std;

// Qt includes
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>

namespace utils{
  void csl_2_vec(QSqlQuery& query, int index, const char* separator, std::vector<int>& vec, int& val)
  {
    QStringList stringList = query.value(index).toString().split(separator);
    for (auto iter : stringList) {
      val += iter.toInt();
      vec.push_back(val);        
    }
  }
} //namespace
