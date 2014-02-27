// boost #includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>


//my includes
#include "Point3D.h"


bool Point3D::inside(const Cube& cube) const
{
  bool retval = false;

  if (
    (m_x > cube.m_minx) &&
    (m_x < cube.m_maxx) &&
    (m_y > cube.m_miny) &&
    (m_y < cube.m_maxy) &&
    (m_z > cube.m_minz) &&
    (m_z < cube.m_maxz)
  )
  {
    retval = true;
  }
  else
  {
    //cout << FN << "Invalid location! " << toString() << endl;
  }
  return (retval);
}
