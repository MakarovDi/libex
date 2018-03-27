#include <gtest/gtest.h>

#include <ex/ct/basename>
#include <ex/ct/streq>


using namespace ex;


TEST(ct_basename_test, basename_check)
{
    static_assert(ct::basename("test-path\\file.c") == "file.c", "basename failure");
    static_assert(ct::basename("test-path/file.c") == "file.c", "basename failure");
    static_assert(ct::basename("./file.c") == "file.c", "basename failure");
    static_assert(ct::basename("./file.c") == "file.c", "basename failure");
    static_assert(ct::basename("/") == "", "basename failure");
    static_assert(ct::basename("\\") == "", "basename failure");
    static_assert(ct::basename("") == "", "basename failure");


    static_assert(ct::basename(L"test-path\\file.c") == L"file.c", "basename failure");
    static_assert(ct::basename(L"test-path/file.c") == L"file.c", "basename failure");
    static_assert(ct::basename(L"./file.c") == L"file.c", "basename failure");
    static_assert(ct::basename(L"./file.c") == L"file.c", "basename failure");
    static_assert(ct::basename(L"/") == L"", "basename failure");
    static_assert(ct::basename(L"\\") == L"", "basename failure");
    static_assert(ct::basename(L"") == L"", "basename failure");
}