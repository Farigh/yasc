/*
 * This file is part of the YASC project (https://github.com/Farigh/yasc)
 * Copyright (C) 2016  David GARCIN <david.garcin.pro[at]gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _DATA_MANAGER_H_
# define _DATA_MANAGER_H_

# include <string>

namespace yasc {
namespace tests {

class DataManager
{
public:
    static void setResourcePath(const std::string& resourcePath);
    static std::string getResourcePath();

private:
    // This is a singleton handler, it should not be instanciated
    DataManager() = delete;
    ~DataManager() = delete;

    static std::string _resourcePath;
};

} // namespace tests
} // namespace yasc

#endif /* !_DATA_MANAGER_H_ */
