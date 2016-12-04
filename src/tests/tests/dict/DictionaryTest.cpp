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
#include "DictionaryTest.h"

#include <yasc/dict/Dictionary.h>

#include <sstream>

namespace yasc {
namespace tests {

// Register test suite
CPPUNIT_TEST_SUITE_REGISTRATION(DictionaryTest);

void DictionaryTest::AddValidEntityTest()
{
    // Create dictionary with 3 letters alphabet
    const std::set<char> alphabet = { 'a', 'b', 'c' };

    ::yasc::dict::Dictionary dict(alphabet);

    CheckAddEntity(dict);
}

void DictionaryTest::AddInvalidEntityTest()
{
    // Create dictionary with 3 letters alphabet
    const std::set<char> alphabet = { 'a', 'b', 'c' };

    ::yasc::dict::Dictionary dict(alphabet);

    // Adding an invalid entry (contains z, which is not in the distionary) should return false
    CPPUNIT_ASSERT(!dict.safeAddEntry("abbza"));

    // Check tree consistency
    std::ostringstream expectedOutput;
    expectedOutput << " -> []" << std::endl;
    CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict.toString());
}

void DictionaryTest::AddEntityComplexTest(const Steps step)
{
    // Create dictionary with 3 letters alphabet
    const std::set<char> alphabet = { 'a', 'b', 'c' };

    ::yasc::dict::Dictionary dict(alphabet);

    const std::ostringstream expectedOutput = CheckAddEntityComplex(dict, step);

    if (step != Steps::AddInvalidEntry)
    {
        return;
    }

    // === Adding an invalid entry (contains z, which is not in the distionary) should return false
    CPPUNIT_ASSERT(!dict.safeAddEntry("abbza"));

    // Check tree consistency (should not have changed since we use safeAddEntry)
    CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict.toString());
}

void DictionaryTest::CheckEntityExistenceTest()
{
    // Create dictionary with 3 letters alphabet
    const std::set<char> alphabet = { 'a', 'b', 'c' };

    ::yasc::dict::Dictionary dict(alphabet);

    CheckEntityExistence(dict);
}

} // namespace tests
} // namespace yasc
