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

  //              simpleplot.cpp
#ifndef simpleplot_h
#define simpleplot_h

// standard libs
#include <math.h>

// Qt libs
#include <qapplication.h>
#include <qwt3d_surfaceplot.h>
#include <qwt3d_function.h>

// my includes
#include "elevation.h"
#include "utils.h"

class Rosenbrock : public Qwt3D::Function
{
public:
  Rosenbrock(Qwt3D::SurfacePlot* pw, Longitudes& longitudes, uint32_t coarseness) : Function(pw), m_longitudes(longitudes), m_coarseness(coarseness) 
  {
  }

  Longitudes& m_longitudes;

  double operator()(double x, double y)
  {
    //return log((1-x)*(1-x) + 100 * (y - x*x)*(y - x*x)) / 8;

    /*
    longitude_t lo = x;
    latitude_t la = y;
    return m_longitudes.getElevation(lo,la); 
    */

    return m_longitudes.getElevation(x,y, m_coarseness);
  }
  uint32_t m_coarseness;
};


class Plot : public Qwt3D::SurfacePlot
{
public:
  Plot(QStringList& args, Longitudes& longitudes);
  Longitudes& m_longitudes;
};

#endif
