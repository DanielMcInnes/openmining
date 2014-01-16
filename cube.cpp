/*
  Copyright 2014 Daniel McInnes

  This file is part of NineMops.

  NineMops is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  NineMops is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with NineMops.  If not, see <http://www.gnu.org/licenses/>.

*/


// standard library includes

// boost #includes
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/serialization/map.hpp>


// Qt includes

// my includes
#include "cube.h"
#include "utils.h"


using namespace std;
using utils::copy_mapped_value;

Cube::Cube() : m_minlat(INT32_MAX), m_maxlat(INT32_MIN), m_minlong(INT32_MAX), m_maxlong(INT32_MIN), m_minel(INT32_MAX), m_maxel(INT32_MIN), m_sidelength(0) {}

bool Cube::Load(const QStringList& args)
{
  if (copy_mapped_value(args, "-sidelength", m_sidelength))
  { 
    cout << "sidelength specified: "<< m_sidelength << endl;
  }
  else
  {
    cout << "sidelength not specified." << endl;
  }
  copy_mapped_value(args, "-minlat", m_minlat);
  copy_mapped_value(args, "-maxlat", m_maxlat);
  copy_mapped_value(args, "-minlong", m_minlong);
  copy_mapped_value(args, "-maxlong", m_maxlong);
  copy_mapped_value(args, "-minel", m_minel);
  copy_mapped_value(args, "-maxel", m_maxel);
  return(true);
}

void Cube::Print()
{
  cout << FN << "m_minlat = " << m_minlat << endl;
  cout << FN << "m_maxlat = " << m_maxlat << endl;
  cout << FN << "m_minlong = " << m_minlong << endl;
  cout << FN << "m_maxlong = " << m_maxlong << endl;
  cout << FN << "m_minel = " << m_minel << endl;
  cout << FN << "m_maxel = " << m_maxel << endl;
}

void Cube::UpdateMinMax(const longitude_t& longitude, const latitude_t& latitude, const elevation_t& elevation)
{
  if (latitude  < m_minlat) { m_minlat 	= latitude;  }
  if (latitude  > m_maxlat) { m_maxlat 	= latitude;  }
  if (longitude < m_minlong){ m_minlong = longitude; }
  if (longitude > m_maxlong){ m_maxlong = longitude; }
  if (elevation < m_minel)  { m_minel 	= elevation; }
  if (elevation > m_maxel)  { m_maxel 	= elevation; }
}






