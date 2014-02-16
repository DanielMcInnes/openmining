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
#include <QString>
#include <QStringList>

// my includes
#include "utils/Rectangle.h"
#include "Points3DGrid.h"

class GridMappingFunction : public Qwt3D::Function
{
public:
  GridMappingFunction(Qwt3D::SurfacePlot* pw, points3dgrid32_t& locations, utils::Rectangle_t& grid) : Function(pw), m_locations(locations), m_grid(grid)
  {
  }

  points3dgrid32_t& m_locations;
  double operator()(double x, double y);
  utils::Rectangle_t m_grid;
}
;

class Plot : public Qwt3D::SurfacePlot
{
QStringList& m_args;
public:
  Plot(QStringList& args, Cube& cube, points3dgrid32_t& locations);
  double (*funcptr)(double x, double y);
};

#endif
