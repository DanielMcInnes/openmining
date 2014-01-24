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

// standard libarary includes
#include <iostream>

// boost includes

// Qt includes
#include <QString>
#include <QStringList>

// my includes
#include "database.h"
#include "utils/utils.h" // FN
#include "utils/Exit.h"
//#include "utils/check_argv.h"
#include "utils/get_mapped_value.h"

using namespace std;
using namespace utils;


Database::Database(const QStringList& args) : m_initialised(false)
{
  m_db = QSqlDatabase::addDatabase("QPSQL");

  /*check_argv(args,FN, m_requiredArgs);
  for (auto str : m_requiredArgs)
  {
    if (get_mapped_value(args, str.c_str()) == "")
    {
      Exit(str, -1);
    }
  }*/
  m_db.setHostName     (get_mapped_value(args,"-host", FN));
  m_db.setDatabaseName (get_mapped_value(args,"-database", FN));
  m_db.setUserName     (get_mapped_value(args,"-username", FN));
  m_db.setPassword     (get_mapped_value(args,"-password", FN));

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
