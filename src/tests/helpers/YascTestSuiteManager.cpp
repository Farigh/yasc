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
#include "YascTestSuiteManager.h"

#include "YascTestRunner.h"

#ifdef __GNUC__
// Disable CppUnit warnings (third-party)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wsuggest-override"
#endif

# include <cppunit/extensions/TestFactoryRegistry.h>

#ifdef __GNUC__
// Restore warnings
# pragma GCC diagnostic pop
#endif

#include <sstream>

namespace tests {
namespace helpers {

YascTestSuiteManager::YascTestSuiteManager()
{
    // Get all registered tests
    _allTests = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
}

/**
 * @brief Lists all test-suites and their tests
 * @return The printable test-suite list
 */
std::string YascTestSuiteManager::listAllTests() const
{
    std::ostringstream resultFormater;
    const std::int32_t testSuiteCount = _allTests->getChildTestCount();
    if (testSuiteCount == 0)
    {
        resultFormater << "No test found !" << std::endl;
    }

    for (std::int32_t i = 0; i < testSuiteCount; ++i)
    {
        const CppUnit::Test* testSuite = _allTests->getChildTestAt(i);
        resultFormater << "Test suite: " << testSuite->getName() << std::endl;

        const std::int32_t testCount = testSuite->getChildTestCount();
        for (std::int32_t j = 0; j < testCount; ++j)
        {
            resultFormater << "   Test: " << testSuite->getChildTestAt(j)->getName() << std::endl;
        }
    }

    return resultFormater.str();
}

/**
 * @brief Runs all tests from the given @p tests test-suite
 * @return true if all tests passed, false otherwise
 */
static bool runCppUnitTest(CppUnit::Test* tests)
{
    YascTestRunner testRunner;
    testRunner.addTest(tests);

    // Return 0 if run succeeded, 1 otherwise
    return !testRunner.runTests();
}

/**
 * @brief Runs all registered tests
 * @return true if all tests passed, false otherwise
 */
bool YascTestSuiteManager::runAllTests() const
{
    return runCppUnitTest(_allTests);
}

/**
 * @brief Runs the test named @p testName
 * @param testName The name of the test to run as listed by @ref listAllTests
 * @return true if all tests passed and the @p testName test exists, false otherwise
 */
bool YascTestSuiteManager::runTestByName(const std::string& testName) const
{
    return runCppUnitTest(_allTests->findTest(testName));
}

} // namespace tests
} // namespace helpers
