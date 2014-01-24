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
#include "elevation.h" // Longitudes object

class Cube;
class Longitudes;
typedef double (Longitudes::*fp_t)(double&, double&, uint32_t);

class GridMappingFunction : public Qwt3D::Function
{
public:
  GridMappingFunction(Qwt3D::SurfacePlot* pw, Longitudes& locations, uint32_t coarseness) : Function(pw), m_locations(locations), m_coarseness(coarseness) 
  {
  }

  Longitudes& m_locations;
  double operator()(double x, double y);
  uint32_t m_coarseness;
};

class Plot : public Qwt3D::SurfacePlot
{
public:
  Plot(QStringList& args, Cube& cube, Longitudes& locations);
  double (*funcptr)(double x, double y);
};

#endif
