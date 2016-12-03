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

#include <utils/Dictionary.h>

#include <list>
#include <sstream>

namespace yasc {

// Register test suite
CPPUNIT_TEST_SUITE_REGISTRATION(DictionaryTest);

void DictionaryTest::AddValidEntityTest()
{
    // Create dictionary with 3 letters alphabet
    const std::set<char> alphabet = { 'a', 'b', 'c' };

    ::yasc::utils::Dictionary dict(alphabet);

    // Adding a valid entry should return true
    CPPUNIT_ASSERT(dict.addEntry("abbaa"));

    // Check tree consistency
    std::ostringstream expectedOutput;
    expectedOutput << " -> []" << std::endl
                   << " -> a -> b -> b -> a -> a -> []" << std::endl;
    CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict.toString());
}

void DictionaryTest::AddInvalidEntityTest()
{
    // Create dictionary with 3 letters alphabet
    const std::set<char> alphabet = { 'a', 'b', 'c' };

    ::yasc::utils::Dictionary dict(alphabet);

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

    ::yasc::utils::Dictionary dict(alphabet);

    // === Adding a valid entry should return true
    CPPUNIT_ASSERT(dict.addEntry("abbaa"));

    // Check tree consistency
    std::ostringstream expectedOutput;
    expectedOutput << " -> []" << std::endl
                   << " -> a -> b -> b -> a -> a -> []" << std::endl;
    CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict.toString());

    if (step == Steps::AddValidEntry)
    {
        return;
    }

    // === Adding a valid entry twice should return true and the dictionary should remain the same
    CPPUNIT_ASSERT(dict.addEntry("abbaa"));
    CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict.toString());

    if (step == Steps::AddValidEntryTwice)
    {
        return;
    }

    // === Adding an invalid entry (contains z, which is not in the distionary) should return false
    CPPUNIT_ASSERT(!dict.safeAddEntry("abbza"));

    // Check tree consistency (should not have changed since we use safeAddEntry)
    CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict.toString());

    if (step == Steps::AddInvalidEntry)
    {
        return;
    }

    // === Adding an entry with no common prefix
    CPPUNIT_ASSERT(dict.addEntry("bacbac"));

    // Check tree consistency
    std::ostringstream expectedOutput2;
    expectedOutput2 << " -> []" << std::endl
                    << " -> a -> b -> b -> a -> a -> []" << std::endl
                    << " -> b -> a -> c -> b -> a -> c -> []" << std::endl;
    CPPUNIT_ASSERT_EQUAL(expectedOutput2.str(), dict.toString());

    if (step == Steps::AddEntryWithNoCommonPrefix)
    {
        return;
    }

    // === Adding a longer entry with common prefix
    CPPUNIT_ASSERT(dict.addEntry("abbaacc"));

    // Check tree consistency
    std::ostringstream expectedOutput3;
    expectedOutput3 << " -> []" << std::endl
                    << " -> a -> b -> b -> a -> a -> []" << std::endl
                    << "                          -> c -> c -> []" << std::endl
                    << " -> b -> a -> c -> b -> a -> c -> []" << std::endl;
    CPPUNIT_ASSERT_EQUAL(expectedOutput3.str(), dict.toString());

    if (step == Steps::AddLongEntryWithCommonPrefix)
    {
        return;
    }

    // === Adding a shorter entry which is already a prefix
    CPPUNIT_ASSERT(dict.addEntry("abb"));

    // Check tree consistency
    std::ostringstream expectedOutput4;
    expectedOutput4 << " -> []" << std::endl
                    << " -> a -> b -> b -> []" << std::endl
                    << "                -> a -> a -> []" << std::endl
                    << "                          -> c -> c -> []" << std::endl
                    << " -> b -> a -> c -> b -> a -> c -> []" << std::endl;
    CPPUNIT_ASSERT_EQUAL(expectedOutput4.str(), dict.toString());
}

void DictionaryTest::CheckEntityExistenceTest()
{
    // Create dictionary with 3 letters alphabet
    const std::set<char> alphabet = { 'a', 'b', 'c' };

    ::yasc::utils::Dictionary dict(alphabet);

    // === Add some entries to the dictionary
    const std::list<std::string> entries = { "abbaa", "abcba", "acbaabba" };
    for (const std::string& entry : entries)
    {
        dict.addEntry(entry);
    }

    // === Check for existing values
    for (const std::string& entry : entries)
    {
        CPPUNIT_ASSERT(dict.isExistingEntry(entry));
    }

    // Empty string is a valid one
    CPPUNIT_ASSERT(dict.isExistingEntry(""));

    // === Check for unknown entries
    CPPUNIT_ASSERT(!dict.isExistingEntry("aaabccb"));

    // Check with unknown char
    CPPUNIT_ASSERT(!dict.isExistingEntry("jdi"));

    // Check with existing prefix
    for (const std::string& entry : entries)
    {
        CPPUNIT_ASSERT(!dict.isExistingEntry(entry + "cca"));
    }

    // Check with partial match
    for (const std::string& entry : entries)
    {
        CPPUNIT_ASSERT(!dict.isExistingEntry(entry.substr(0, 3)));
    }
}

} // namespace yasc
