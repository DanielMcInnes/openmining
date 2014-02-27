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

#ifndef find_or_return_default_h
#define find_or_return_default_h

#include <iostream>

#include "contains.h"

namespace utils
{
  template <class Tcontainer, class Tkey>
  typename Tcontainer::mapped_type& find_or_return_default(Tcontainer& container, const Tkey& key, Tcontainer& default_return_value)
  {
    if (contains(container, key)) 
    { 
      std::cout << FN << " found matching value." << std::endl;
      return container.find(key)->second; 
    }
    else
    {
      std::cout << FN << " no matching value found." << std::endl;
      return default_return_value.begin()->second;
    }
  }
}

#endif
