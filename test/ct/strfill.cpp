#include <gtest/gtest.h>

#include <ex/ct/strfill>


using namespace ex;


TEST(ct_strfill_test, strfill_check)
{
    static_assert(ct::strfill<char, 3, 'f'>().size == 4, "wrong strfill size");
    static_assert(ct::strfill<char, 3, 'f'>()[0] == 'f', "wrong strfill char");
    static_assert(ct::strfill<char, 3, 'f'>()[1] == 'f', "wrong strfill char");
    static_assert(ct::strfill<char, 3, 'f'>()[2] == 'f', "wrong strfill char");
    static_assert(ct::strfill<char, 3, 'f'>()[3] == '\0', "wrong strfill char");

    static_assert(ct::strfill<char, 0, 'f'>().size == 1, "wrong strpad size");
    static_assert(ct::strfill<char, 0, 'f'>()[0] == '\0', "wrong strpad size");

    static_assert(ct::strfill<wchar_t, 3, L'f'>().size == 4, "wrong strfill size");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[0] == L'f', "wrong strfill char");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[1] == L'f', "wrong strfill char");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[2] == L'f', "wrong strfill char");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[3] == L'\0', "wrong strfill char");

    static_assert(ct::strfill<wchar_t, 0, 'f'>().size == 1, "wrong strpad size");
    static_assert(ct::strfill<wchar_t, 0, 'f'>()[0] == L'\0', "wrong strpad size");
}


TEST(ct_strpad_test, strpad_check)
{
    static_assert(ct::strpad<char, 3>().size == 4, "wrong strpad size");
    static_assert(ct::strpad<char, 3>()[0] == '\0', "wrong strpad char");
    static_assert(ct::strpad<char, 3>()[1] == '\0', "wrong strpad char");
    static_assert(ct::strpad<char, 3>()[2] == '\0', "wrong strpad char");
    static_assert(ct::strpad<char, 3>()[3] == '\0', "wrong strpad char");

    static_assert(ct::strpad<char, 0>().size == 1, "wrong strpad size");
    static_assert(ct::strpad<char, 0>()[0] == '\0', "wrong strpad size");

    static_assert(ct::strfill<wchar_t, 3, L'f'>().size == 4, "wrong strfill size");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[0] == L'f', "wrong strfill char");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[1] == L'f', "wrong strfill char");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[2] == L'f', "wrong strfill char");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[3] == L'\0', "wrong strfill char");

    static_assert(ct::strpad<wchar_t, 0>().size == 1, "wrong strpad size");
    static_assert(ct::strpad<wchar_t, 0>()[0] == L'\0', "wrong strpad size");
}
