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


// boost includes

// Qt includes
#include <QGuiApplication>

// my includes
#include "modelview.h"
#include "database.h"
#include "location.h"
#include "utils.h"
#include "simpleplot.h"
#include "elevation.h"

using namespace std;
using namespace utils;

// sample data for ravensworth:
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
  string time1 = "Start time: " + timestamp();
  cout << FN << time1 << std::endl;
  QApplication app(argc, argv);
  QStringList args = QCoreApplication::arguments();
  Database db(args);

  Longitudes longitudes(args);
  longitudes.load(args);
  cout << FN << "built longitudes:" << timestamp() << endl;
  //longitudes.print();

/*  longitude_t lo = 543669354;
  latitude_t la = -116767356;
  cout << FN << "Longitudes test: lo: " << lo << " la: " << la << " elev: " << longitudes[lo][la] << endl;
  longitudes.print();
*/
      Plot plot(args, longitudes);
      plot.resize(800,600);
      plot.show();
      return app.exec();
  std::string time2 = "Locations built. " + timestamp();
  std::string time3 = "Finished. " + timestamp();

  std::cout << FN << time1 << std::endl;
  std::cout << FN << time2 << std::endl;
  std::cout << FN << time3 << std::endl;

  ModelView view;
  view.resize(800,600);
  view.show();
  return app.exec();
}
