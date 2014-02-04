#ifndef ThreeDPoints_h
#define ThreeDPoints_h

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
#include "utils/Rectangle.h"

class Points3DSqlQuery : public Points3D
{
public:
  Points3DSqlQuery(const QStringList& args);
  Points3DSqlQuery();
  //Points3DSqlQuery(const std::string& sqlQuery);
  bool getZ(const utils::Rectangle_t& rectangle, z_t& elevation) ;
  bool getZ(const utils::Rectangle_t& rectangle, z_t& elevation, bool& retval) ;
  void init(const QStringList& args);
  void build(QString& query);
  void build(QSqlQuery& query);
  friend class boost::serialization::access;

private:
  Cube m_boundary;
  //std::vector<Point3D> m_locations;
  longitudes_t m_sqlQueryPoints; // interpolated subset of m_sqlQueryPoints. Much smaller. Gets built once and then cached.
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
};

#endif

