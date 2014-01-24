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
#include <fstream>
#include <string>
#include <stdexcept> // std::out_of_range

// boost includes

// Qt includes
#include <QString>
#include <QStringList>

// my includes
#include "elevation.h"
#include "utils/copy_mapped_value.h"
#include "utils/utils.h"
#include "utils/load.h"
#include "utils/save.h"
#include "mytypes.h"  // elevation_t
#include "location.h"

using namespace std;
using namespace utils;

uint32_t Longitudes_dbg = false;
uint32_t Latitudes_dbg = false;

Latitudes emptyLatitudes;
longitudes_t dummy_longitudes = {{0, emptyLatitudes}};
latitudes_t dummy_latitudes = {{0,0}};
elevation_t dummy_elevation = 0;

Longitudes::Longitudes(QStringList& args) : m_filename("longitudes.cache"), m_args(args), changesNotSaved(false)
{
  copy_mapped_value(args, m_key, m_filename);
  if (contains_key(args, "--latitudes-dbg")) Latitudes_dbg = true;
  if (contains_key(args, "--longitudes-dbg")) Longitudes_dbg = true;
}

bool Longitudes::saveIfUpdated()
{
  bool retval = false;
  if( changesNotSaved )
  {
    retval = true;
    cout << FN << " - saving..." << endl;
    save(*this, m_filename);
    cout << FN << " - finished." << endl;
    changesNotSaved = false;
  }
  return retval;
}

bool Longitudes::load()
{
  bool retval = false;
  if (utils::load(this, m_filename))
  {
    retval = true;
  }
  else
  {
    cout << FN << "building 'Longitudes' object from 'Locations' object" << endl;
    Locations locations(m_args); 
    if ((retval = locations.load(m_args)) == true) 
    {
      cout << FN << "copying 'Locations' data to 'Longitudes' object " << endl;
      *this = locations;
      utils::save(*this, m_filename); 
    }
  }
  if (contains_key(m_args, "-exitafterbuildinglongitudes")) exit (0);

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
  return m_longitudes[longitude];
}

elevation_t& Latitudes::operator[](const latitude_t& latitude)
{
  if (Latitudes_dbg) std::cout << FN <<  "calling Latitudes::operator[" << latitude << "], returning '" << m_latitudes[latitude] << "'."<< std::endl;
  return m_latitudes[latitude];
}
 
double Longitudes::getElevation(double& longitude, double& latitude, const uint32_t coarseness)
{
  double elevation = INT32_MIN;
  try
  {
    elevation = m_plottedLongitudes.at(longitude).m_latitudes.at(latitude);
    
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
        if (iter_2->second > elevation) 
        {
          elevation = iter_2->second; 
        }
      }
    }
    m_plottedLongitudes[longitude][latitude] = elevation; // save our interpolated gps location in RAM. Later on we will save it to disk.
    changesNotSaved = true;
  }
  if (Latitudes_dbg) cout << FN << ": returning " << elevation << endl;    
  return elevation;
}

Latitudes::Latitudes()
{
}
