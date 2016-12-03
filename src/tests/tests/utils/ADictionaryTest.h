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
#ifndef _A_DICTIONARY_TEST_H_
# define _A_DICTIONARY_TEST_H_

# include <helpers/cppunit/CppUnitHelperMacrosWrapper.h>

# include <list>

namespace yasc {

class ADictionaryTest
{
protected:
    enum class Steps : std::uint8_t
    {
        AddValidEntry = 0,
        AddValidEntryTwice,
        AddInvalidEntry,
        AddEntryWithNoCommonPrefix,
        AddLongEntryWithCommonPrefix,
        AddEntryWhichIsAPrefix
    };

    ADictionaryTest() = default;
    ~ADictionaryTest() = default;

    // Make it non-copyable
    ADictionaryTest(const ADictionaryTest&) = delete;
    ADictionaryTest& operator=(const ADictionaryTest&) = delete;

    template<class DictionaryType>
    void CheckAddEntity(DictionaryType& dict) const
    {
        // Adding a valid entry should return true
        CPPUNIT_ASSERT(dict.addEntry("abbaa"));

        // Check tree consistency
        std::ostringstream expectedOutput;
        expectedOutput << " -> []" << std::endl
                       << " -> a -> b -> b -> a -> a -> []" << std::endl;
        CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict.toString());
    }

    template<class DictionaryType>
    std::ostringstream CheckAddEntityComplex(DictionaryType& dict, const Steps step) const
    {
        // === Adding a valid entry should return true
        CPPUNIT_ASSERT(dict.addEntry("abbaa"));

        // Check tree consistency
        std::ostringstream expectedOutput;
        expectedOutput << " -> []" << std::endl
                       << " -> a -> b -> b -> a -> a -> []" << std::endl;
        CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict.toString());

        if (step == Steps::AddValidEntry)
        {
            return expectedOutput;
        }

        // === Adding a valid entry twice should return true and the dictionary should remain the same
        CPPUNIT_ASSERT(dict.addEntry("abbaa"));
        CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict.toString());

        if (step == Steps::AddValidEntryTwice)
        {
            return expectedOutput;
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
            return expectedOutput2;
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
            return expectedOutput3;
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

        return expectedOutput4;
    }

    template<class DictionaryType>
    void CheckEntityExistence(DictionaryType& dict) const
    {
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
};

} // namespace yasc

#endif /* !_A_DICTIONARY_TEST_H_ */
