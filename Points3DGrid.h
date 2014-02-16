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
#include "utils/utils.h"
#include "utils/load.h"
#include "utils/save.h"
#include "utils/contains_key.h"
template<class TGridDataContainer, class TSqlDataContainer>
class Points3DGrid : public Points3D
{
private:
  TGridDataContainer m_gridData; // interpolated subset of m_sqlQueryPoints. Much smaller. Gets built once and then cached.
  TSqlDataContainer m_sqlQueryPoints; // big data structure, only restored if m_gridData cannot be restored from local cache file. Gets built once from remote db and then cached on local disk.
  bool Points3DGrid_dbg = false;
  const char* cachefile = "Points3DGrid.cachefile";

public:
  Points3DGrid(const QStringList& args) : m_sqlQueryPoints(args)
  {
    //if (utils::load(this, CLASS))
    if (utils::load(this, cachefile))
    {
      std::cout << FN <<   " loaded object from file '" << cachefile << "'." << std::endl;
    }
    else
    {
      m_sqlQueryPoints.init(args);
    }
  
    if (utils::contains_key(args, "--points3dgrid-dbg")) 
    {
      std::cout << "Points3DGrid_dbg = true" << std::endl;
      Points3DGrid_dbg = true;
    }
  }

  void saveIfUpdated()
  {
    std::cout << FN << "...." << cachefile ;
    //utils::saveIfUpdated(this, CLASS);
    utils::saveIfUpdated(this, "Points3DGrid.cachefile");
    std::cout << ".finished" << std::endl;
  }

  bool getZ(const utils::Rectangle_t& rectangle, zcoordinate32_t& elevation)
  {
    bool retval = false;
    xcoordinate32_t longitude = rectangle.xCentre();
    y_coordinate32_t  latitude  = rectangle.yCentre();
    try
    {
      elevation = m_gridData.at(longitude).at(latitude);
      retval = true;
    }
    catch (...) // this will happen once for every point in the grid. Once the answer has been calculated, the result is cached to ram, and then to disk for subsequent executions of the program. Next time the program is run, all elevations are restored from the local cache file to m_gridData. This code will not run again until the local cache file is deleted, or new grid points are plotted.
    {
      m_sqlQueryPoints.getZ(rectangle, elevation);
      if (Points3DGrid_dbg) std::cout << FN << " catch (...) m_sqlQueryPoints.getZ(" << rectangle << ") returns " << elevation << std::endl;
      m_gridData[longitude][latitude] = elevation; // save our interpolated gps location in RAM. Later on we will save it to disk.
      m_changesNotSaved = true;
    }
    if (Points3DGrid_dbg) std::cout << FN << ": elevation " << elevation << std::endl;
    return retval;
  }

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

//typedef Points3DGrid<xyzcoordinates32_t, Points3DSqlQuery> points3dgrid32_t;
typedef Points3DGrid<xyzcoordinates32_t, points3DSqlQuery_t> points3dgrid32_t;

#endif
