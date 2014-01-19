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
#include "utils/utils.h"

using namespace std;
using namespace Qwt3D;
using namespace utils;


Plot::Plot(QStringList& args, Longitudes& longitudes) : m_longitudes(longitudes)
{
  uint32_t coarseness = 0;
  float xscale = 1, yscale = 1, zscale = 1;

  setTitle("A Simple SurfacePlot Demonstration");

  copy_mapped_value(args, "-coarseness", coarseness) || Exit("Error! -coarseness not specified", -1);  
  copy_mapped_value(args, "-xscale", xscale);
  copy_mapped_value(args, "-yscale", yscale);
  copy_mapped_value(args, "-zscale", zscale);
  
  Rosenbrock rosenbrock(this, longitudes, coarseness);
  
  rosenbrock.setMesh(41,31); // x, y. How finely we slice the x and y domains.
  //rosenbrock.setMesh(longitudes.m_extremities.m_minlong, longitudes.m_extremities.m_maxlong); 

  cout << "calling setDomain(" << 
    longitudes.m_extremities.m_minlong << "," <<  
    longitudes.m_extremities.m_maxlong << "," <<  
    longitudes.m_extremities.m_minlat << "," <<  
    longitudes.m_extremities.m_maxlat << "," <<  
    longitudes.m_extremities.m_minel << "," <<
    longitudes.m_extremities.m_maxel <<
     ")" <<
    endl;
  rosenbrock.setDomain(longitudes.m_extremities.m_minlong, longitudes.m_extremities.m_maxlong, longitudes.m_extremities.m_minlat, longitudes.m_extremities.m_maxlat ); // xmin, xmax, ymin, ymax
  rosenbrock.setMinZ(longitudes.m_extremities.m_minel);
  rosenbrock.setMaxZ(longitudes.m_extremities.m_maxel);
  
  cout << "calling create() " << endl;
  rosenbrock.create();

  cout << "calling setRotation() " << endl;
  setRotation(30,0,15);
  cout << "calling setScale(" << xscale << ", " << yscale << ", " << zscale << ")" << endl;
  setScale(xscale,yscale,zscale);
  cout << "calling setRotation() " << endl;
  setShift(0.15,0,0);
  cout << "calling setRotation() " << endl;
  setZoom(0.9);
  cout << "calling setRotation() " << endl;

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
}


