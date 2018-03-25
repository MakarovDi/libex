#include <gtest/gtest.h>

#include <ex/ct/substr>
#include <ex/ct/streq>


using namespace ex;


TEST(ct_substr_test, substr_check)
{
    static_assert(ct::substr<2>("Test") == "st", "substr failure");
    static_assert(ct::substr<2>(L"Test") == L"st", "substr failure");
    static_assert(ct::substr<2>("Test") == ct::meta_str("st"), "substr failure");
    static_assert(ct::substr<2>(L"Test") == ct::meta_str(L"st"), "substr failure");


    static_assert(ct::substr<0>("Test") == "Test", "substr failure");
    static_assert(ct::substr<0>(L"Test") == L"Test", "substr failure");

    static_assert(ct::substr<4>("Test") == "", "substr failure");
    static_assert(ct::substr<4>(L"Test") == L"", "substr failure");
}