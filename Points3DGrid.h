#ifndef Points3DGrid_h
#define Points3DGrid_h

//std includes
#include <string>

// boost #includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>

//Qt includes
#include <QString>
#include <QStringList>

//my includes
#include "mytypes.h"
#include "Points3D.h"
#include "Points3DSqlQuery.h"
#include "utils/Rectangle.h"

class Points3DGrid : public Points3D
{
public:
  Points3DGrid(const QStringList& args);
  void saveIfUpdated();
  bool getZ(const utils::Rectangle_t& rectangle, z_t& elevation) ;
  Points3DSqlQuery m_sqlQueryPoints; // big data structure, only restored if m_gridData cannot be restored from local cache file. Gets built once from remote db and then cached on local disk.
  longitudes_t m_gridData; // interpolated subset of m_sqlQueryPoints. Much smaller. Gets built once and then cached.

  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & m_gridData;
    Q_UNUSED(version);
  }
};

#endif
