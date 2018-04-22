#include <gtest/gtest.h>
#include <ex/range_check>


using namespace ex;


TEST(range_check_test, range_check)
{
    ASSERT_NO_THROW(range_check(0, -1, 1));
    ASSERT_NO_THROW(range_check(0.0, -1.0, 1.0));
    ASSERT_NO_THROW(range_check(0, 1));
    ASSERT_NO_THROW(range_check(0.0, 1.0));

    ASSERT_THROW(range_check(2, -1, 1), std::overflow_error);
    ASSERT_THROW(range_check(2.0, -1.0, 1.0), std::overflow_error);
    ASSERT_THROW(range_check(2, 1), std::overflow_error);
    ASSERT_THROW(range_check(2.0, 1.0), std::overflow_error);
}


// uint64 -> uint32
TEST(range_check_test, uint64_to_int32_size)
{
    ASSERT_NO_THROW(range_check<uint64_t>(std::numeric_limits<uint32_t>::min()));
    ASSERT_NO_THROW(range_check<uint64_t>(std::numeric_limits<uint32_t>::max()));
}


// uint64 -> uint32
TEST(range_check_test, uint64_to_uint32_size)
{
    ASSERT_NO_THROW(range_check<uint32_t>(std::numeric_limits<uint64_t>::min()));
    ASSERT_NO_THROW(range_check<uint32_t>(uint64_t(std::numeric_limits<uint32_t>::max())));
    ASSERT_THROW(range_check<uint32_t>(std::numeric_limits<uint64_t>::max()), std::overflow_error);
}


// uint32 -> int32
TEST(range_check_test, uint32_to_int32_size)
{
    ASSERT_NO_THROW(range_check<int32_t>(std::numeric_limits<uint32_t>::min()));
    ASSERT_NO_THROW(range_check<int32_t>(uint32_t(std::numeric_limits<int32_t>::max())));
    ASSERT_THROW(range_check<int32_t>(std::numeric_limits<uint32_t>::max()), std::overflow_error);
}


// int32 -> uint32
TEST(range_check_test, int32_to_uint32_size)
{
    ASSERT_NO_THROW(range_check<uint32_t>(std::numeric_limits<int32_t>::max()));
    ASSERT_THROW(range_check<uint32_t>(std::numeric_limits<int32_t>::min()), std::overflow_error);
}


// uint32 -> int64
TEST(range_check_test, uint32_to_int64_size)
{
    ASSERT_NO_THROW(range_check<int64_t>(std::numeric_limits<uint32_t>::min()));
    ASSERT_NO_THROW(range_check<int64_t>(std::numeric_limits<uint32_t>::max()));
}


// int32 -> uint64
TEST(range_check_test, int32_to_uint64_size)
{
    ASSERT_NO_THROW(range_check<uint64_t>(std::numeric_limits<int32_t>::max()));
    ASSERT_THROW(range_check<uint64_t>(std::numeric_limits<int32_t>::min()), std::overflow_error);
}


// int32 -> int64
TEST(range_check_test, int32_to_int64_size)
{
    ASSERT_NO_THROW(range_check<int64_t>(std::numeric_limits<int32_t>::min()));
    ASSERT_NO_THROW(range_check<int64_t>(std::numeric_limits<int32_t>::max()));
}


// int64 -> uint32
TEST(range_check_test, int64_to_uint32_size)
{
    ASSERT_NO_THROW(range_check<uint32_t>(int64_t(std::numeric_limits<uint32_t>::min())));
    ASSERT_THROW(range_check<uint32_t>(std::numeric_limits<int64_t>::max()), std::overflow_error);
    ASSERT_THROW(range_check<uint32_t>(std::numeric_limits<int64_t>::min()), std::overflow_error);
}


// int64 -> int32
TEST(range_check_test, int64_to_int32_size)
{
    ASSERT_NO_THROW(range_check<int32_t>(int64_t(std::numeric_limits<int32_t>::min())));
    ASSERT_NO_THROW(range_check<int32_t>(int64_t(std::numeric_limits<int32_t>::max())));
    ASSERT_THROW(range_check<int32_t>(std::numeric_limits<int64_t>::max()), std::overflow_error);
    ASSERT_THROW(range_check<int32_t>(std::numeric_limits<int64_t>::min()), std::overflow_error);
}
