// std includes

// my includes
#include "Points3DGrid.h"
#include "Points3DSqlQuery.h"
#include "utils/utils.h"
#include "utils/load.h"
#include "utils/save.h"

using namespace std;
using namespace utils;

bool Points3DGrid_dbg = false;

Points3DGrid::Points3DGrid(const QStringList& args) : m_sqlQueryPoints(args)
{
  if (load(this, CLASS))
  {
    cout << FN <<   " loaded object from file '" << CLASS << "'." << endl;
  }
  else
  {
    m_sqlQueryPoints.init(args);
  }
  
  if (contains_key(args, "--points3dgrid-dbg")) 
  {
    cout << "Points3DGrid_dbg = true" << endl;
    Points3DGrid_dbg = true;
  }
}

void Points3DGrid::saveIfUpdated()
{
  cout << FN << "...." << CLASS;
  utils::saveIfUpdated(this, CLASS);
  cout << ".finished" << endl;
}

bool Points3DGrid::getZ(const Rectangle_t& rectangle, z_t& elevation) 
{
  bool retval = false;
  longitude_t longitude = rectangle.xCentre();
  latitude_t  latitude  = rectangle.yCentre();
  try
  {
    elevation = m_gridData.at(longitude).at(latitude);
    retval = true;
  }
  catch (...) // this will happen once for every point in the grid. Once the answer has been calculated, the result is cached to ram, and then to disk for subsequent executions of the program. Next time the program is run, all elevations are restored from the local cache file to m_gridData. This code will not run again until the local cache file is deleted, or new grid points are plotted.
  {
    m_sqlQueryPoints.getZ(rectangle, elevation);
    cout << FN << " catch (...) m_sqlQueryPoints.getZ(" << rectangle << ") returns " << elevation << endl;
    m_gridData[longitude][latitude] = elevation; // save our interpolated gps location in RAM. Later on we will save it to disk.
    m_changesNotSaved = true;
  }
  if (Points3DGrid_dbg) cout << FN << ": elevation " << elevation << endl;    
  return retval;
}


