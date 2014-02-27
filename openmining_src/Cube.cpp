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
#include <cstdint>

// boost #includes


// Qt includes
#include <QStringList>
#include <QString>

// my includes
#include "Cube.h"
#include "utils/utils.h"
#include "utils/find_or_exit.h"
#include "utils/copy_mapped_value.h"

using namespace std;
using namespace utils;

Cube::Cube() : m_miny(INT32_MAX), m_maxy(INT32_MIN), m_minx(INT32_MAX), m_maxx(INT32_MIN), m_minz(INT32_MAX), m_maxz(INT32_MIN), m_sidelength(0) {}

bool Cube::init(const QStringList& args)
{
  if (copy_mapped_value(args, "-sidelength", m_sidelength))
  { 
    cout << "sidelength specified: "<< m_sidelength << endl;
  }
  else
  {
    cout << "sidelength not specified." << endl;
  }
  m_minx = find_or_exit(args, "-minlong", FN);
  m_miny = find_or_exit(args, "-minlat",  FN);
  m_minz = find_or_exit(args, "-minel",   FN);
  m_maxx = find_or_exit(args, "-maxlong", FN);
  m_maxy = find_or_exit(args, "-maxlat",  FN);
  m_maxz = find_or_exit(args, "-maxel",   FN);

  return(true);
}

void Cube::Print() const
{
  cout << FN << "m_miny = " << m_miny << endl;
  cout << FN << "m_maxy = " << m_maxy << endl;
  cout << FN << "m_minx = " << m_minx << endl;
  cout << FN << "m_maxx = " << m_maxx << endl;
  cout << FN << "m_minz = " << m_minz << endl;
  cout << FN << "m_maxz = " << m_maxz << endl;
}

void Cube::UpdateMinMax(const xcoordinate32_t& longitude, const y_coordinate32_t& latitude, const zcoordinate32_t& elevation)
{
  if (latitude  < m_miny) { m_miny 	= latitude;  }
  if (latitude  > m_maxy) { m_maxy 	= latitude;  }
  if (longitude < m_minx){ m_minx = longitude; }
  if (longitude > m_maxx){ m_maxx = longitude; }
  if (elevation < m_minz)  { m_minz 	= elevation; }
  if (elevation > m_maxz)  { m_maxz 	= elevation; }
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
  os << " m_minx: " << cube.m_minx << ", m_maxx: " << cube.m_maxx << ", m_miny: " << cube.m_miny << ", m_maxy: " <<  cube.m_maxy << ", m_minz: " <<  cube.m_minz << ", m_maxz: " << cube.m_maxz <<  ", ranges: " << cube.ranges();
  return os;
}

