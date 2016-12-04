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
#include "DictionaryFactory.h"

#include "DynamicDictionary.h"

#include <fstream>

namespace yasc {
namespace dict {

/**
 * @brief Creates a dictionnary and populate it from a given file (@p filePath)
 * @param filePath the path to the file to read
 * @return returns the newly created dictionnary
 */
Dictionary::Ptr DictionaryFactory::CreateFromFile(const std::string& filePath)
{
    DynamicDictionary::Ptr result = std::make_shared<DynamicDictionary>();

    std::ifstream inputFile(filePath);
    std::string word;
    while (inputFile >> word)
    {
        result->addEntry(word);
    }

    return result;
}


} // namespace dict
} // namespace yasc
