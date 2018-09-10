#pragma once

#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#define _CPPUNIT_STR_EXPAND(s) #s
#define _CPPUNIT_ADD_TEST(s,cls,mth) s->addTest(new CppUnit::TestCaller < cls > (_CPPUNIT_STR_EXPAND(mth), &cls::mth, new CppUnit::ConcretTestFixtureFactory < cls > ()));

#define _CPPUNIT_MAKE_TEST_NAME(cls,name,when,should) TESTOF_##cls##_##name##__WHEN_##when##__SHOULD_##should
#define _CPPUNIT_DECLARE_TEST(id,cls,name,when,should) \
    static void _reg_##id##(CppUnit::TestSuite * s) \
    { \
        _CPPUNIT_ADD_TEST(s,cls,_CPPUNIT_MAKE_TEST_NAME(cls,name,when,should)) \
    } \
    void _CPPUNIT_MAKE_TEST_NAME(cls,name,when,should)()
