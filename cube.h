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

#ifndef cube_h
#define cube_h

// standard library includes

// boost #includes
#include <boost/archive/text_oarchive.hpp>

// Qt includes
#include <QStringList>

// my includes
#include "mytypes.h"

class Cube
{
public:
  Cube();
  friend class boost::serialization::access;
  bool Load(const QStringList& args);
  void Print();
  void UpdateMinMax(const longitude_t& longitude, const latitude_t& latitude, const elevation_t& elevation);
  latitude_t m_minlat, m_maxlat;
  longitude_t m_minlong, m_maxlong;
  elevation_t m_minel, m_maxel;
  int32_t m_sidelength;

private:
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & m_minlat;
    ar & m_maxlat;
    ar & m_minlong;
    ar & m_maxlong;
    ar & m_minel;
    ar & m_maxel;
    Q_UNUSED(version);
  }
};

#endif
