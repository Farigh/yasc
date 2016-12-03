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
#ifndef _YASC_TEST_RUNNER_H_
# define _YASC_TEST_RUNNER_H_

# ifdef __GNUC__
// Disable CppUnit warnings (third-party)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wsuggest-override"
#  pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
# endif

# include <cppunit/TestResult.h>
# include <cppunit/TestResultCollector.h>
# include <cppunit/TestRunner.h>

# ifdef __GNUC__
// Restore warnings
#  pragma GCC diagnostic pop
# endif

# include <memory>
# include <string>

namespace yasc {
namespace tests {
namespace helpers {
namespace cppunit {

class YascTestRunner : public CppUnit::TestRunner
{
public:
    YascTestRunner();

    ~YascTestRunner() = default;

    bool runTests();

private:
    CppUnit::TestResult _eventManager;
    std::unique_ptr<CppUnit::TestResultCollector> _resultCollector;
};

} // namespace cppunit
} // namespace helpers
} // namespace tests
} // namespace yasc

#endif /* !_YASC_TEST_RUNNER_H_ */
