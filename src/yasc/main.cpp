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
#include <utils/Dictionary.h>

#include <iostream>

int main(void)
{
    // Just a little test for now
    std::set<char> alphabet = { 'a', 'b', 'c' };

    ::utils::Dictionary dict(alphabet);

    dict.addEntry("abbaa");
    dict.addEntry("aba");
    dict.addEntry("aaba");
    dict.addEntry("aababa");

    std::cout << dict.toString() << std::endl;

    return 0;
}