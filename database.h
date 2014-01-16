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

#ifndef DATABASE_H
#define DATABASE_H
// standard library #includes
#include <iostream>

// Qt #includes
#include <QtSql/qsqldatabase.h>
#include <QStringList>

class Database
{
public:
  Database(const QStringList& args); 
  bool m_initialised;
  QSqlDatabase m_db;

private:
};

#endif
