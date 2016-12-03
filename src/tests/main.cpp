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
#include <helpers/cppunit/YascTestSuiteManager.h>

#include <cstdint>
#include <iostream>

int main (int argc, char* argv[])
{
    bool returnValue = 1;
    ::yasc::tests::helpers::cppunit::YascTestSuiteManager unitTestRunner;
    if (argc > 2)
    {
        std::cerr << "Error: too many aruments" << std::endl;
        std::cout << "Usage: " << argv[0] << " [test_name]" << std::endl;
    }
    // Print tests
    else if ((argc == 2) && (std::string(argv[1]) == "-l"))
    {
        std::cout << unitTestRunner.listAllTests() << std::endl;
    }
    // Run tests
    else
    {
        // Select specific test if asked for
        if (argc == 2)
        {
            returnValue = unitTestRunner.runTestByName(argv[1]);
        }
        else
        {
            returnValue = unitTestRunner.runAllTests();
        }
    }

    return returnValue;
}
