#include <gtest/gtest.h>

#include <ex/ct/streq>


using namespace ex;


TEST(ct_streq_test, streq_check)
{
    static_assert(ct::streq("Test", "Test"), "streq failure");
    static_assert(ct::streq("Test", "Test\0\0\0\0\0\0\0"), "streq failure");
    static_assert(ct::streq("Test\0\0\0", "Test\0\0\0\0\0\0\0"), "streq failure");
    static_assert(!ct::streq("Test", "Tost"), "streq failure");
    static_assert(!ct::streq("Test", "Tst"), "streq failure");
    static_assert(ct::streq("", ""), "streq failure");

    static_assert(ct::streq(L"Test", L"Test"), "streq failure");
    static_assert(ct::streq(L"Test", L"Test\0\0\0\0\0\0\0"), "streq failure");
    static_assert(ct::streq(L"Test\0\0", L"Test\0\0\0\0\0\0\0"), "streq failure");
    static_assert(!ct::streq(L"Test", L"Tost"), "streq failure");
    static_assert(!ct::streq(L"Test", L"Tst"), "streq failure");
    static_assert(ct::streq(L"", L""), "streq failure");


    static_assert(ct::streq(ct::meta_str("Test"), ct::meta_str("Test")), "streq failure");
    static_assert(ct::streq(ct::meta_str("Test"), ct::meta_str("Test\0\0\0\0\0\0\0")), "streq failure");
}


TEST(ct_streq_test, operator_eq_check)
{
    static_assert(ct::meta_str("123") == ct::meta_str("123"), "streq operator failure");
    static_assert(ct::meta_str("123") == "123", "streq operator failure");
    static_assert("123" == ct::meta_str("123"), "streq operator failure");

    static_assert(ct::meta_str(L"123") == ct::meta_str(L"123"), "streq operator failure");
    static_assert(ct::meta_str(L"123") == L"123", "streq operator failure");
    static_assert(L"123" == ct::meta_str(L"123"), "streq operator failure");
}
