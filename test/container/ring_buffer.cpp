#include <gtest/gtest.h>

#include <ex/policy/notice>

#define EX_NOTICE_POLICY ex::policy::ThrowNotice<std::logic_error>
#include <ex/container/ring_buffer>


TEST(ring_buffer, empty_access)
{
    ex::RingBuffer<int> buf(3);

    ASSERT_TRUE(buf.is_empty());
    ASSERT_TRUE(!buf.is_full());
    ASSERT_TRUE(buf.count() == 0);

    ASSERT_THROW(buf.front(), std::logic_error);
    ASSERT_THROW(buf.back(), std::logic_error);
    ASSERT_THROW(buf.pop_back(), std::logic_error);
    ASSERT_THROW(buf.pop_front(), std::logic_error);
}


TEST(ring_buffer, check_push_back)
{
    ex::RingBuffer<int> buf(3);

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);

    ASSERT_TRUE(buf.count() == 3);
    ASSERT_TRUE(buf.is_full());
    ASSERT_TRUE(!buf.is_empty());

    ASSERT_TRUE(buf.front() == 1);
    ASSERT_TRUE(buf.back() == 3);
}


TEST(ring_buffer, pop_back)
{
    ex::RingBuffer<int> buf(3);

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);

    ASSERT_TRUE(buf.front() == 1);
    ASSERT_TRUE(buf.back() == 3);
    ASSERT_TRUE(buf.count() == 3);

    ASSERT_TRUE(buf.pop_back() == 3);
    ASSERT_TRUE(buf.front() == 1);
    ASSERT_TRUE(buf.back() == 2);
    ASSERT_TRUE(buf.count() == 2);

    ASSERT_TRUE(buf.pop_back() == 2);
    ASSERT_TRUE(buf.front() == 1);
    ASSERT_TRUE(buf.back() == 1);
    ASSERT_TRUE(buf.count() == 1);
}


TEST(ring_buffer, pop_front)
{
    ex::RingBuffer<int> buf(3);

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);

    ASSERT_TRUE(buf.front() == 1);
    ASSERT_TRUE(buf.back() == 3);
    ASSERT_TRUE(buf.count() == 3);

    ASSERT_TRUE(buf.pop_front() == 1);
    ASSERT_TRUE(buf.front() == 2);
    ASSERT_TRUE(buf.back() == 3);
    ASSERT_TRUE(buf.count() == 2);

    ASSERT_TRUE(buf.pop_front() == 2);
    ASSERT_TRUE(buf.front() == 3);
    ASSERT_TRUE(buf.back() == 3);
    ASSERT_TRUE(buf.count() == 1);
}


TEST(ring_buffer, pop_to_zero)
{
    ex::RingBuffer<int> buf(3);

    buf.push_back(1);
    buf.push_back(2);

    buf.pop_front();
    buf.pop_back();

    ASSERT_TRUE(buf.is_empty());
    ASSERT_TRUE(buf.count() == 0);

    ASSERT_THROW(buf.front(), std::logic_error);
    ASSERT_THROW(buf.back(), std::logic_error);

    buf.push_back(0);

    ASSERT_TRUE(buf.front() == 0);
    ASSERT_TRUE(buf.back() == 0);
    ASSERT_TRUE(buf.count() == 1);

    buf.push_back(4);

    ASSERT_TRUE(buf.front() == 0);
    ASSERT_TRUE(buf.back() == 4);
    ASSERT_TRUE(buf.count() == 2);
}


TEST(ring_buffer, circling_back)
{
    ex::RingBuffer<int> buf(3);

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);

    ASSERT_TRUE(buf.count() == 3);
    ASSERT_TRUE(buf.is_full());
    ASSERT_TRUE(buf.front() == 1);
    ASSERT_TRUE(buf.back() == 3);

    buf.push_back(4);

    ASSERT_TRUE(buf.count() == 3);
    ASSERT_TRUE(buf.is_full());
    ASSERT_TRUE(buf.front() == 2);
    ASSERT_TRUE(buf.back() == 4);

    buf.pop_back();

    ASSERT_TRUE(buf.count() == 2);
    ASSERT_TRUE(!buf.is_full());
    ASSERT_TRUE(buf.front() == 2);
    ASSERT_TRUE(buf.back() == 3);
}


TEST(ring_buffer, circling_front)
{
    ex::RingBuffer<int> buf(3);

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);

    ASSERT_TRUE(buf.count() == 3);
    ASSERT_TRUE(buf.is_full());
    ASSERT_TRUE(buf.front() == 1);
    ASSERT_TRUE(buf.back() == 3);

    buf.push_back(4);
    buf.push_back(5);

    ASSERT_TRUE(buf.front() == 3);

    buf.pop_front();

    ASSERT_TRUE(buf.count() == 2);
    ASSERT_TRUE(!buf.is_full());
    ASSERT_TRUE(buf.front() == 4);
    ASSERT_TRUE(buf.back() == 5);
}


TEST(ring_buffer, indexing)
{
    ex::RingBuffer<int> buf(3);

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.push_back(4);

    ASSERT_TRUE(buf[0] == 2);
    ASSERT_TRUE(buf[1] == 3);
    ASSERT_TRUE(buf[2] == 4);
    ASSERT_TRUE(buf[3] == 2);

    buf.pop_front();

    ASSERT_THROW(buf[2], std::logic_error);
}


TEST(ring_buffer, clear)
{
    ex::RingBuffer<int> buf(3);

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.push_back(4);

    buf.clear();

    ASSERT_TRUE(buf.is_empty());
    ASSERT_TRUE(buf.count() == 0);

    buf.push_back(5);

    ASSERT_TRUE(buf.front() == 5);
    ASSERT_TRUE(buf.back() == 5);
    ASSERT_TRUE(buf.count() == 1);
}