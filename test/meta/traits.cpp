#include <gtest/gtest.h>
#include <ex/meta/traits>
#include <string>
#include <vector>


TEST(traits, check_pointers)
{
    ASSERT_TRUE(ex::has_index_operator<int*>::value == true);
    ASSERT_TRUE(ex::has_index_operator<std::string*>::value == true);
}


TEST(traits, check_false)
{
    ASSERT_FALSE(ex::has_index_operator<int>::value);

    struct A {};
    ASSERT_FALSE(ex::has_index_operator<A>::value);
}


TEST(traits, check_class)
{
    ASSERT_TRUE(ex::has_index_operator<std::string>::value == true);
}


TEST(traits, check_compile_time)
{
    static_assert(ex::has_index_operator<int*>::value, "compile-time check");
}


TEST(traits_iterator_type, check_pointer_iterator)
{
    using T1 = ex::iterator_type<int*>::type;
    using T2 = ex::iterator_type<const int*>::type;

    static_assert(std::is_same<T1, int*>::value == true, "iterator for pointer");
    static_assert(std::is_same<T2, const int*>::value == true, "iterator for pointer");
}


TEST(traits_iterator_type, check_class_iterator)
{
    using T1 = ex::iterator_type<std::vector<int>>::type;
    using T2 = ex::iterator_type<const std::vector<int>>::type;

    static_assert(std::is_same<T1, std::vector<int>::iterator>::value == true, "iterator for class");
    static_assert(std::is_same<T2, std::vector<int>::const_iterator>::value == true, "iterator for class");
}
