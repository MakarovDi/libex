#include <gtest/gtest.h>

#include <ex/ct/strcat>
#include <ex/ct/streq>
#include <ex/meta/sequence>


using namespace ex;



TEST(ct_strcat_test, strcat_check)
{
    static_assert( ct::strcat("Te", "st") == "Test", "strcat failure");
    static_assert( ct::strcat(ct::meta_str("Te"), ct::meta_str("st")) == "Test", "strcat failure");

    static_assert( ct::strcat(L"Te", L"st") == L"Test", "strcat failure");
    static_assert( ct::strcat(ct::meta_str(L"Te"), ct::meta_str(L"st")) == L"Test", "strcat failure");

    static_assert( ct::strcat("Te\0\0\0\0", "st") == "Test", "strcat failure");
    static_assert( ct::strcat("Te", "st\0\0\0\0") == "Test", "strcat failure");

    static_assert( ct::strcat("Te\0\0\0\0", "st\0\0\0\0") == "Test", "strcat failure");
    static_assert( ct::strcat("Te", "st\0\0\0\0") == "Test", "strcat failure");
    static_assert( ct::strcat("\0Te\0\0\0\0", "st\0\0\0\0") == "st", "strcat failure");
    static_assert( ct::strcat("Te\0\0\0\0", "\0st\0\0\0\0") == "Te", "strcat failure");
    static_assert( ct::strcat("\0Te\0\0\0\0", "\0st\0\0\0\0") == "", "strcat failure");
    static_assert( ct::strcat("", "st") == "st", "strcat failure");
    static_assert( ct::strcat("Te", "") == "Te", "strcat failure");

    static_assert( ct::strcat("", "") == "", "strcat failure");
    static_assert( ct::strcat(L"", L"") == L"", "strcat failure");

    static_assert( ct::strcat("", "").size == 1, "strcat failure");
    static_assert( ct::strcat(L"", L"").size == 1, "strcat failure");
    static_assert( ct::strcat("Te", "st").size == 5, "strcat size failure");
    static_assert( ct::strcat(L"Te", L"st").size == 5, "strcat size failure");

    static_assert( ct::strcat("Te\0\0\0", "st").size == 8, "strcat size failure");
    static_assert( ct::strcat("Te", "st\0\0\0").size == 8, "strcat size failure");
    static_assert( ct::strcat("\0\0\0Te", "st").size == 8, "strcat size failure");
    static_assert( ct::strcat("Te", "\0\0\0st").size == 8, "strcat size failure");
}


TEST(ct_strcat_test, strcat_operator_check)
{
    static_assert(ct::meta_str("Te") + "st" == "Test", "strcat operator failure");
    static_assert("Te" + ct::meta_str("st") == "Test", "strcat operator failure");
    static_assert(ct::meta_str("Te") + ct::meta_str("st") == "Test", "strcat operator failure");
}