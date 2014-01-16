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

#ifndef LOCATION_H
#define LOCATION_H

// standard library #includes
#include <string>
#include <iostream> // cout
#include <algorithm> // min_element(...)
#include <time.h>

// boost #includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>

// Qt #includes
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QVariant> // needed for QSqlQuery

// my #includes
#include "mytypes.h"
#include "utils.h"
#include "database.h"
#include "cube.h"

//class Cube;

class Location
{
public:
  friend class boost::serialization::access;
  Location(const latitude_t& latitude, const longitude_t& longitude, const elevation_t& elevation);
  Location();
  bool inside(const Cube& cube);

  latitude_t m_latitude;	// -116788254 = 116.788254 degrees south
  longitude_t m_longitude;//, m_maxlat;	// 543654588 = 54.3654588 degrees east
  elevation_t m_elevation; 	// 10889 = 108.89m above mean sea level (geoid)
  //bool min_latitude(Location& i, Location& j) { return (i.m_latitude < j.m_latitude);}
  std::string toString(void) const;

private:
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & m_latitude;
    ar & m_longitude;
    ar & m_elevation;
    Q_UNUSED(version);
  }
};

bool min_latitude(const Location& i, const Location& j);
bool min_longitude(const Location& i, const Location& j);
bool min_elevation(const Location& i, const Location& j);

class Locations
{
public:
  Locations(const QStringList& args);

  friend class boost::serialization::access;
  Cube m_validXYZ;
  static uint32_t m_numInvalidLocations;
  uint32_t m_dbRowCount, m_dbNumRows;
  std::vector<Location> m_locations;
  // make a map of all longitudes recorded for a given latitude.
  std::string m_filename;

  void print(void);
  void build();
  void build(QSqlQuery& query);
  void build(QString& str);
  bool load(const QStringList& args);
  void save();

  //elevation_t elevation(const latitude_t& latitude, const longitude_t& longitude);

private:
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & m_validXYZ;
    ar & m_numInvalidLocations;
    ar & m_locations;
    Q_UNUSED(version);
  }
  QSqlQuery m_query;
  const char* m_key = "--locations-filename";
};

bool isValidLocation(const Location& loc, const latitude_t& minlat, const latitude_t& maxlat, const longitude_t& minlong, const longitude_t& maxlong, const elevation_t& minel, const elevation_t& maxel);

#endif
