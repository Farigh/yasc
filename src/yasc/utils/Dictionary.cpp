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

namespace yasc {
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
 * It will not check for it's validity before adding new nodes, if the entry was not valid
 * the dictionnary might get corrupted.
 * @return returns true if the entry is valid (according to the alphabet), false otherwhise
 */
bool Dictionary::addEntry(const std::string& entry)
{
    bool isValidEntry = true;

    NodeType currentNode = _head;
    for (const char& c : entry)
    {
        // Convert to lower-case first
        const char currentChar = std::tolower(c, std::locale());

        // Invalid transition type, return false
        if (_alphabet.find(currentChar) == _alphabet.end())
        {
            isValidEntry = false;
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
    if (isValidEntry && !currentNode->IsOutput())
    {
        currentNode->SetOutput(true);
    }

    return isValidEntry;
}

/**
 * @brief This function adds an entry to the dictionary only if it's a valid one
 * @return returns true if the entry is valid (according to the alphabet), false otherwhise
 */
bool Dictionary::safeAddEntry(const std::string& entry)
{
    bool isValidEntry = true;

    // Check entry validity
    for (const char& c : entry)
    {
        // Convert to lower-case first
        const char currentChar = std::tolower(c, std::locale());

        // Invalid transition type, return false
        if (_alphabet.find(currentChar) == _alphabet.end())
        {
            isValidEntry = false;
            break;
        }
    }

    if (isValidEntry)
    {
        addEntry(entry);
    }

    return isValidEntry;
}

/**
 * @brief This function checks if the given @p entry is part of the dictionary
 * @return returns true if the entry exists, false otherwhise
 */
bool Dictionary::isExistingEntry(const std::string& entry)
{
    bool entryExists = true;

    NodeType currentNode = _head;
    for (const char& c : entry)
    {
        // Convert to lower-case first
        const char currentChar = std::tolower(c, std::locale());

        NodeType tmpNode = currentNode->TryFollow(currentChar);
        if (tmpNode == nullptr)
        {
            entryExists = false;
            break;
        }
    }

    // Entry exists if it can go through it's entire transitions and ends with an output node
    return entryExists && currentNode->IsOutput();
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
} // namespace yasc
