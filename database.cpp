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

#include <iostream>
#include <QString>
#include <QStringList>
#include "database.h"
#include "utils/utils.h"

using namespace std;
using namespace utils;

Database::Database(const QStringList& args) : m_initialised(false)
{
  m_db = QSqlDatabase::addDatabase("QPSQL");

  m_db.setHostName     (valueForKey(args,"-host"));
  m_db.setDatabaseName (valueForKey(args,"-database"));
  m_db.setUserName     (valueForKey(args,"-username"));
  m_db.setPassword     (valueForKey(args,"-password"));

  if (m_db.open() == 0) {
    std::cout << FN << "failed to open db" << std::endl;
    exit (-1);
  }
  else
  {
    m_initialised = true;
    std::cout << FN << "db opened ok" << std::endl;
    QStringList tables = m_db.tables();

    for (auto str : tables)
    {
      //std::cout << FN << "table: " << str.toStdString() << std::endl;
    }
  }
}
