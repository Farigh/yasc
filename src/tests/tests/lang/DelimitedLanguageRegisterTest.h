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
#ifndef _DELIMITED_LANGUAGE_REGISTER_TEST_H_
# define _DELIMITED_LANGUAGE_REGISTER_TEST_H_

# include <helpers/cppunit/CppUnitHelperMacrosWrapper.h>
# include <yasc/lang/LanguageSeparator.h>

namespace yasc {
namespace tests {

class DelimitedLanguageRegisterTest : public CppUnit::TestFixture
{
private:
    CPPUNIT_TEST_SUITE(DelimitedLanguageRegisterTest);
        CPPUNIT_TEST(AddEntityTest);
        CPPUNIT_TEST(AddEntityComplexTest);
    CPPUNIT_TEST_SUITE_END();

public:
    DelimitedLanguageRegisterTest();

    void AddEntityTest();
    void AddEntityComplexTest();

private:
    ::yasc::lang::LanguageSeparatorList _testSeparators;
};

} // namespace tests
} // namespace yasc

#endif /* !_DELIMITED_LANGUAGE_REGISTER_TEST_H_ */
