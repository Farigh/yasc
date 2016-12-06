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
#ifndef _GRAPH_NODE_H_
# define _GRAPH_NODE_H_

# include <map>
# include <memory>
# include <sstream>
# include <unordered_map>

namespace yasc {
namespace dict {

template <typename KeyType>
class GraphNode
{
public:
    using Ptr = std::shared_ptr<GraphNode<KeyType>>;
    using TransitionsType = std::unordered_map<KeyType, Ptr>;

    GraphNode() : _isOutput(false) {}

    virtual ~GraphNode() = default;

    /**
     * @brief This function tries to follow the @p moveType transition
     *
     * @param transitionType the transition type to follow
     * @return returns the destination node if the transition exists,
     *         nullptr otherwhise
     */
    Ptr TryFollow(const KeyType& transitionType)
    {
        Ptr result = nullptr;
        if (_transitions.find(transitionType) != _transitions.end())
        {
            result = _transitions[transitionType];
        }

        return result;
    }

    /**
     * @brief This function adds a transition if it does not exist, else follows it
     *
     * This function tries to follow the @p moveType transition.
     * If it does not exist it creates it
     *
     * @param transitionType the transition type to follow
     * @return returns the destination node
     */
    Ptr FollowOrAdd(const KeyType& transitionType)
    {
        Ptr result = TryFollow(transitionType);
        if (result == nullptr)
        {
            result = AddTransition(transitionType);
        }

        return result;
    }

    /**
     * @brief This function add a @p transitionType node
     *
     * @param transitionType the transition type to add
     * @return returns the newly created node
     */
    Ptr AddTransition(const KeyType& transitionType)
    {
        Ptr result = std::make_shared<GraphNode<KeyType>>();

        AddTransitionToNode(transitionType, result);

        return result;
    }

    /**
     * @brief This function add a @p transitionType to an existing node
     *
     * @param transitionType the transition type to add
     * @param destNode the destination node
     */
    void AddTransitionToNode(const KeyType& transitionType, Ptr destNode)
    {
        _transitions.insert({ transitionType, destNode });
    }

    /**
     * @brief This function sets wether the current node is an output of the graph
     *
     * @param isOutput true if the node is an output, false otherwise
     */
    void SetOutput(const bool isOutput)
    {
        _isOutput = isOutput;
    }

    /**
     * @brief This function returns wether the current node is an output of the graph
     *
     * @return returns true if the graph is an output, false otherwhise
     */
    bool IsOutput() const
    {
        return _isOutput;
    }

    /**
     * @brief This function create a string representing the current node
     *
     * @return returns the constructed string
     */
    std::string toString(const std::string& padding = "") const
    {
        std::ostringstream resultFormater;

        // First, print output status
        bool isFirstPrint = true;
        if (IsOutput())
        {
            resultFormater << " -> []" << std::endl;
            isFirstPrint = false;
        }

        // Sort transitions for printing
        std::map<KeyType, Ptr> sortedTransitions;
        sortedTransitions.insert(_transitions.begin(), _transitions.end());
        for (const typename TransitionsType::value_type& t : sortedTransitions)
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

            resultFormater << " -> " << t.first << t.second->toString(padding + "     ");
        }

        return resultFormater.str();
    }

private:
    bool _isOutput;
    TransitionsType _transitions;
};

} // namespace dict
} // namespace yasc

#endif /* !_GRAPH_NODE_H_ */
