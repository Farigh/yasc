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
#ifndef _DICTIONARY_H_
# define _DICTIONARY_H_

# include "GraphNode.h"

# include <set>

namespace yasc {
namespace dict {

class Dictionary
{
public:
    using Ptr = std::shared_ptr<Dictionary>;
    using NodeType = GraphNode<char>::Ptr;

    // Keep the compiler from generating default ctor
    Dictionary() = delete;
    Dictionary(const std::set<char>& alphabet);
    virtual ~Dictionary() = default;

    virtual bool addEntry(const std::string& entry);
    virtual bool safeAddEntry(const std::string& entry);
    bool isExistingEntry(const std::string& entry);

    std::string toString() const;

protected:
    NodeType _head;

private:
    const std::set<char>& _alphabet;
};

} // namespace dict
} // namespace yasc

#endif /* !_DICTIONARY_H_ */
