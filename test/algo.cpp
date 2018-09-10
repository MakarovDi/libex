#include <gtest/gtest.h>
#include <ex/algo>


TEST(algo, last_min)
{
    int data[] = { 1, 1, 5, 2, 3, 2, 0, 0 };


    auto start = &data[2];
    auto end  = &data[6];

    ASSERT_EQ(ex::last_min_element(start, end), &data[5]);
}


TEST(algo, last_min_empty)
{
    int data[] = { 1, 1, 5, 2, 3, 2, 0, 0 };


    auto start = &data[6];
    auto end  = &data[6];

    ASSERT_EQ(ex::last_min_element(start, end), end);
}


TEST(algo, last_max)
{
    int data[] = { 10, 10, 5, 6, 3, 6, 9, 9 };


    auto start = &data[2];
    auto end  = &data[6];

    ASSERT_EQ(ex::last_max_element(start, end), &data[5]);
}


TEST(algo, last_max_empty)
{
    int data[] = { 1, 1, 5, 2, 3, 2, 0, 0 };


    auto start = &data[6];
    auto end  = &data[6];

    ASSERT_EQ(ex::last_max_element(start, end), end);
}