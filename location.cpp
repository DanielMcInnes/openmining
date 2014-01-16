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

#include "location.h"
#include <QSqlQuery>
#include <QString>
#include <QStringList>
#include <iostream>
#include <fstream>
#include "utils.h"

using namespace std;
using namespace utils;
uint32_t Locations_dbg = 0;

Location::Location()
{
  if (Locations_dbg) cout << FN << "constructor: long: " << m_longitude << " lat: " << m_latitude << " elev: " << m_elevation << endl;
}

Location::Location(const latitude_t& latitude, const longitude_t& longitude, const elevation_t& elevation) : m_latitude(latitude), m_longitude(longitude), m_elevation(elevation)
{
  //cout << FN << "constructor: long: " << longitude << " lat: " << latitude << " elev: " << elevation << endl;
}

bool Location::inside(const Cube& cube)
{
  bool retval = false;
  if (Locations_dbg)
  {
    if  (m_latitude  < cube.m_minlat)	{	cout << FN << "m_latitude: " << m_latitude << " < minlat: " << cube.m_minlat << endl;	}
    if  (m_latitude  > cube.m_maxlat)	{ 	cout << FN << "m_latitude: " <<  m_latitude << " > maxlat: " << cube.m_maxlat << endl;	}
    if  (m_longitude < cube.m_minlong) 	{	cout << FN << "m_longitude: " << m_longitude << " < minlong: " << cube.m_minlong << endl;}
    if  (m_longitude > cube.m_maxlong) 	{	cout << FN << "m_longitude: " << m_longitude << " > maxlong: " << cube.m_maxlong << endl;}
    if  (m_elevation < cube.m_minel) 	{	cout << FN << "m_elevation: " << m_elevation << " < minel: " << cube.m_minel << endl;	}
    if  (m_elevation > cube.m_maxel)	{	cout << FN << "m_elevation: " << m_elevation << " > maxel: " << cube.m_maxel << endl;	}
  }
  if (
    (m_latitude  > cube.m_minlat) &&
    (m_latitude  < cube.m_maxlat) &&
    (m_longitude > cube.m_minlong) &&
    (m_longitude < cube.m_maxlong) &&
    (m_elevation > cube.m_minel) &&
    (m_elevation < cube.m_maxel)
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

uint32_t Locations::m_numInvalidLocations = 0;

bool min_latitude(const Location& i, const Location& j) 
{
  return (i.m_latitude < j.m_latitude); 
}

bool min_longitude(const Location& i, const Location& j) 
{ 
  return (i.m_longitude < j.m_longitude); 
}

bool min_elevation(const Location& i, const Location& j) 
{
  return (i.m_elevation < j.m_elevation); 
}

Locations::Locations(const QStringList& args) : m_dbRowCount(0), m_dbNumRows(0)
{
  exit_if_no_cachefile_specified(args, m_key, m_filename, FN );
  copy_mapped_value(args, "--locations-dbg", Locations_dbg);
}

bool Locations::load(const QStringList& args)
{
  if (utils::load(this,m_filename))
  {
    cout << FN <<   " loaded object from file '" << m_filename << "'." << endl;
  }

  else
  {
    cout << FN << "building object from db query: " << endl;

    m_validXYZ.Load(args);

    QString str, strCountQuery;
    if (copy_mapped_value(args, "--locations-count-query", strCountQuery))
    {
      QSqlQuery countQuery(strCountQuery);
      while (countQuery.next())
      {
        //QStringList stringList = query.value(index).toString().split(separator);
        m_dbNumRows = countQuery.value(0).toUInt();
        // QStringList stringList = query.value(index).toString().split(separator);
      }
    }
    copy_mapped_value(args, "--locations-query", str) || Exit("ERROR! no query specified in the command line arguments via --locations-query", -1);
    build(str);

    utils::save(*this, m_filename);
  }

  if (containsKey(args, "--exitafterlocationsquery")) exit (0);
  return (true);
}
//void save(){}

void Locations::build(QString& str)
{  
  QSqlQuery query(str);
  build(query);
}

void Locations::build(QSqlQuery& query)
{
  static uint32_t progress = 0;
  query.setForwardOnly(true);
  while (query.next()) 
  {
    int32_t latitude = 0, longitude = 0, elevation = 0;
    vector<int32_t> vecLatitudes, veclongitudes_t, vecLongitudes;

    csl_2_vec(query, 0, ",", vecLatitudes,  latitude);
    csl_2_vec(query, 1, ",", veclongitudes_t, longitude);
    csl_2_vec(query, 2, ",", vecLongitudes, elevation);
    if( ! sameSize(vecLatitudes, veclongitudes_t, vecLongitudes))
    {
      cerr << "ERROR! db table has different numbers of latitudes, longitudes, and longitudes" << endl;
      exit (-1);
    }
      
    for (size_t i = 0; i < vecLatitudes.size(); i++) {
      Location location (vecLatitudes[i], veclongitudes_t[i], vecLongitudes[i]);
      if (location.inside(m_validXYZ))
      {
        m_locations.push_back(location);        
      }
      else
      {
        m_numInvalidLocations++;
      }
    }
    update_progress(percent(m_dbRowCount++,m_dbNumRows), progress, FN);
  }
}

void Locations::print(void) {
  cout << FN << __func__ << endl;
  m_validXYZ.Print();
  cout << FN << "m_numInvalidLocations = " << m_numInvalidLocations << endl;

  if (m_locations.size() > 0)
  {
    cout << FN << "Latitude:  min = " << min_element(begin(m_locations), end(m_locations), min_latitude )->m_latitude  << endl;  
    cout << FN << "Latitude:  max = " << max_element(begin(m_locations), end(m_locations), min_latitude )->m_latitude  << endl;  
    cout << FN << "Longitude: min = " << min_element(begin(m_locations), end(m_locations), min_longitude)->m_longitude << endl;  
    cout << FN << "Longitude: max = " << max_element(begin(m_locations), end(m_locations), min_longitude)->m_longitude << endl;  
    cout << FN << "Elevation: min = " << min_element(begin(m_locations), end(m_locations), min_elevation)->m_elevation << endl;  
    cout << FN << "Elevation: max = " << max_element(begin(m_locations), end(m_locations), min_elevation)->m_elevation << endl;  
  }
  cout << FN << __func__ << " m_locations.size() == " << m_locations.size() << endl;
  cout << FN << __func__ << " m_longitudes.size() == " << m_locations.size() << endl;
}
std::string Location::toString(void) const
{
  std::string str;
  str = "Latitude: " + std::to_string(m_latitude) + " Longitude: " + std::to_string(m_longitude) + " Elevation: " + std::to_string(m_elevation);
  return (str);
}
