#pragma once

#include "testutils.hpp"

#include <string>

#include <calculator/quadeq.hpp>

class QuadEqBBDTest : public CppUnit::TestFixture
{

public:

    static std::string name() { return "QuadEqBBDTest"; }

    CPPUNIT_TEST_SUITE(QuadEqBBDTest);
        _CPPUNIT_NAMED_TEST(
            "WHEN the given equation is not an equation of 2nd order "
            "THEN the function should return [quadeq_error_notsqreq] "
            "indicating the error",
            _GWT(
            quadsq_solve,
            nonQuadEq,
            returnErrorCode));
        _CPPUNIT_NAMED_TEST(
            "WHEN no solution exists (discriminant is less than 0) "
            "in class of quadratic equations with all coefficients specified "
            "THEN the function should return [quadeq_error_negdiscr] "
            "indicating the error",
            _GWT(
            quadsq_solve,
            negDiscrWithAllCoefs,
            returnErrorCode));
        _CPPUNIT_NAMED_TEST(
            "WHEN no solution exists (discriminant is less than 0) "
            "in class of quadratic equations in symmetric form (B "
            "coefficient in front X is zero) "
            "THEN the function should return [quadeq_error_negdiscr] "
            "indicating the error",
            _GWT(
            quadsq_solve,
            negDiscrZeroB,
            returnErrorCode));
        _CPPUNIT_NAMED_TEST(
            "WHEN the given equation has two distinct non-symmetric roots "
            "THEN the function should return [quadeq_error_success] "
            "and populate the roots with their values",
            _GWT(
            quadsq_solve,
            posDiscrNonSymmetric,
            returnSuccessAndPopulateRoots));
        _CPPUNIT_NAMED_TEST(
            "WHEN the given equation has two distinct symmetric roots "
            "THEN the function should return [quadeq_error_success] "
            "and populate the roots with their values",
            _GWT(
            quadsq_solve,
            posDiscrSymmetric,
            returnSuccessAndPopulateRoots));
        _CPPUNIT_NAMED_TEST(
            "WHEN the given equation has two same roots (discriminant is zero) "
            "THEN the function should return [quadeq_error_success] "
            "and populate the roots with their values",
            _GWT(
            quadsq_solve,
            zeroDiscr,
            returnSuccessAndPopulateRoots));
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
        negDiscrWithAllCoefs,
        returnErrorCode)
    {
        double x1, x2;
        auto r = calculator::quadeq_solve(1, 1, 4, x1, x2);
        CPPUNIT_ASSERT_EQUAL(static_cast<int>(calculator::quadeq_error_negdiscr), r);
    }
    
    _CPPUNIT_DECLARE_TEST(
        quadsq_solve,
        negDiscrZeroB,
        returnErrorCode)
    {
        double x1, x2;
        auto r = calculator::quadeq_solve(1, 0, 4, x1, x2);
        CPPUNIT_ASSERT_EQUAL(static_cast<int>(calculator::quadeq_error_negdiscr), r);
    }
    
    _CPPUNIT_DECLARE_TEST(
        quadsq_solve,
        posDiscrNonSymmetric,
        returnSuccessAndPopulateRoots)
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

    _CPPUNIT_DECLARE_TEST(
        quadsq_solve,
        posDiscrSymmetric,
        returnSuccessAndPopulateRoots)
    {
        double x1, x2;
        auto r = calculator::quadeq_solve(1, 0, -4, x1, x2);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("success",
                static_cast<int>(calculator::quadeq_error_success), r);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("1st root",
                -2, x1, 1e-15);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("2nd root",
                2, x2, 1e-15);
    }

    _CPPUNIT_DECLARE_TEST(
        quadsq_solve,
        zeroDiscr,
        returnSuccessAndPopulateRoots)
    {
        double x1, x2;
        auto r = calculator::quadeq_solve(1, -8, 16, x1, x2);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("success",
                static_cast<int>(calculator::quadeq_error_success), r);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("1st root",
                4, x1, 1e-15);
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("2nd root",
                4, x2, 1e-15);
    }
};
