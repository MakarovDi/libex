#include <gtest/gtest.h>

#include <ex/ct/charset>


using namespace ex;


TEST(ct_charset_test, zero_check)
{
    static_assert(ct::charset::zero<char>() == '\0', "wrong char");
    static_assert(ct::charset::zero<char16_t>() == u'\0', "wrong char");
    static_assert(ct::charset::zero<char32_t>() == U'\0', "wrong char");
    static_assert(ct::charset::zero<wchar_t>() == L'\0', "wrong char");
}


TEST(ct_charset_test, slash_check)
{
    static_assert(ct::charset::slash<char>() == '/', "wrong char");
    static_assert(ct::charset::slash<char16_t>() == u'/', "wrong char");
    static_assert(ct::charset::slash<char32_t>() == U'/', "wrong char");
    static_assert(ct::charset::slash<wchar_t>() == L'/', "wrong char");
}


TEST(ct_charset_test, back_slash_check)
{
    static_assert(ct::charset::back_slash<char>() == '\\', "wrong char");
    static_assert(ct::charset::back_slash<char16_t>() == u'\\', "wrong char");
    static_assert(ct::charset::back_slash<char32_t>() == U'\\', "wrong char");
    static_assert(ct::charset::back_slash<wchar_t>() == L'\\', "wrong char");
}
