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
#include <iostream>
#include <fstream>
#include <string>

// boost includes

// Qt includes
#include <QString>
#include <QStringList>

// my includes
#include "elevation.h"
#include "utils.h"
#include "mytypes.h"  // elevation_t
#include "find_or_return_default.h"

using namespace std;
using namespace utils;

uint32_t Longitudes_dbg = 0;
uint32_t Latitudes_dbg = 0;

Latitudes emptyLatitudes;
//typedef std::map<latitude_t, elevation_t> latitudes_t;
longitudes_t dummy_longitudes = {{0, emptyLatitudes}};
latitudes_t dummy_latitudes = {{0,0}};
elevation_t dummy_elevation = 0;
Longitudes::Longitudes(QStringList& args)
{
  exit_if_no_cachefile_specified(args, m_key, m_filename, FN );
  copy_mapped_value(args, "--longitudes-dbg", Longitudes_dbg);
}

bool Longitudes::load(const QStringList& args)
{
  bool retval = false;
  if (utils::load(this, m_filename))
  {
    retval = true;
  }
  else
  {
    cout << FN << "building 'Longitudes' object from 'Locations' object" << endl;
    Locations locations(args); 
    if ((retval = locations.load(args)) == true) 
    {
      cout << FN << "copying 'Locations' data to 'Longitudes' object " << endl;
      *this = locations;
      save(*this, m_filename); 
    }
  }
  if (containsKey(args, "-exitafterbuildinglongitudes")) exit (0);

  return (retval);
}

void Longitudes::print()
{
  cout << FN << "longitudes_t.size() == " << m_longitudes.size() << endl;

  for (auto iter_1 : m_longitudes)
  {
    for (auto iter_2 : iter_1.second.m_latitudes)
    {
      cout << "long: " << iter_1.first << " lat: " << iter_2.first << " elev: " << iter_2.second  << endl;
    }
  }
}

Longitudes& Longitudes::operator=(const Locations& locations)
{
  cout << FN << "calling Longitudes::operator=" << endl;
  for (auto it = locations.m_locations.begin(); it != locations.m_locations.end(); ++it)
  {
    m_extremities.UpdateMinMax(it->m_longitude, it->m_latitude, it->m_elevation);
    m_longitudes[it->m_longitude][it->m_latitude] = it->m_elevation;
    //cout << FN << "long: " << it->m_longitude << " lat: " << it->m_latitude << " elev: " << it->m_elevation  << " = " << m_longitudes[it->m_longitude][it->m_latitude] << endl << endl;
  }
  cout << FN  << " finished." << endl;
  return(*this);
}


Latitudes& Longitudes::operator[](const longitude_t& longitude)
{
  if (Longitudes_dbg) cout << FN << "calling Longitudes::operator[" << longitude << "]" << endl;
  //return(find_or_return_default(m_longitudes, longitude, dummy_longitudes));
  return m_longitudes[longitude];
}

elevation_t& Latitudes::operator[](const latitude_t& latitude)
{
  if (Latitudes_dbg) std::cout << FN <<  "calling Latitudes::operator[" << latitude << "], returning '" << m_latitudes[latitude] << "'."<< std::endl;
  //return (find_or_return_default(m_latitudes, latitude, dummy_latitudes));
  return m_latitudes[latitude];
}
 
elevation_t Longitudes::getElevation(const longitude_t& longitude, const latitude_t& latitude, const uint32_t coarseness)
{
  elevation_t elevation = INT32_MIN;
  try
  {
    elevation = m_longitudes.at(longitude).m_latitudes.at(latitude);
    
    if (Latitudes_dbg) cout << FN << ": found value at :" << longitude << ", " << latitude << endl;    
  }
  catch (...) // this will happen more often than not. Search for an elevation in the surrounding area
  {
    auto lower_longitude = m_longitudes.lower_bound(longitude - coarseness);
    auto upper_longitude = m_longitudes.upper_bound(longitude + coarseness);

    for (auto iter_1 = lower_longitude; iter_1 != upper_longitude; ++iter_1)
    {
      auto latitudes = iter_1->second.m_latitudes;
      auto lower_latitude = latitudes.lower_bound(latitude - coarseness);
      auto upper_latitude = latitudes.upper_bound(latitude + coarseness);
      for (auto iter_2 = lower_latitude; iter_2 != upper_latitude; ++iter_2)
      {
        if (iter_2->second > elevation) { elevation = iter_2->second; }
      }
    }
    if (Latitudes_dbg) cout << FN << ": no value found at :" << longitude << ", " << latitude << endl;    
  }
  if (Latitudes_dbg) cout << FN << ": returning " << elevation << endl;    
  return elevation;
}

Latitudes::Latitudes()
{
//  copy_mapped_value(args, "--latitudes-dbg", Latitudes_dbg);
}
