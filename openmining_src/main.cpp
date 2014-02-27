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

/*
Dependencies:
Qt 5.2
graphviz
*/

// boost includes

// Qt includes
#include <QGuiApplication>

// my includes
#include "modelview.h"
#include "utils/utils.h"
#include "simpleplot.h"
#include "utils/Exit.h"
#include "Points3DGrid.h"

using namespace std;
using namespace utils;

void runchecks();
// sample data
// latitude :    -116,745,993
// latitude min: -117,000,000
// latitude max: -116,000,000
// longitude :    543,642,828
// longitude min: 543,000,000
// longitude max: 544,000,000
// elevation:
// elevation min: 0m
//elevation max:  100000 (1000m)

int main(int argc, char *argv[])
{
  runchecks();
  QApplication app(argc, argv);
  cout << FN << "Start time: " << timestamp() << endl;
  QStringList args = QCoreApplication::arguments();
  points3dgrid32_t grid(args);
  Cube boundary;
  boundary.init(args);
  Plot plot(args, boundary, grid);
  plot.resize(800,600);
  plot.show();
  grid.saveIfUpdated();
  return app.exec();
}

void runchecks()
{
// check that exceptions are enabled.
  bool caught = false;
  vector<int32_t> vec(10);

  try { 
    vec.at(20) = 100;
  }
  catch(out_of_range& oor)
  {
    caught = true;
  }
  if (!caught) { Exit(FN, -1); }
}
