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

//-----------------------------------------------------------------
  //              simpleplot.cpp
  //
  //      A simple example which shows how to use SurfacePlot
  //-----------------------------------------------------------------

#include <math.h>
#include <iostream>

#include <qapplication.h>
#include <qwt3d_surfaceplot.h>
#include <qwt3d_function.h>

// my includes
#include "simpleplot.h"
#include "location.h"  
#include "utils/Exit.h"
#include "utils/copy_mapped_value.h"

using namespace std;
using namespace Qwt3D;
using namespace utils;

Plot::Plot(QStringList& args, Cube& cube, Longitudes& locations)
{
  uint32_t columns = 41, rows = 31, plotx = 800, ploty = 600;
  longitude_t column_width = 0;
  float xscale = 1, yscale = 1, zscale = 1;

  setTitle("A Simple SurfacePlot Demonstration");
  copy_mapped_value(args, "-xscale", xscale);
  copy_mapped_value(args, "-yscale", yscale);
  copy_mapped_value(args, "-zscale", zscale);
  copy_mapped_value(args, "--plotsize-x", plotx);
  copy_mapped_value(args, "--plotsize-y", ploty);
  copy_mapped_value(args, "-columns", columns);
  copy_mapped_value(args, "-rows", rows);
  if (columns < 1) Exit("Error! Invalid number of columns specified via '-columns'", -1);
  if (rows < 1)    Exit("Error! Invalid number of rows specified via '-rows'"      , -1);
  
  column_width = cube.longitudeRange() / columns;
  cout << "Column width = " << column_width << " units of latitude." << endl;
  
  GridMappingFunction gridMappingFunction(this, locations, (column_width / 2));
  
  gridMappingFunction.setMesh(columns+1,rows+1); // x, y. How finely we slice the x and y domains. Gridlines = columns + 1, rows + 1.

  cout << "calling setDomain(" << cube << ")" << endl;
  gridMappingFunction.setDomain(cube.m_minlong, cube.m_maxlong, cube.m_minlat, cube.m_maxlat ); // xmin, xmax, ymin, ymax
  gridMappingFunction.setMinZ(cube.m_minel);
  gridMappingFunction.setMaxZ(cube.m_maxel);
  
  cout << "calling create() " << endl;
  gridMappingFunction.create();

  cout << "calling setRotation() " << endl;
  setRotation(30,0,15);
  cout << "calling setScale(" << xscale << ", " << yscale << ", " << zscale << ")" << endl;
  setScale(xscale,yscale,zscale);
  cout << "calling setShift() " << endl;
  setShift(0.15,0,0);
  cout << "calling setZoom() " << endl;
  setZoom(0.9);

  for (unsigned i=0; i!=coordinates()->axes.size(); ++i)
  {
    coordinates()->axes[i].setMajors(7);
    coordinates()->axes[i].setMinors(4);
  }

  coordinates()->axes[X1].setLabelString("x-axis");
  coordinates()->axes[Y1].setLabelString("y-axis");
  coordinates()->axes[Z1].setLabelString(QChar (0x38f)); // Omega - see http://www.unicode.org/charts/

  setCoordinateStyle(BOX);

  updateData();
  cout << "calling updateGL() " << endl;
  updateGL();
  cout << "calling resize() " << endl;
  resize(plotx,ploty);

  cout << "calling locations.saveIfUpdated()";
  locations.saveIfUpdated();
}

double GridMappingFunction::operator()(double x, double y)
{
    //return log((1-x)*(1-x) + 100 * (y - x*x)*(y - x*x)) / 8;

    /*
    longitude_t lo = x;
    latitude_t la = y;
    return m_longitudes.getElevation(lo,la); 
    */

  return m_locations.getElevation(x,y, m_coarseness);
}

