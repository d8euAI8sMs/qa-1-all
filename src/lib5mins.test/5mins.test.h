#include <array>
#include <tuple>

#include <cxxtest/TestSuite.h>

#include "5mins.stub.h"

class Lib5MinsTestSuite : public CxxTest::TestSuite
{
private:
    using test_data_t = std::tuple < std::string, int, std::string > ;
private:
    std::vector < test_data_t > testData;
    void setUp()
    {
        testData = {{
            /* 00 */ std::make_tuple("00:00", 0, "zero hours five minutes"), // basic logic
            /* 01 */ std::make_tuple("12:34", 0, "twelve hours thirty nine minutes"), // all digits read correctly
            /* 02 */ std::make_tuple("08:08", 0, "eight hours thirteen minutes"), // occasionally octal input
            /* 03 */ std::make_tuple("00:59", 0, "one hours four minutes"), // minute field overflow
            /* 04 */ std::make_tuple("00:58", 0, "one hours three minutes"),
            /* 05 */ std::make_tuple("00:57", 0, "one hours two minutes"),
            /* 06 */ std::make_tuple("00:56", 0, "one hours one minutes"),
            /* 07 */ std::make_tuple("00:55", 0, "one hours zero minutes"),
            /* 08 */ std::make_tuple("00:54", 0, "zero hours fifty nine minutes"),
            /* 09 */ std::make_tuple("23:55", 0, "zero hours zero minutes"), // hour field overflow
            /* 10 */ std::make_tuple("23:56", 0, "zero hours one minutes"), // hour field overflow
            /* 11 */ std::make_tuple("01.02", 1, ""),
            /* 12 */ std::make_tuple("0A:0B", 1, ""), // occasionally hex input
            /* 13 */ std::make_tuple("XY:ZW", 2, ""),
            /* 14 */ std::make_tuple("00:60", 2, ""), // invalid time (minutes)
            /* 15 */ std::make_tuple("24:00", 2, ""), // invalid time (hours)
            /* 16 */ std::make_tuple("24:000", 1, ""), // too long input
        }};
    }
private:
    static void s_doTest(const test_data_t & d)
    {
        int status;
        std::string result;

        status = GetTimePlus5MinStr(std::get < 0 > (d), result);

        TS_ASSERT_EQUALS(status, std::get < 1 > (d));
        TS_ASSERT_EQUALS(result, std::get < 2 > (d));
    }
public:
    void testBasicLogic()                               { s_doTest(testData[ 0]); }
    void testThatAllTimeFieldsReadProperly()            { s_doTest(testData[ 1]); }
    void testOnOccasionallyOctalInput()                 { s_doTest(testData[ 2]); }
    void testOnMinuteFieldOverflow1_UpperBound()        { s_doTest(testData[ 3]); }
    void testOnMinuteFieldOverflow2()                   { s_doTest(testData[ 4]); }
    void testOnMinuteFieldOverflow3()                   { s_doTest(testData[ 5]); }
    void testOnMinuteFieldOverflow4()                   { s_doTest(testData[ 6]); }
    void testOnMinuteFieldOverflow5_LowerBound()        { s_doTest(testData[ 7]); }
    void testOnMinuteFieldOverflow6_UnderLowerBound()   { s_doTest(testData[ 8]); }
    void testOnHourFieldOverflow1_LowerBound()          { s_doTest(testData[ 9]); }
    void testOnHourFieldOverflow2_UpperBound()          { s_doTest(testData[10]); }
    void testInvalidInput_InvalidFieldSeparator()       { s_doTest(testData[11]); }
    void testInvalidInput_HexadecimalDigits()           { s_doTest(testData[12]); }
    void testInvalidInput_Letters()                     { s_doTest(testData[13]); }
    void testInvalidInput_MinutesRange()                { s_doTest(testData[14]); }
    void testInvalidInput_HoursRange()                  { s_doTest(testData[15]); }
    void testInvalidInput_TooLong()                     { s_doTest(testData[16]); }
};
