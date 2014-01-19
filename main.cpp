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
Qt
graphviz
*/

// boost includes

// Qt includes
#include <QGuiApplication>

// my includes
#include "modelview.h"
#include "database.h"
#include "location.h"
#include "utils/utils.h"
#include "simpleplot.h"
#include "elevation.h"

using namespace std;
using namespace utils;

/*! \page pagerequirements Requirements
\tableofcontents
\section sec Non-functional requirements:
\subsection subsectiondeps Dependency Management
In general, all dependencies shall be documented and kept to the bare minimum required to satisfy the requirements.

\subsection ssaff Affordability 
The system shall be developed in a manner calculated to minimize total cost over the entire project lifespan (development, installation, maintenance).

\subsection ssaud Auditability 
- bidirectional mapping: every functional requirement shall be mapped to its associated automated unit tests, so that it is easy to see which unit tests apply to a given requirement. Likewise, a unit test may be used by more than one requirement, so each unit test shall be mapped to its associated requirements.
- There shall be bidirectional mapping between every artifact in the system.
- System artifacts include: functional requirements, design artifacts, use cases, source and header files, free functions(not in a class), classes, enums, #defines, global variables, static variables. 
- every requirement shall document the following:
- functional dependencies (eg. application depends on Qt, postgres, etc.)
- build time dependencies (eg. header files, libraries etc.)
- every requirement's dependency on other requirements shall be recorded and mapped.
- all downloadable packages shall have a version number, which changes every time a new version is released.
	
\subsection sssim Simplicity 
- The project shall adhere to 'lesscode' principles.

\subsection ssreu Reusability
- Functions shall be as short as possible to facilitate code reuse. 

\subsection sstes Testability 
- every functional requirement shall have an associated automated unit test.

\subsection ssrel Reliability 
- the project shall never be released with known bugs. Issues shall be resolved before new features are developed, as per Spolsky's 'dogfood' arguments.

\subsection sseff Efficiency 
- the project shall consume the minimum amount of computer resources required to fulfil requirements.

\subsection ssbui Buildability
- every source file shall include every header file required for successful compilation, ie. if main.cpp depends on a.h and b.h, main.cpp shall explicitly include a.h and b.h, even if a.h includes b.h. This shall be proved by compiling every single source file into a standalone library.
- Compilation dependencies shall be mapped and minimized.
- Source files shall not include files that are not needed.
- Library dependencies shall be documented.

\subsection ssind Installability
- the system shall minimize the effort required to configure and use the software. Ideally, zero site specific configuration shall be required.
- the software shall utilize standard packaging, such as '.deb' packages for ubuntu and '.msi' or '.exe' for windows applications.
- see "http://www.producingoss.com/en/getting-started.html" for guidelines.

\subsection ssusa Usability
- Make it as simple as possible, then simplify some more. 
- Every request for technical assistance shall be recorded and categorised, and a 'heat map' developed to highlight problem areas. The ideal system would be so easy to use that nobody every needed help to use it. If you get asked to explain something, it is not simple enough.

\subsection sssel Self documenting 
- the source code shall contain the requirements documentation.
- the source code shall generate html documentation using doxygen

\subsection ssmai Maintainability
- All discussions shall be public unless there is a specific need for privacy.

\subsection ssdep Dependency Management
- Every 3rd party library that is required shall be documented, along with the license applicable to the library.

\subsection ssdesDesign Constraints
Follow the recommendations in "Beyond the C++ Standard Library: An introduction to boost"
- use smart_pointer library (shared_pointer, scoped_ptr, intrusive_ptr, weak_ptr) or similar whenever objects are created dynamically (ie. via 'new'). 
- scoped_ptr: calls 'delete' for you. Non-copyable.
- shared_ptr: reference counted pointer, deletes pointee when reference counts goes to 0.
- weak_ptr: observer of a shared_ptr, does not imply ownership. If the underlying object gets deleted, wek_ptr gets set to null. Avoids dangling pointer problem.

Casting & Conversions: The boost extensions allow you to unambiguously state your intent.
- polymorphic_cast: always throws an exception if the conversion fails. (dynamic_cast throws if a reference conversion fails, but doesn't throw if a ptr conversion fails). If a failed polymorphic pointer cast is not an error, you should use dynamic_cast).
- polymorphic_downcast: debug build: dynamic_cast. Release build: static_cast. Gives a performance increase for release builds. This is an optimization, and should only be used after profiling demonstrates the need for it. 
- numeric_cast: std::numeric_limits<int>::max(), ...::(min).
- lexical_cast:

\subsection sscod Coding Standard
- whenever a type conversion is performed between different numeric types, make the conversion safe by using numeric_cast.
- whenever a type conversion is performed to or from string types, make the conversion safe by using lexical_cast.
- prefer boost::checked_delete to delete. This adds zero runtime overhead.
- measure object size for each build.

\subsection ssfun Functional Requirements
Features:
- builds a 3D scale model of the mine surface, which changes over time as material is added / removed.
- (planned) Allows replaying historical gps data. THe user can see trucks, shovels etc moving around the mine.
- (planned) Allows the assignment of trucks to shovels, and all other operations permitted by MineOPS.
**/


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
