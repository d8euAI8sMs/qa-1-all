#pragma once

#include "testutils.hpp"

#include <string>

#include <calculator/quadeq.hpp>

class QuadEqTest : public CppUnit::TestFixture
{

public:

    static std::string name() { return "QuadEqTest"; }

    CPPUNIT_TEST_SUITE(QuadEqTest);
        CPPUNIT_TEST(_GWT(
            quadsq_solve,
            nonQuadEq,
            returnErrorCode));
        CPPUNIT_TEST(_GWT(
            quadsq_solve,
            negDiscr,
            returnErrorCode));
        CPPUNIT_TEST(_GWT(
            quadsq_solve,
            posDiscr,
            returnSuccessAndProperRoots));
    CPPUNIT_TEST_SUITE_END();

public:

    _CPPUNIT_DECLARE_TEST(
        quadsq_solve,
        nonQuadEq,
        returnErrorCode)
    {
        double x1, x2;
        auto r = calculator::quadeq_solve(0, 1, 2, x1, x2);
        CPPUNIT_ASSERT_EQUAL(static_cast<int>(calculator::quadeq_error_notsqreq), r);
    }
    
    _CPPUNIT_DECLARE_TEST(
        quadsq_solve,
        negDiscr,
        returnErrorCode)
    {
        double x1, x2;
        auto r = calculator::quadeq_solve(1, 0, 4, x1, x2);
        CPPUNIT_ASSERT_EQUAL(static_cast<int>(calculator::quadeq_error_negdiscr), r);
    }
    
    _CPPUNIT_DECLARE_TEST(
        quadsq_solve,
        posDiscr,
        returnSuccessAndProperRoots)
    {
        double x1, x2;
        auto r = calculator::quadeq_solve(5, 4, -1, x1, x2);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("success",
                static_cast<int>(calculator::quadeq_error_success), r);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("1st root",
                -1, x1, 1e-15);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("2nd root",
                0.2, x2, 1e-15);
    }
};
