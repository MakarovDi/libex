#include <gtest/gtest.h>


#include <ex/ct/strcat>


using namespace ex;


template <typename CharType, size_t N>
constexpr auto process_str(const CharType (&str)[N]) -> decltype(ct::meta_str(str))
{
    return ct::meta_str(str);
}



TEST(ct_meta_str_test, compile_time_size_check)
{
    static_assert(ct::meta_str("test").size == 5, "meta_str size check");
    static_assert(ct::meta_str("test").size == ct::meta_str(L"test").size, "size should be independent of encoding");

    static_assert(ct::meta_str("").size == 1, "meta_str size check");
    static_assert(ct::meta_str(L"").size == 1, "meta_str size check");

    static_assert(ct::meta_str("\0").size == 2, "meta_str size check");
    static_assert(ct::meta_str(L"\0").size == 2, "meta_str size check");
}


TEST(ct_meta_str_test, compile_time_processing)
{
    static_assert(process_str("Test").size == 5, "compile-time processing test");
    static_assert(process_str(L"Test").size == 5, "compile-time processing test");
}


TEST(ct_meta_str_test, compile_time_indexing)
{
    static_assert(ct::meta_str("")[0] == '\0', "compile-time indexing");
    static_assert(ct::meta_str(L"")[0] == L'\0', "compile-time indexing");

    static_assert(ct::meta_str("Test")[2] == 's', "compile-time indexing");
    static_assert(ct::meta_str(L"Test")[2] == L's', "compile-time indexing");
    static_assert(ct::meta_str("Test")[0] == 'T', "compile-time indexing");
    static_assert(ct::meta_str(L"Test")[0] == L'T', "compile-time indexing");
    static_assert(ct::meta_str("Test")[4] == '\0', "compile-time indexing");
    static_assert(ct::meta_str(L"Test")[4] == L'\0', "compile-time indexing");
}

