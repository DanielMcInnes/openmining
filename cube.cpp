/*
  Copyright 2014 Daniel McInnes

  This file is part of OpenMining.

  OpenMining is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenMining is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenMining.  If not, see <http://www.gnu.org/licenses/>.

*/


// standard library includes
#include <iostream>
#include <sstream>
#include <string>

// boost #includes


// Qt includes
#include <QStringList>
#include <QString>

// my includes
#include "cube.h"
#include "utils/utils.h"
#include "utils/find_or_exit.h"
#include "utils/copy_mapped_value.h"


using namespace std;
using namespace utils;

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
  m_minlat  = find_or_exit(args, "-minlat",  FN);
  m_maxlat  = find_or_exit(args, "-maxlat",  FN);
  m_minlong = find_or_exit(args, "-minlong", FN);
  m_maxlong = find_or_exit(args, "-maxlong", FN);
  m_minel   = find_or_exit(args, "-minel",   FN);
  m_maxel   = find_or_exit(args, "-maxel",   FN);
  return(true);
}

void Cube::Print() const
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

string Cube::ranges() const
{
  ostringstream oss;
  oss << "longitude range: " << longitudeRange() << 
  " latitude range: " << latitudeRange() <<
  " elevation range: " << elevationRange();
  return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Cube& cube)
{
  os << " m_minlong: " << cube.m_minlong << ", m_maxlong: " << cube.m_maxlong << ", m_minlat: " << cube.m_minlat << ", m_maxlat: " <<  cube.m_maxlat << ", m_minel: " <<  cube.m_minel << ", m_maxel: " << cube.m_maxel <<  ", ranges: " << cube.ranges();
  return os;
}






