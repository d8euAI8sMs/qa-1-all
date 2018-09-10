#pragma once

#include <ctime>

#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#define _CPPUNIT_STR_EXPAND(s) #s

#define _GWT(name,when,should) TESTOF_##name##__WHEN_##when##__SHOULD_##should
#define _CPPUNIT_DECLARE_TEST(name,when,should) \
    void _GWT(name,when,should)()
#define _CPPUNIT_NAMED_TEST(name,testMethod)              \
    CPPUNIT_TEST_SUITE_ADD_TEST(                          \
        ( new CPPUNIT_NS::TestCaller<TestFixtureType>(    \
                  context.getTestNameFor(std::string(_CPPUNIT_STR_EXPAND(testMethod) "[") + name + std::string("]")), \
                  &TestFixtureType::testMethod,           \
                  context.cloneFactory() ) ) )

inline std::string local_date()
{
    char buf[100];
    std::tm fmtt;

    std::time_t t = time(nullptr);

    localtime_s(&fmtt, &t);

    std::strftime(buf, 100, "%d.%m.%Y %H:%M:%S", &fmtt);

    return buf;
}
