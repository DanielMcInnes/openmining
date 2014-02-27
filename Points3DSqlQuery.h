#ifndef points3dsqlquery_h
#define points3dsqlquery_h

// standard library includes
#include <string>
#include <vector>

// boost #includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>

// Qt includes
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>

//my includes
#include "mytypes.h"
#include "Point3D.h"
#include "Points3D.h"
#include "Cube.h"
#include "utils/utils.h" 		// FN
#include "utils/copy_mapped_value.h"
#include "utils/get_mapped_value.h"
#include "utils/Rectangle.h"
#include "utils/usage.h"
#include "utils/Exit.h"
#include "utils/load.h"
#include "utils/save.h"
#include "utils/contains_key.h"
#include "utils/update_progress.h"
#include "utils/percent.h"
#include "utils/same_size.h"
#include "utils/csl_2_vec.h"
#include "Database.h"

template <class T1>
class Points3DSqlQuery : public Points3D
{
private:
  Cube m_boundary;
  T1 m_sqlQueryPoints; // interpolated subset of m_sqlQueryPoints. Much smaller. Gets built once and then cached.
  uint32_t m_numInvalidLocations, m_dbRowCount, m_dbNumRows;

  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & m_sqlQueryPoints;
    Q_UNUSED(version);
  }
  QStringList m_args;

  // not until gcc 4.8.2! 
  // const char* m_cachefile = "Points3DGrid.m_cachefile";
  const char* m_cachefile;

public:
  Points3DSqlQuery(const QStringList& args) : m_numInvalidLocations(0), m_dbRowCount(0), m_dbNumRows(0), m_args(args), m_cachefile("Points3DGrid.m_cachefile")
  {
    m_boundary.init(args);
  }
  Points3DSqlQuery() : m_numInvalidLocations(0), m_dbRowCount(0), m_dbNumRows(0) {}
  bool getZ(const utils::Rectangle_t& rectangle, zcoordinate32_t& elevation)
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

  bool getZ(const utils::Rectangle_t& rectangle, zcoordinate32_t& elevation, bool& retval)
  {
    retval = getZ(rectangle, elevation);
    return (retval);
  } 

  void init(const QStringList& args)
  {
    //if (utils::load(this, CLASS))
    if (utils::load(this, m_cachefile))
    {
      std::cout << FN <<   " loaded object from file '" << m_cachefile << "'." << std::endl;
    }
    else
    {
      std::cout << FN << "building object from db query: " << std::endl;
      QString str, strCountQuery = "SELECT COUNT(*) from shift_gps;";
      utils::copy_mapped_value(args, "--locations-count-query", strCountQuery);
  
      Database db(args);
      QSqlQuery countQuery(strCountQuery);
      while (countQuery.next())
      {
        m_dbNumRows = countQuery.value(0).toUInt();
      }
      //std::cout << FN << " finished count query, m_dbNumRows == " << m_dbNumRows << std::endl;
  
      const char* key = "--locations-query";
      bool result = (utils::copy_mapped_value(args, key, str));
      if (result == false) 
      {
        utils::usage();
        utils::Exit("ERROR! no query specified in the command line arguments via --locations-query", -1);
      }
      build(str);
  
      //utils::save(*this, CLASS);
      utils::save(*this, "Points3DSqlQuery.m_cachefile");
    }
  
    if (utils::contains_key(args, "--exitafterlocationsquery")) exit (0);
  }

  void build(QString& str)
  {
    QSqlQuery query(str);
    build(query);
  }

  void build(QSqlQuery& query)
  {
    uint32_t progress = 0;
    query.setForwardOnly(true);
    //std::cout << FN << ": started" << std::endl;

    QSqlQuery countQuery(QString("SELECT COUNT(*) FROM shift_gps;"));
    while (countQuery.next())
    {
      m_dbNumRows = countQuery.value(0).toUInt();
    }

    while (query.next()) 
    {
      int32_t latitude = 0, longitude = 0, elevation = 0;
      std::vector<int32_t> vecLatitudes, vecLongitudes, vecElevations;

      utils::csl_2_vec(query, 0, ",", vecLatitudes,  latitude);
      utils::csl_2_vec(query, 1, ",", vecLongitudes, longitude);
      utils::csl_2_vec(query, 2, ",", vecElevations, elevation);
      if( ! utils::same_size(vecLatitudes, vecLongitudes, vecElevations))
      {
        std::cerr << "ERROR! db table has different numbers of latitudes, longitudes, and elevations" << std::endl;
        exit (-1);
      }
      
      for (size_t i = 0; i < vecLatitudes.size(); i++) {
        Point3D point(vecLatitudes[i], vecLongitudes[i], vecElevations[i]);
        if (point.inside(m_boundary))
        {
          //utils::contains_key(m_args, FN) && std::cout << FN << ": location within bounds" << std::endl;
          m_sqlQueryPoints[point.m_x][point.m_y] = point.m_z;        
        }
        else
        {
          //std::cout << FN << ": location outside bounds" << std::endl;
          m_numInvalidLocations++;
        }
      }
      utils::update_progress(utils::percent(m_dbRowCount++,m_dbNumRows), progress, FN);
    }
    //std::cout << FN << ": finished" << std::endl;
  }
  friend class boost::serialization::access;

};

typedef Points3DSqlQuery<xyzcoordinates32_t> points3DSqlQuery_t;
#endif

