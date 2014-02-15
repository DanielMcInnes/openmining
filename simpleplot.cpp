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
#include "utils/Exit.h"
#include "utils/copy_mapped_value.h"
#include "utils/Rectangle.h"
#include "utils/save.h"
#include "utils/utils.h"

using namespace std;
using namespace Qwt3D;
using namespace utils;

Plot::Plot(QStringList& args, Cube& boundary, points3dgrid32_t& locations)
{
  uint32_t columns = 40, rows = 30;
  xcoordinate32_t grid_width  = 0;
  y_coordinate32_t  grid_height = 0;
  float xscale = 1, yscale = 1, zscale = 1;

  setTitle("A Simple SurfacePlot Demonstration");
  copy_mapped_value(args, "-xscale", xscale);
  copy_mapped_value(args, "-yscale", yscale);
  copy_mapped_value(args, "-zscale", zscale);
  copy_mapped_value(args, "-columns", columns);
  copy_mapped_value(args, "-rows", rows);
  if (columns < 1) Exit("Error! Invalid number of columns specified via '-columns'", -1);
  if (rows < 1)    Exit("Error! Invalid number of rows specified via '-rows'"      , -1);
  
  grid_width  = boundary.longitudeRange() / columns;
  grid_height = boundary.latitudeRange() / rows;
  Rectangle_t grid(grid_width, grid_height);
  
  cout << "Grid width  = " << grid_width  << " units of latitude."  << endl;
  cout << "Grid height = " << grid_height << " units of longitude." << endl;
  
  GridMappingFunction gridMappingFunction(this, locations, grid);
  
  gridMappingFunction.setMesh(columns+1,rows+1); // x, y. How finely we slice the x and y domains. Gridlines = columns + 1, rows + 1.

  cout << "calling setDomain(" << boundary << ")" << endl;
  gridMappingFunction.setDomain(boundary.m_minx, boundary.m_maxx, boundary.m_miny, boundary.m_maxy ); // xmin, xmax, ymin, ymax
  gridMappingFunction.setMinZ(boundary.m_minz);
  gridMappingFunction.setMaxZ(boundary.m_maxz);
  
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

  setCoordinateStyle(BOX);

  updateData();
  cout << "calling updateGL() " << endl;
  updateGL();
}

double GridMappingFunction::operator()(double x, double y)
{

//  return log((1-x)*(1-x) + 100 * (y - x*x)*(y - x*x)) / 8;


  int32_t longitude = x;
  int32_t latitude = y;
  m_grid.setCentre(longitude, latitude);
  zcoordinate32_t elevation = 0;

  m_locations.getZ(m_grid, elevation);
  double retval = elevation;
  cout << FN << longitude << ", " << latitude << ": " << retval << ", " << endl;
  return retval;
}
