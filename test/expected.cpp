#include <gtest/gtest.h>

#include <ex/policy/notice>

#define EX_NOTICE_POLICY ex::policy::ThrowNotice<std::logic_error>
#include <ex/expected>


TEST(expected_test, valid_value_check)
{
    auto e = ex::expected<int>(1000);

    ASSERT_TRUE(e.is_valid());
    ASSERT_TRUE(e);
    ASSERT_TRUE(e.get() == 1000);
}


TEST(expected_test, exception_value_check)
{
    auto e = ex::expected<int>(std::runtime_error("Ops!"));

    ASSERT_FALSE(e.is_valid());
    ASSERT_FALSE(e);
    ASSERT_TRUE(e.has_exception<std::runtime_error>());
}


TEST(expected_test, rethrow_check)
{
    auto e = ex::expected<int>(std::runtime_error("Ops!"));

    ASSERT_THROW(e.get(), std::runtime_error);
    ASSERT_THROW(e.rethrow(), std::runtime_error);
}


TEST(expected_test, current_exception_check)
{
    auto e = []
    {
        try
        {
            throw std::logic_error("Ops!");
        }
        catch(...)
        {
            return ex::expected<int>::current_exception();
        }
    }();

    ASSERT_TRUE(e.has_exception<std::logic_error>());
    ASSERT_THROW(e.rethrow(), std::logic_error);
}


TEST(expected_test, slicing_check)
{
    auto test = []
    {
        try
        {
            throw std::logic_error("Ops!");
        }
        catch(std::exception& e)
        {
            return ex::expected<int>(e);
        }
    };


    ASSERT_THROW(test(), std::logic_error);
}


TEST(expected_test, swap_value_check)
{
    ex::expected<int> e1(1);
    ex::expected<int> e2(2);

    swap(e1, e2);
    ASSERT_TRUE(e1.get() == 2);
    ASSERT_TRUE(e2.get() == 1);
}


TEST(expected_test, swap_exception_check)
{
    ex::expected<int> e1(std::runtime_error("1"));
    ex::expected<int> e2(std::logic_error("2"));

    swap(e1, e2);
    ASSERT_TRUE(e1.has_exception<std::logic_error>());
    ASSERT_TRUE(e2.has_exception<std::runtime_error>());
}


TEST(expected_test, swap_mixed_check)
{
    ex::expected<int> e1(1);
    ex::expected<int> e2(std::logic_error("2"));

    swap(e1, e2);
    ASSERT_TRUE(e1.has_exception<std::logic_error>());
    ASSERT_TRUE(e2.is_valid());
    ASSERT_TRUE(e2.get() == 1);

    swap(e1, e2);
    ASSERT_TRUE(e2.has_exception<std::logic_error>());
    ASSERT_TRUE(e1.is_valid());
    ASSERT_TRUE(e1.get() == 1);
}
