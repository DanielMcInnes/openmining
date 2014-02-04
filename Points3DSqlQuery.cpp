//std includes
#include <iostream>
#include <vector>

// Qt includes

// my includes
#include "Points3DSqlQuery.h"
#include "utils/get_mapped_value.h"
#include "utils/utils.h" 		// FN
#include "utils/same_size.h"
#include "utils/update_progress.h"
#include "utils/percent.h"
#include "utils/load.h"
#include "utils/save.h"

using namespace std;
using namespace utils;

Points3DSqlQuery::Points3DSqlQuery() : m_numInvalidLocations(0), m_dbRowCount(0), m_dbNumRows(0) {}
Points3DSqlQuery::Points3DSqlQuery(const QStringList& args) : m_numInvalidLocations(0), m_dbRowCount(0), m_dbNumRows(0)
{
  m_boundary.init(args);
}

/*
Points3DSqlQuery::Points3DSqlQuery(const std::string& sqlQuery)
{
}
*/
bool Points3DSqlQuery::getZ(const utils::Rectangle_t& rectangle, z_t& elevation, bool& retval)
{
  retval = getZ(rectangle, elevation);
  return (retval);
} 

bool Points3DSqlQuery::getZ(const utils::Rectangle_t& rectangle, z_t& elevation) 
{
  bool retval = false;
  auto lower_longitude = m_sqlQueryPoints.lower_bound(rectangle.xMin());
  auto upper_longitude = m_sqlQueryPoints.upper_bound(rectangle.xMax());

  for (auto iter_1 = lower_longitude; iter_1 != upper_longitude; ++iter_1)
  {
    auto latitudes = iter_1->second;
    auto lower_latitude = latitudes.lower_bound(rectangle.yMin());
    auto upper_latitude = latitudes.upper_bound(rectangle.yMax());
    for (auto iter_2 = lower_latitude; iter_2 != upper_latitude; ++iter_2)
    {
      if (iter_2->second > elevation) 
      {
        retval = true;
        elevation = iter_2->second; 
      }
    }
  }
  return retval;
}

void Points3DSqlQuery::init(const QStringList& args)
{
  if (load(this, CLASS))
  {
    cout << FN <<   " loaded object from file '" << CLASS << "'." << endl;
  }
  else
  {
    cout << FN << "building object from db query: " << endl;
    QString str, strCountQuery = "SELECT COUNT(*) from shift_gps;";
    copy_mapped_value(args, "--locations-count-query", strCountQuery);

    QSqlQuery countQuery(strCountQuery);
    while (countQuery.next())
    {
      m_dbNumRows = countQuery.value(0).toUInt();
    }
    cout << FN << " finished count query, m_dbNumRows == " << m_dbNumRows << endl;

    const char* key = "--locations-query";
    bool result = (utils::copy_mapped_value(args, key, str));
    if (result == false) 
    {
      usage();
      Exit("ERROR! no query specified in the command line arguments via --locations-query", -1);
    }
    build(str);

    utils::save(*this, CLASS);
  }

  if (contains_key(args, "--exitafterlocationsquery")) exit (0);
}

void Points3DSqlQuery::build(QString& str)
{
  QSqlQuery query(str);
  build(query);
}

void Points3DSqlQuery::build(QSqlQuery& query)
{
  uint32_t progress = 0;
  query.setForwardOnly(true);
  cout << FN << ": started" << endl;

  QSqlQuery countQuery(QString("SELECT COUNT(*) FROM shift_gps;"));
  while (countQuery.next())
  {
    m_dbNumRows = countQuery.value(0).toUInt();
  }

  while (query.next()) 
  {
    cout << FN << ": 1" << endl;
    int32_t latitude = 0, longitude = 0, elevation = 0;
    vector<int32_t> vecLatitudes, vecLongitudes, vecElevations;

    csl_2_vec(query, 0, ",", vecLatitudes,  latitude);
    csl_2_vec(query, 1, ",", vecLongitudes, longitude);
    csl_2_vec(query, 2, ",", vecElevations, elevation);
    if( ! same_size(vecLatitudes, vecLongitudes, vecElevations))
    {
      cerr << "ERROR! db table has different numbers of latitudes, longitudes, and elevations" << endl;
      exit (-1);
    }
      
    for (size_t i = 0; i < vecLatitudes.size(); i++) {
      Point3D point(vecLatitudes[i], vecLongitudes[i], vecElevations[i]);
      if (point.inside(m_boundary))
      {
        cout << FN << ": location within bounds" << endl;
        m_sqlQueryPoints[point.m_x][point.m_y] = point.m_z;        
      }
      else
      {
        cout << FN << ": location outside bounds" << endl;
        m_numInvalidLocations++;
      }
    }
    update_progress(percent(m_dbRowCount++,m_dbNumRows), progress, FN);
  }
  cout << FN << ": finished" << endl;
}
