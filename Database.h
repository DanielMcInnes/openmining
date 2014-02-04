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

#ifndef DATABASE_H
#define DATABASE_H

// standard library #includes
#include <iostream>

// Qt #includes
#include <QtSql/qsqldatabase.h>
#include <QStringList>

// my includes


class Database
{
public:
  Database(const QStringList& args); 
  bool m_initialised;
  QSqlDatabase m_db;

private:
/*
configure: error: Building GCC requires GMP 4.2+, MPFR 2.4.0+ and MPC 0.8.0+.
Try the --with-gmp, --with-mpfr and/or --with-mpc options to specify
their locations.  Source code for these libraries can be found at
their respective hosting sites as well as at
ftp://gcc.gnu.org/pub/gcc/infrastructure/.  See also
http://gcc.gnu.org/install/prerequisites.html for additional info.  If
you obtained GMP, MPFR and/or MPC from a vendor distribution package,
make sure that you have installed both the libraries and the header
files.  They may be located in separate packages.

apt-get install lib32gmp-dev libmpfr-dev libmpc-dev gcc-multilib
*/
 /// \ThirdPartyDep The version of gcc in the ubuntu 12.04 repositories won't work, You need at least gcc version 4.8.1 to build non-static data member initialisers
  std::vector<std::string> m_requiredArgs = { "-host", "-database", "-username", "-password" };
};

#endif
