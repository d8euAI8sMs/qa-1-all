#pragma once

#define CXXTEST_USER_VALUE_TRAITS

#include <string>

#include <cxxtest/ValueTraits.h>

namespace CxxTest
{
    CXXTEST_TEMPLATE_INSTANTIATION
    class ValueTraits<std::string>
    {
        std::string _s;
    public:
        ValueTraits(const std::string & s) : _s("\"" + s + "\"") {}
        const char *asString() const { return _s.c_str(); }
    };

    CXXTEST_TEMPLATE_INSTANTIATION
    class ValueTraits<int>
    {
        std::string _s;
    public:
        ValueTraits(int i) : _s(std::to_string(i)) {}
        const char *asString() const { return _s.c_str(); }
    };
};
