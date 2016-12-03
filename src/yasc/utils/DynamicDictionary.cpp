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
#include "DynamicDictionary.h"

#include <locale>

namespace yasc {
namespace utils {

/**
 * @brief This is the @c DynamicDictionary constructor
 */
DynamicDictionary::DynamicDictionary()
    : Dictionary(std::set<char>())
{
}

/**
 * @brief This function adds an entry to the dictionary
 * @param entry the entry to add
 * @return returns true if the entry is valid, false otherwhise
 */
bool DynamicDictionary::addEntry(const std::string& entry)
{
    bool isValidEntry = true;

    NodeType currentNode = _head;
    for (const char& c : entry)
    {
        // Convert to lower-case first
        const char currentChar = std::tolower(c, std::locale());

        NodeType tmpNode = currentNode->TryFollow(currentChar);
        if (tmpNode == nullptr)
        {
            tmpNode = currentNode->AddTransition(currentChar);
        }

        currentNode = tmpNode;
    }

    // The last node added is the output
    if (!currentNode->IsOutput())
    {
        currentNode->SetOutput(true);
    }

    return isValidEntry;
}

/**
 * @brief This function does the exact same as @ref addEntry
 * Dynamic dictionary does not store any alphabet
 * @return returns true if the entry is valid, false otherwhise
 */
bool DynamicDictionary::safeAddEntry(const std::string& entry)
{
    return addEntry(entry);
}

} // namespace utils
} // namespace yasc
