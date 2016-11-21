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

#include "Dictionary.h"

#include <locale>

namespace utils {

/**
 * @brief This is the @c Dictionary constructor
 * @param alphabet the set of valid transition values
 */
Dictionary::Dictionary(const std::set<char>& alphabet)
    : _head(std::make_shared<GraphNode<char>>()),
      _alphabet(alphabet)
{
    // Head is always an output since an empty string is valid
    _head->SetOutput(true);
}

/**
 * @brief This function adds an entry to the dictionary
 * @return returns true if the entry is valid (according to the alphabet), false otherwhise
 */
bool Dictionary::addEntry(const std::string& entry)
{
    bool result = true;

    NodeType currentNode = _head;
    for (const char& c : entry)
    {
        // Convert to lower-case first
        const char currentChar = std::tolower(c, std::locale());

        // Invalid transition type, return false
        if (_alphabet.find(currentChar) == _alphabet.end())
        {
            result = false;
            break;
        }

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

    return result;
}
/**
 * @brief This function create a string representing the current graph
 * @return returns the constructed string
 */
std::string Dictionary::toString() const
{
    return _head->toString();
}

} // namespace utils