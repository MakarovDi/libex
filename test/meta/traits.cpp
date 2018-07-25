#include <gtest/gtest.h>
#include <ex/meta/traits>
#include <string>


TEST(treits, check_pointers)
{
    ASSERT_TRUE(ex::has_index_operator<int*>::value);
    ASSERT_TRUE(ex::has_index_operator<std::string*>::value);
}


TEST(treits, check_false)
{
    ASSERT_FALSE(ex::has_index_operator<int>::value);

    struct A {};
    ASSERT_FALSE(ex::has_index_operator<A>::value);
}


TEST(treits, check_class)
{
    ASSERT_TRUE(ex::has_index_operator<std::string>::value);
}


TEST(treits, check_compile_time)
{
    static_assert(ex::has_index_operator<int*>::value, "compile-time check");
}



