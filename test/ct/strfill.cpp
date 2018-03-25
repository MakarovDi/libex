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

    static_assert(ct::strfill<wchar_t, 3, L'f'>().size == 4, "wrong strfill size");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[0] == L'f', "wrong strfill char");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[1] == L'f', "wrong strfill char");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[2] == L'f', "wrong strfill char");
    static_assert(ct::strfill<wchar_t, 3, L'f'>()[3] == L'\0', "wrong strfill char");
}
