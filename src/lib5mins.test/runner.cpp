/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main_proxy( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_Lib5MinsTestSuite_init = false;
#include "5mins.test.h"

static Lib5MinsTestSuite suite_Lib5MinsTestSuite;

static CxxTest::List Tests_Lib5MinsTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Lib5MinsTestSuite( "5mins.test.h", 8, "Lib5MinsTestSuite", suite_Lib5MinsTestSuite, Tests_Lib5MinsTestSuite );

static class TestDescription_suite_Lib5MinsTestSuite_testBasicLogic : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testBasicLogic() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 47, "testBasicLogic" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testBasicLogic(); }
} testDescription_suite_Lib5MinsTestSuite_testBasicLogic;

static class TestDescription_suite_Lib5MinsTestSuite_testThatAllTimeFieldsReadProperly : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testThatAllTimeFieldsReadProperly() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 48, "testThatAllTimeFieldsReadProperly" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testThatAllTimeFieldsReadProperly(); }
} testDescription_suite_Lib5MinsTestSuite_testThatAllTimeFieldsReadProperly;

static class TestDescription_suite_Lib5MinsTestSuite_testOnOccasionallyOctalInput : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testOnOccasionallyOctalInput() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 49, "testOnOccasionallyOctalInput" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testOnOccasionallyOctalInput(); }
} testDescription_suite_Lib5MinsTestSuite_testOnOccasionallyOctalInput;

static class TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow1_UpperBound : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow1_UpperBound() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 50, "testOnMinuteFieldOverflow1_UpperBound" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testOnMinuteFieldOverflow1_UpperBound(); }
} testDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow1_UpperBound;

static class TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow2() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 51, "testOnMinuteFieldOverflow2" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testOnMinuteFieldOverflow2(); }
} testDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow2;

static class TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow3 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow3() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 52, "testOnMinuteFieldOverflow3" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testOnMinuteFieldOverflow3(); }
} testDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow3;

static class TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow4 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow4() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 53, "testOnMinuteFieldOverflow4" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testOnMinuteFieldOverflow4(); }
} testDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow4;

static class TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow5_LowerBound : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow5_LowerBound() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 54, "testOnMinuteFieldOverflow5_LowerBound" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testOnMinuteFieldOverflow5_LowerBound(); }
} testDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow5_LowerBound;

static class TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow6_UnderLowerBound : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow6_UnderLowerBound() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 55, "testOnMinuteFieldOverflow6_UnderLowerBound" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testOnMinuteFieldOverflow6_UnderLowerBound(); }
} testDescription_suite_Lib5MinsTestSuite_testOnMinuteFieldOverflow6_UnderLowerBound;

static class TestDescription_suite_Lib5MinsTestSuite_testOnHourFieldOverflow1_LowerBound : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testOnHourFieldOverflow1_LowerBound() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 56, "testOnHourFieldOverflow1_LowerBound" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testOnHourFieldOverflow1_LowerBound(); }
} testDescription_suite_Lib5MinsTestSuite_testOnHourFieldOverflow1_LowerBound;

static class TestDescription_suite_Lib5MinsTestSuite_testOnHourFieldOverflow2_UpperBound : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testOnHourFieldOverflow2_UpperBound() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 57, "testOnHourFieldOverflow2_UpperBound" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testOnHourFieldOverflow2_UpperBound(); }
} testDescription_suite_Lib5MinsTestSuite_testOnHourFieldOverflow2_UpperBound;

static class TestDescription_suite_Lib5MinsTestSuite_testInvalidInput_InvalidFieldSeparator : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testInvalidInput_InvalidFieldSeparator() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 58, "testInvalidInput_InvalidFieldSeparator" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testInvalidInput_InvalidFieldSeparator(); }
} testDescription_suite_Lib5MinsTestSuite_testInvalidInput_InvalidFieldSeparator;

static class TestDescription_suite_Lib5MinsTestSuite_testInvalidInput_HexadecimalDigits : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testInvalidInput_HexadecimalDigits() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 59, "testInvalidInput_HexadecimalDigits" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testInvalidInput_HexadecimalDigits(); }
} testDescription_suite_Lib5MinsTestSuite_testInvalidInput_HexadecimalDigits;

static class TestDescription_suite_Lib5MinsTestSuite_testInvalidInput_Letters : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testInvalidInput_Letters() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 60, "testInvalidInput_Letters" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testInvalidInput_Letters(); }
} testDescription_suite_Lib5MinsTestSuite_testInvalidInput_Letters;

static class TestDescription_suite_Lib5MinsTestSuite_testInvalidInput_MinutesRange : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testInvalidInput_MinutesRange() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 61, "testInvalidInput_MinutesRange" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testInvalidInput_MinutesRange(); }
} testDescription_suite_Lib5MinsTestSuite_testInvalidInput_MinutesRange;

static class TestDescription_suite_Lib5MinsTestSuite_testInvalidInput_HoursRange : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lib5MinsTestSuite_testInvalidInput_HoursRange() : CxxTest::RealTestDescription( Tests_Lib5MinsTestSuite, suiteDescription_Lib5MinsTestSuite, 62, "testInvalidInput_HoursRange" ) {}
 void runTest() { suite_Lib5MinsTestSuite.testInvalidInput_HoursRange(); }
} testDescription_suite_Lib5MinsTestSuite_testInvalidInput_HoursRange;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
