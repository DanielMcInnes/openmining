#ifndef csl_2_vec_h
#define csl_2_vec_h

namespace utils
{
  void csl_2_vec(QSqlQuery& query, int index, const char* separator, std::vector<int>& vec, int& val);
}

#endif
