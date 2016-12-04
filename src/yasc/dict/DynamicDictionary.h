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
#ifndef _DYNAMIC_DICTIONARY_H_
# define _DYNAMIC_DICTIONARY_H_

# include "Dictionary.h"

namespace yasc {
namespace dict {

class DynamicDictionary : public Dictionary
{
public:
    DynamicDictionary();

    ~DynamicDictionary() = default;

    bool addEntry(const std::string& entry) override;
    bool safeAddEntry(const std::string& entry) override;
};

} // namespace dict
} // namespace yasc

#endif /* !_DYNAMIC_DICTIONARY_H_ */
