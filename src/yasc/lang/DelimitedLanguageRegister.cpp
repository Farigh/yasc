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
#include "DelimitedLanguageRegister.h"

namespace yasc {
namespace lang {

constexpr DelimitedLanguageRegister::NodeType::InnerKeyType DelimitedLanguageRegister::_skipSeparator;

DelimitedLanguageRegister::DelimitedLanguageRegister(const LanguageSeparatorList& separatorList)
	: _separatorHead(std::make_shared<NodeType>())
{
    static constexpr char spaceSeparator = ' ';

    // Process separator list to create separator transitions
    for (const LanguageSeparatorList::value_type& separator : separatorList)
    {
        NodeType::Ptr currentNode = _separatorHead;
        if (separator.Surrounding == LanguageSeparator::SurroundingTypes::SpaceBeforeNeeded)
        {
            currentNode = currentNode->FollowOrAdd(spaceSeparator);
        }

        // Add separator transition
        currentNode = currentNode->FollowOrAdd(separator.Value);

        if (separator.Surrounding == LanguageSeparator::SurroundingTypes::SpaceAfterNeeded)
        {
            currentNode = currentNode->FollowOrAdd(spaceSeparator);
        }

        currentNode->AddTransitionToNode(_skipSeparator, _head);
    }
}

/**
 * @brief This function adds an entry to the language register
 *
 * @param entry the entry to add
 * @return returns true if the entry is valid, false otherwhise
 */
bool DelimitedLanguageRegister::addEntry(const std::string& entry)
{
     NodeType::Ptr tail = DynamicDictionary::innerAddEntry(entry);

     tail->AddTransitionToNode(_skipSeparator, _separatorHead);

     return true;
}

/**
 * @brief This function create a string representing the selected node
 *
 * @param padding The line padding for indentation
 *
 * @return returns the constructed string
 */
// TODO: Factorize with nodeToString
std::string DelimitedLanguageRegister::separatorNodeToString(const NodeType::Ptr& node, const std::string& padding) const
{
    std::ostringstream resultFormater;

    // Break on head node to avoid infinite loop
    if (node == _head)
    {
        resultFormater << " -> []" << std::endl;
    }
    else
    {
        bool isFirstPrint = true;

        // Sort transitions for printing
        std::map<NodeType::InnerKeyType, NodeType::Ptr> sortedTransitions;
        const NodeType::TransitionsType& nodeTransitions = node->getTransitions();
        sortedTransitions.insert(nodeTransitions.begin(), nodeTransitions.end());
        for (const typename NodeType::TransitionsType::value_type& t : sortedTransitions)
        {
            if (isFirstPrint)
            {
                isFirstPrint = false;
            }
            else
            {
                // Add padding
                resultFormater << padding;
            }

            // Make _skipSeparator printable
            const NodeType::InnerKeyType transitionChar = t.first;
            std::string transitionStr = "''";
            if (transitionChar != _skipSeparator)
            {
                transitionStr = std::string(1, transitionChar);
            }

            resultFormater << " -> " << transitionStr << separatorNodeToString(t.second, padding + "     ");
        }
    }

    return resultFormater.str();
}

/**
 * @brief This function create a string representing the selected separator node
 *
 * @param padding The line padding for indentation
 *
 * @return returns the constructed string
 */
std::string DelimitedLanguageRegister::nodeToString(const NodeType::Ptr& node, const std::string& padding) const
{
    std::ostringstream resultFormater;

    // First, print output status
    bool isFirstPrint = true;
    if (node->IsOutput())
    {
        resultFormater << " -> []" << std::endl;
        isFirstPrint = false;
    }

    // Break on separators transition to avoid infinite loop
    if (node == _separatorHead)
    {
        if (!isFirstPrint)
        {
            // Add padding
            resultFormater << padding;
        }
        resultFormater << " -> [S]" << std::endl;
    }
    else
    {
        // Sort transitions for printing
        std::map<NodeType::InnerKeyType, NodeType::Ptr> sortedTransitions;
        const NodeType::TransitionsType& nodeTransitions = node->getTransitions();
        sortedTransitions.insert(nodeTransitions.begin(), nodeTransitions.end());
        for (const typename NodeType::TransitionsType::value_type& t : sortedTransitions)
        {
            if (isFirstPrint)
            {
                isFirstPrint = false;
            }
            else
            {
                // Add padding
                resultFormater << padding;
            }

            // Make _skipSeparator printable
            const NodeType::InnerKeyType transitionChar = t.first;
            std::string transitionStr = "''";
            if (transitionChar != _skipSeparator)
            {
                transitionStr = std::string(1, transitionChar);
            }

            resultFormater << " -> " << transitionStr << nodeToString(t.second, padding + "     ");
        }
    }

    return resultFormater.str();
}

/**
 * @brief This function create a string representing the current graph
 *
 * @return returns the constructed string
 */
std::string DelimitedLanguageRegister::toString() const
{
    std::ostringstream resultFormater;

    resultFormater << "Separators [S]:" << std::endl
                   << "  " << separatorNodeToString(_separatorHead, "  ") << std::endl
                   << "Graph:" << std::endl
                   << "  " << nodeToString(_head, "  ");

    return resultFormater.str();
}

} // namespace lang
} // namespace yasc
