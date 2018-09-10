#pragma once

#include <cmath>

#include <calculator/calculator_api.hpp>

namespace calculator
{

    enum quadeq_error : int
    {
        quadeq_error_success = 0,
        /* when discriminant is negative */
        quadeq_error_negdiscr,
        /* when the passed equation is not of the 2nd order (a = 0) */
        quadeq_error_notsqreq
    };

    /**
     * Solves the 2nd order equation given by its
     * coefficients (a, b, c):
     * 
     * <p/>
     * {@code a x^2 + b x + c = 0}
     * 
     * <p/>
     * Places the first and the second roots to `x1`
     * and `x2` respectively.
     * 
     * @param a Coefficient of x^2
     * @param b Coefficient of x
     * @param c Constant term
     * 
     * @param x1 The first root
     * @param x2 The second root
     * 
     * @return Error code ({@see quadeq_error above})
     */
    CALCULATOR_API int quadeq_solve(double a, double b, double c,
                                    double & x1, double & x2);

} /* namespace calculator */