#include <gtest/gtest.h>

#include <ex/ct/char>


using namespace ex;


TEST(ct_char_test, select_char_check)
{
    static_assert(ct::select_char<char>(L'c', 'w', u'6', U'3') == 'w', "wrong char selected");
    static_assert(ct::select_char<char16_t>(L'c', 'w', u'6', U'3') == u'6', "wrong char selected");
    static_assert(ct::select_char<char32_t>(L'c', 'w', u'6', U'3') == U'3', "wrong char selected");
    static_assert(ct::select_char<wchar_t>(L'c', 'w', u'6', U'3') == L'c', "wrong char selected");

    static_assert(ct::select_char<wchar_t>(L'\0', 'w', u'6', U'3') == L'\0', "wrong char selected");
}


TEST(ct_char_test, contains_char_check)
{
    static_assert(ct::contains_char("test", 'e'), "must contain e");
    static_assert(ct::contains_char(L"test", L'e'), "must contain e");

    static_assert(ct::contains_char(L"test", L'\0'), "must contain e");
}


TEST(ct_char_test, char_at_check)
{
    static_assert(ct::char_at<2>("123") == '3', "char_at failure");
    static_assert(ct::char_at<2>(u"123") == u'3', "char_at failure");
    static_assert(ct::char_at<2>(U"123") == U'3', "char_at failure");
    static_assert(ct::char_at<2>(L"123") == L'3', "char_at failure");
}


TEST(ct_char_test, strlchr_check)
{
    static_assert(ct::strlchr("test", 't') == 0, "strlchr failure");
    static_assert(ct::strlchr("test", '\0') == 4, "strlchr failure");
    static_assert(ct::strlchr("test", 'a') == ct::npos, "strlchr failure");
    static_assert(ct::strlchr("", 'a') == ct::npos, "strlchr failure");

    static_assert(ct::strlchr(L"test", L't') == 0, "strlchr failure");
    static_assert(ct::strlchr(L"test", L'\0') == 4, "strlchr failure");
    static_assert(ct::strlchr(L"test", L'a') == ct::npos, "strlchr failure");
    static_assert(ct::strlchr(L"", L'a') == ct::npos, "strlchr failure");
}


TEST(ct_char_test, strrchr_check)
{
    static_assert(ct::strrchr("test", 't') == 3, "strrchr failure");
    static_assert(ct::strrchr("test", '\0') == 4, "strrchr failure");
    static_assert(ct::strrchr("test", 'a') == ct::npos, "strrchr failure");
    static_assert(ct::strrchr("", 'a') == ct::npos, "strrchr failure");

    static_assert(ct::strrchr(L"test", L't') == 3, "strrchr failure");
    static_assert(ct::strrchr(L"test", L'\0') == 4, "strrchr failure");
    static_assert(ct::strrchr(L"test", L'a') == ct::npos, "strrchr failure");
    static_assert(ct::strrchr(L"", L'a') == ct::npos, "strrchr failure");
}
