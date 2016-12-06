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
#include "LanguageSeparator.h"

#include <locale>

namespace yasc {
namespace lang {

LanguageSeparator::LanguageSeparator(const char value, const SurroundingTypes surrounding)
    : Value(value), Surrounding(surrounding)
{
}


void LanguageSeparatorList::addSeparator(const char value, const LanguageSeparator::SurroundingTypes surrounding)
{
    _innerList.push_back(LanguageSeparator(value, surrounding));
}

LanguageSeparatorList::const_iterator LanguageSeparatorList::begin() const
{
    return cbegin();
}

LanguageSeparatorList::const_iterator LanguageSeparatorList::end() const
{
    return cend();
}

LanguageSeparatorList::const_iterator LanguageSeparatorList::cbegin() const
{
    return _innerList.cbegin();
}

LanguageSeparatorList::const_iterator LanguageSeparatorList::cend() const
{
    return _innerList.cend();
}

} // namespace lang
} // namespace yasc
