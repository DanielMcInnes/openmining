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

#ifndef cube_h
#define cube_h

// standard library includes
#include <iostream>
#include <sstream>
#include <string>

// boost #includes
#include <boost/archive/text_oarchive.hpp>

// Qt includes
#include <QStringList>

// my includes
#include "mytypes.h"

class Cube
{
public:
  //const member functions
  void Print() const;
  longitude_t longitudeRange() const { return m_maxx - m_minx; }
  latitude_t latitudeRange()   const { return m_maxy - m_miny; } 
  elevation_t elevationRange() const { return m_maxz - m_minz; }
  std::string ranges() const;

  // non-const member functions
  Cube();
  bool init(const QStringList& args);
  void UpdateMinMax(const longitude_t& longitude, const latitude_t& latitude, const elevation_t& elevation);

  // member variables
  latitude_t m_miny, m_maxy;
  longitude_t m_minx, m_maxx;
  elevation_t m_minz, m_maxz;
  int32_t m_sidelength;

  // friends
  friend std::ostream& operator<<(std::ostream& os, const Cube& cube);
  friend class boost::serialization::access;
 
private:
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & m_miny;
    ar & m_maxy;
    ar & m_minx;
    ar & m_maxx;
    ar & m_minz;
    ar & m_maxz;
    Q_UNUSED(version);
  }
};

std::ostream& operator<<(std::ostream& os, const Cube& cube);

#endif
