#pragma once

#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#define _GWT(name,when,should) TESTOF_##name##__WHEN_##when##__SHOULD_##should
#define _CPPUNIT_DECLARE_TEST(name,when,should) \
    void _GWT(name,when,should)()
