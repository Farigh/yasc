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
#ifndef _LANGUAGE_SEPARATOR_H_
# define _LANGUAGE_SEPARATOR_H_

# include <list>

namespace yasc {
namespace lang {

struct LanguageSeparator
{
public:
    using SurroundingTypes = enum
    {
        NoSurroundingNeeded,
        SpaceBeforeNeeded,
        SpaceAfterNeeded
    };

    LanguageSeparator() = delete;
    LanguageSeparator(const char value, const SurroundingTypes surrounding);

    const char Value;
    const SurroundingTypes Surrounding;
};

class LanguageSeparatorList
{
    using InnerListType = std::list<LanguageSeparator>;

public:
    using const_iterator = typename InnerListType::const_iterator;
    using value_type = typename InnerListType::value_type;

    LanguageSeparatorList() = default;

    void addSeparator(const char value, const LanguageSeparator::SurroundingTypes surrounding);

    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

private:
    InnerListType _innerList;
};

} // namespace lang
} // namespace yasc

#endif /* !_LANGUAGE_SEPARATOR_H_ */
