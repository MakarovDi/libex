#include <gtest/gtest.h>

#include <ex/ct/set_char>


using namespace ex;


TEST(ct_char_test, set_char_check)
{
    static_assert(ct::set_char<0>("te", 'a')[0] == 'a', "set_char failure");
    static_assert(ct::set_char<0>("te", 'a')[1] == 'e', "set_char failure");
    static_assert(ct::set_char<0>(L"te", L'a')[0] == 'a', "set_char failure");
    static_assert(ct::set_char<0>(L"te", L'a')[1] == 'e', "set_char failure");

    static_assert(ct::set_char<0>("te", 'a').size == 3, "set_char failure");
    static_assert(ct::set_char<0>(L"te", L'a').size == 3, "set_char failure");
}