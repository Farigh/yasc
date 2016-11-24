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
#ifdef __GNUC__
// Disable CppUnit warnings (third-party)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wsuggest-override"
#endif

# include <cppunit/extensions/TestFactoryRegistry.h>
# include <cppunit/ui/text/TestRunner.h>

#ifdef __GNUC__
// Restore warnings
# pragma GCC diagnostic pop
#endif

#include <cstdint>
#include <iostream>

int main (int argc, char* argv[])
{
    // Get all registered tests
    CppUnit::Test* allTests = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    bool returnValue = 1;
    if (argc > 2)
    {
        std::cerr << "Error: too many aruments" << std::endl;
        std::cout << "Usage: " << argv[0] << " [test_name]" << std::endl;
    }
    // Print tests
    else if ((argc == 2) && (std::string(argv[1]) == "-l"))
    {
        // allTests->getName() == All Tests

        std::int32_t testSuiteCount = allTests->getChildTestCount();
        if (testSuiteCount == 0)
        {
            std::cout << "No test found" << std::endl;
        }

        for (std::int32_t i = 0; i < testSuiteCount; ++i)
        {
            CppUnit::Test* testSuite = allTests->getChildTestAt(i);
            std::cout << "Test suite: " << testSuite->getName() << std::endl;

            std::int32_t testCount = testSuite->getChildTestCount();
            for (std::int32_t j = 0; j < testCount; ++j)
            {
                std::cout << "   Test: " << testSuite->getChildTestAt(j)->getName() << std::endl;
            }
        }
    }
    // Run tests
    else
    {
        // Select specific test if asked for
        if (argc == 2)
        {
            allTests = allTests->findTest(argv[1]);
        }

        CppUnit::TextUi::TestRunner testRunner;
        testRunner.addTest(allTests);

        // Return 0 if run succeeded, 1 otherwise
        returnValue = !testRunner.run("", false);
    }

    return returnValue;
}
