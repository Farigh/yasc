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
#ifndef _DICTIONARY_TEST_H_
# define _DICTIONARY_TEST_H_

# include <helpers/cppunit/CppUnitHelperMacrosWrapper.h>

# include "ADictionaryTest.h"

namespace yasc {
namespace tests {

class DictionaryTest : public CppUnit::TestFixture, protected ADictionaryTest
{
private:
    using Steps = ADictionaryTest::Steps;

    CPPUNIT_TEST_SUITE(DictionaryTest);
        CPPUNIT_TEST(AddValidEntityTest);
        CPPUNIT_TEST(AddInvalidEntityTest);
        YACS_CPPUNIT_PARAMETERIZED_TEST(AddEntityComplexTest, Steps::AddValidEntry);
        YACS_CPPUNIT_PARAMETERIZED_TEST(AddEntityComplexTest, Steps::AddValidEntryTwice);
        YACS_CPPUNIT_PARAMETERIZED_TEST(AddEntityComplexTest, Steps::AddInvalidEntry);
        YACS_CPPUNIT_PARAMETERIZED_TEST(AddEntityComplexTest, Steps::AddEntryWithNoCommonPrefix);
        YACS_CPPUNIT_PARAMETERIZED_TEST(AddEntityComplexTest, Steps::AddLongEntryWithCommonPrefix);
        YACS_CPPUNIT_PARAMETERIZED_TEST(AddEntityComplexTest, Steps::AddEntryWhichIsAPrefix);
        CPPUNIT_TEST(CheckEntityExistenceTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void AddValidEntityTest();
    void AddInvalidEntityTest();
    void AddEntityComplexTest(const Steps step);
    void CheckEntityExistenceTest();
};

} // namespace tests
} // namespace yasc

#endif /* !_DICTIONARY_TEST_H_ */
