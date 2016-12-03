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

# ifdef __GNUC__
// Disable CppUnit warnings (third-party)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wsuggest-override"
# endif

#include <cppunit/Exception.h>
#include <cppunit/TestFailure.h>

# ifdef __GNUC__
// Restore warnings
#  pragma GCC diagnostic pop
# endif

#include <iostream>

namespace yasc {
namespace tests {
namespace helpers {
namespace cppunit {

YascTestRunner::YascTestRunner()
    : _resultCollector(new CppUnit::TestResultCollector())
{
    _eventManager.addListener(_resultCollector.get());
}

/**
 * @brief Runs all added tests
 * @return true if all tests passed, false otherwise
 */
bool YascTestRunner::runTests()
{
    run(_eventManager, "");

    // Print failures
    for (const CppUnit::TestFailure *failure : _resultCollector->failures())
    {
        // Print error location
        const CppUnit::SourceLine locationObject = failure->sourceLine();
        std::string location = "at unknown location";
        if (locationObject.isValid())
        {
            location = "in file " + locationObject.fileName() + " at line " + std::to_string(locationObject.lineNumber());
        }

        std::cout << "Failure occured " << location << std::endl;

        // Print error content
        CppUnit::Exception* error = failure->thrownException();

        std::cout << error->message().shortDescription() << std::endl;
        std::cout << error->message().details();
    }

    return _resultCollector->wasSuccessful();
}

} // namespace cppunit
} // namespace helpers
} // namespace tests
} // namespace yasc
