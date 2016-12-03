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
#include "DynamicDictionaryTest.h"

#include <utils/DynamicDictionary.h>

#include <list>
#include <sstream>

namespace yasc {
namespace tests {

// Register test suite
CPPUNIT_TEST_SUITE_REGISTRATION(DynamicDictionaryTest);

void DynamicDictionaryTest::AddEntityTest()
{
    ::yasc::utils::DynamicDictionary dict;

    CheckAddEntity(dict);
}

void DynamicDictionaryTest::AddEntityComplexTest(const Steps step)
{
    ::yasc::utils::DynamicDictionary dict;

    CheckAddEntityComplex(dict, step);
}

void DynamicDictionaryTest::CheckEntityExistenceTest()
{
    ::yasc::utils::DynamicDictionary dict;

    CheckEntityExistence(dict);
}

} // namespace tests
} // namespace yasc
