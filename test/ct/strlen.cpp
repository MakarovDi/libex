#include <gtest/gtest.h>

#include <ex/ct/strlen>


using namespace ex;


TEST(ct_strlen_test, strlen_check)
{
    static_assert(ct::strlen("123") == 3, "failure");
    static_assert(ct::strlen("") == 0, "failure");
    static_assert(ct::strlen("1") == 1, "failure");
    static_assert(ct::strlen("1\0\0\0\0") == 1, "failure");

    static_assert(ct::strlen(L"123") == 3, "failure");
    static_assert(ct::strlen(L"") == 0, "failure");
    static_assert(ct::strlen(L"1") == 1, "failure");
    static_assert(ct::strlen(L"1\0\0\0\0") == 1, "failure");
}
