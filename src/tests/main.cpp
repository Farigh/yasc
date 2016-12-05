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
#include <tests/DataManager.h>

#include <yasc/utils/YascGetopts.h>

#include <cstdint>
#include <iostream>
#include <sstream>

int main (int argc, char* argv[])
{
    std::int32_t returnValue = 0;
    bool runTestOptionFound = false;
    std::string runTestOptionArg;
    ::yasc::tests::helpers::cppunit::YascTestSuiteManager unitTestRunner;

    ::yasc::utils::YascGetopts getOpts;

    // Register all options
    getOpts.registerHelpOption();

    getOpts.registerOption('l',
                           "list-tests",
                           [&]()
                           {
                               std::cout << unitTestRunner.listAllTests() << std::endl;
                               std::exit(0);
                           },
                           "List all available test-suites and there tests");

    getOpts.registerArgBasedOption('t',
                                   "run-test",
                                   [&](const std::string& testName)
                                   {
                                       runTestOptionFound = true;
                                       runTestOptionArg = testName;
                                   },
                                   "Run the selected test by it's name",
                                   "test_name");

    getOpts.registerArgBasedOption('r',
                                   "resource-path",
                                   [&](const std::string& resourcePath)
                                   {
                                       ::yasc::tests::DataManager::setResourcePath(resourcePath);
                                   },
                                   "Set the resource path",
                                   "resource_path",
                                   true);

    // Process options
    const std::list<std::string> remainingArgs = getOpts.parseArgs(argc, argv);
    if (!remainingArgs.empty())
    {
        std::ostringstream errorMsgFormater;
        errorMsgFormater << "Error: unknown arguments:" << std::endl;
        for (const std::string& arg : remainingArgs)
        {
            errorMsgFormater << "'" << arg << "' ";
        }
        getOpts.PrintErrorMessage(errorMsgFormater.str());

        returnValue = 1;
    }
    else if (runTestOptionFound)
    {
        returnValue = unitTestRunner.runTestByName(runTestOptionArg);
    }
    else
    {
        returnValue = unitTestRunner.runAllTests();
    }

    return returnValue;
}
