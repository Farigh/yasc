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
#ifndef _YASC_TEST_CALLER_H_
# define _YASC_TEST_CALLER_H_

# ifdef __GNUC__
// Disable CppUnit warnings (third-party)
#  pragma GCC diagnostic push
//#  pragma GCC diagnostic ignored "-Wsuggest-override"
# endif

# include <cppunit/TestCase.h>

# ifdef __GNUC__
// Restore warnings
#  pragma GCC diagnostic pop
# endif

namespace yasc {
namespace tests {
namespace helpers {
namespace cppunit {

template <class Fixture>
class YascTestCaller : public CppUnit::TestCase
{
public:
    using TestMethod = void (Fixture::*)();

    /*!
    * Constructor for YascTestCaller.
    * This constructor does not create a new Fixture instance but accepts
    * an existing one as parameter. The YascTestCaller will own the
    * Fixture object and delete it in its destructor.
    * @param name name of this YascTestCaller
    * @param fixture the Fixture to invoke the test method on.
    * @param test the method this YascTestCaller calls in runTest()
    * @param params the params forwarded to the @p test method on call.
    */
    template<typename TestMethod, typename... Args>
    YascTestCaller(std::string name, Fixture* fixture, TestMethod test, Args... params)
        : TestCase(name),
          _cppUnitFixture(fixture)
    {
        // Test method pointer needs to be passed by copy
        _testCall = [&, test]()
                    {
                        (this->_cppUnitFixture->*test)(params...);
                    };
    }

    ~YascTestCaller()
    {
        // CppUnit fixture needs to be deleted
        delete _cppUnitFixture;
    }

    void runTest()
    {
        _testCall();
    }

    void setUp()
    {
        _cppUnitFixture->setUp();
    }

    void tearDown()
    {
        _cppUnitFixture->tearDown();
    }

    std::string toString() const
    {
        return "TestCaller " + getName();
    }

private:
    YascTestCaller(const YascTestCaller &other) = delete;
    YascTestCaller& operator=(const YascTestCaller &other) = delete;

private:
    Fixture *_cppUnitFixture;
    std::function<void()> _testCall;
};

} // namespace cppunit
} // namespace helpers
} // namespace tests
} // namespace yasc

#endif /* !_YASC_TEST_CALLER_H_ */
