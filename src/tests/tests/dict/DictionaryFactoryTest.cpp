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
#include "DictionaryFactoryTest.h"

#include <tests/DataManager.h>
#include <yasc/dict/DictionaryFactory.h>

namespace yasc {
namespace tests {

// Register test suite
CPPUNIT_TEST_SUITE_REGISTRATION(DictionaryFactoryTest);

void DictionaryFactoryTest::CreateFromFileTest()
{
    const std::string resourcePath = ::yasc::tests::DataManager::getResourcePath();
    const std::string resourceFile = resourcePath + "/dictionary_factory/create_from_file_test.txt";

    // Load dictionary from file
    ::yasc::dict::Dictionary::Ptr dict = ::yasc::dict::DictionaryFactory::CreateFromFile(resourceFile);

    std::ostringstream expectedOutput;
    expectedOutput << " -> []" << std::endl
                   << " -> a -> []" << std::endl
                   << "      -> n -> y -> []" << std::endl
                   << " -> c -> h -> a -> r -> []" << std::endl
                   << "                     -> a -> c -> t -> e -> r -> s -> []" << std::endl
                   << "                     -> s -> []" << std::endl
                   << "      -> o -> m -> p -> o -> s -> e -> d -> []" << std::endl
                   << " -> i -> s -> []" << std::endl
                   << "      -> t -> []" << std::endl
                   << " -> m -> o -> r -> e -> []" << std::endl
                   << " -> o -> f -> []" << std::endl
                   << " -> p -> h -> r -> a -> s -> e -> []" << std::endl
                   << " -> r -> i -> g -> h -> t -> []" << std::endl
                   << " -> s -> o -> m -> e -> []" << std::endl
                   << " -> t -> h -> i -> s -> []" << std::endl
                   << " -> w -> h -> i -> c -> h -> []" << std::endl
                   << "      -> i -> t -> h -> []" << std::endl;

    // Check result
    CPPUNIT_ASSERT_EQUAL(expectedOutput.str(), dict->toString());
}

} // namespace tests
} // namespace yasc
