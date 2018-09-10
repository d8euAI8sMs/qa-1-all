#include <calculator/quadeq.hpp>

namespace calculator
{

    int quadeq_solve(double a, double b, double c, double & x1, double & x2)
    {
        if (a == 0) return quadeq_error_notsqreq;
        double d = b * b - 4 * a * c;
        if (d < 0) return quadeq_error_negdiscr;
        x1 = (b - std::sqrt(d)) / 2 / a;
        x2 = (b + std::sqrt(d)) / 2 / a;
        return quadeq_error_success;
    }

}