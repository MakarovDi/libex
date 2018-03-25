#include <gtest/gtest.h>

#include <ex/ct/math>


using namespace ex;


TEST(ct_math_test, math_check)
{
    static_assert(ct::abs(-1) == 1, "abs failure");
    static_assert(ct::abs(1) == 1, "abs failure");
    static_assert(ct::abs(1.0) == 1.0, "abs failure");
    static_assert(ct::abs(-1.0) == 1.0, "abs failure");

    static_assert(ct::factorial(0) == 1, "abs failure");
    static_assert(ct::factorial(1) == 1, "abs failure");
    static_assert(ct::factorial(2) == 2, "abs failure");
    static_assert(ct::factorial(4) == 2*3*4, "abs failure");
    static_assert(ct::factorial(4.0) == 2.0*3.0*4.0, "abs failure");

    static_assert(ct::sqrt(4) == 2, "abs failure");
    static_assert(ct::sqrt(16) == 4, "abs failure");
    static_assert(ct::abs(ct::sqrt(15.0) - 3.87298334) < 1e-8, "abs failure");
    static_assert(ct::sqrt(15) == 3, "abs failure");
}
