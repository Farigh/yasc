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
#include "YascTestRunner.h"

namespace yasc {
namespace tests {
namespace helpers {
namespace cppunit {

YascTestRunner::YascTestRunner()
    : _resultCollector(new CppUnit::TestResultCollector())
{
    _eventManager.addListener(_resultCollector);
}

YascTestRunner::~YascTestRunner()
{
    // Cleanup memory
    delete _resultCollector;
}

/**
 * @brief Runs all added tests
 * @return true if all tests passed, false otherwise
 */
bool YascTestRunner::runTests()
{
    run(_eventManager, "");
    return _resultCollector->wasSuccessful();
}

} // namespace cppunit
} // namespace helpers
} // namespace tests
} // namespace yasc
