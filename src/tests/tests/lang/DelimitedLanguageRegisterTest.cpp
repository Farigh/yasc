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
#include "DelimitedLanguageRegisterTest.h"

#include <yasc/lang/DelimitedLanguageRegister.h>

#include <list>
#include <sstream>

namespace yasc {
namespace tests {

// Register test suite
CPPUNIT_TEST_SUITE_REGISTRATION(DelimitedLanguageRegisterTest);

DelimitedLanguageRegisterTest::DelimitedLanguageRegisterTest()
{
    // Initialize separators
    _testSeparators.addSeparator('.', ::yasc::lang::LanguageSeparator::SurroundingTypes::NoSurroundingNeeded);
    _testSeparators.addSeparator('!', ::yasc::lang::LanguageSeparator::SurroundingTypes::NoSurroundingNeeded);
    _testSeparators.addSeparator('?', ::yasc::lang::LanguageSeparator::SurroundingTypes::NoSurroundingNeeded);
    _testSeparators.addSeparator(',', ::yasc::lang::LanguageSeparator::SurroundingTypes::SpaceAfterNeeded);
    _testSeparators.addSeparator(':', ::yasc::lang::LanguageSeparator::SurroundingTypes::SpaceAfterNeeded);
    _testSeparators.addSeparator('\'', ::yasc::lang::LanguageSeparator::SurroundingTypes::SpaceBeforeNeeded);
    _testSeparators.addSeparator('\'', ::yasc::lang::LanguageSeparator::SurroundingTypes::SpaceAfterNeeded);
    _testSeparators.addSeparator('"', ::yasc::lang::LanguageSeparator::SurroundingTypes::SpaceAfterNeeded);
    _testSeparators.addSeparator('"', ::yasc::lang::LanguageSeparator::SurroundingTypes::SpaceBeforeNeeded);
}

static std::string getSeparatorExpectedOutput()
{

    std::ostringstream expectedOutput;
    expectedOutput << "Separators [S]:" << std::endl
                   << "   ->   -> \" -> '' -> []" << std::endl
                   << "        -> ' -> '' -> []" << std::endl
                   << "   -> ! -> '' -> []" << std::endl
                   << "   -> \" ->   -> '' -> []" << std::endl
                   << "   -> ' ->   -> '' -> []" << std::endl
                   << "   -> , ->   -> '' -> []" << std::endl
                   << "   -> . -> '' -> []" << std::endl
                   << "   -> : ->   -> '' -> []" << std::endl
                   << "   -> ? -> '' -> []" << std::endl;

    return expectedOutput.str();
}

void DelimitedLanguageRegisterTest::AddEntityTest()
{
    ::yasc::lang::DelimitedLanguageRegister dict(_testSeparators);

    // Adding a valid entry should return true
    CPPUNIT_ASSERT(dict.addEntry("Hello"));

    // Check tree consistency
    std::ostringstream expectedOutput;
    expectedOutput << getSeparatorExpectedOutput()
                   << std::endl
                   << "Graph:" << std::endl
                   << "   -> []" << std::endl
                   << "   -> h -> e -> l -> l -> o -> []" << std::endl
                   << "                            -> '' -> [S]" << std::endl;
    CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict.toString());
}

void DelimitedLanguageRegisterTest::AddEntityComplexTest()
{
    ::yasc::lang::DelimitedLanguageRegister dict(_testSeparators);

    dict.addEntry("Hello");
    dict.addEntry("my");
    dict.addEntry("name");
    dict.addEntry("is");
    dict.addEntry("David");

    // Check tree consistency
    std::ostringstream expectedOutput;
    expectedOutput << getSeparatorExpectedOutput()
                   << std::endl
                   << "Graph:" << std::endl
                   << "   -> []" << std::endl
                   << "   -> d -> a -> v -> i -> d -> []" << std::endl
                   << "                            -> '' -> [S]" << std::endl
                   << "   -> h -> e -> l -> l -> o -> []" << std::endl
                   << "                            -> '' -> [S]" << std::endl
                   << "   -> i -> s -> []" << std::endl
                   << "             -> '' -> [S]" << std::endl
                   << "   -> m -> y -> []" << std::endl
                   << "             -> '' -> [S]" << std::endl
                   << "   -> n -> a -> m -> e -> []" << std::endl
                   << "                       -> '' -> [S]" << std::endl;
    CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict.toString());
}

} // namespace tests
} // namespace yasc
