#include <gtest/gtest.h>
#include <ex/window>
#include <array>


TEST(window, min_window_3)
{
    int test_data_1[] = { 1, 2, 3, 4, 5, 6, 7 };
    int test_data_2[] = { 7, 6, 5, 4, 3, 2, 1 };
    int test_data_3[] = { 2, 2, 2, 0, 2, 2, 2 };

    int expected_1[]  = { 1, 1, 1, 2, 3, 4, 5, 6, 7 };
    int expected_2[]  = { 7, 6, 5, 4, 3, 2, 1, 1, 1 };
    int expected_3[]  = { 2, 2, 2, 0, 0, 0, 2, 2, 2 };

    ex::MinWindow<int> w1(3, test_data_1);
    ex::MinWindow<int> w2(3, test_data_2);
    ex::MinWindow<int> w3(3, test_data_3);

    for (int i = 0; i < 9; ++i)
    {
        w1.next();
        w2.next();
        w3.next();

        ASSERT_TRUE(w1.minimum() == expected_1[i]);
        ASSERT_TRUE(w2.minimum() == expected_2[i]);
        ASSERT_TRUE(w3.minimum() == expected_3[i]);
    }
}


TEST(window, min_window_5)
{
    int test_data_1[] = { 1, 2, 3, 4, 5, 6, 7 };
    int test_data_2[] = { 7, 6, 5, 4, 3, 2, 1 };
    int test_data_3[] = { 2, 2, 2, 0, 2, 2, 2 };

    int expected_1[]  = { 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7 };
    int expected_2[]  = { 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1 };
    int expected_3[]  = { 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2 };

    ex::MinWindow<int> w1(5, test_data_1);
    ex::MinWindow<int> w2(5, test_data_2);
    ex::MinWindow<int> w3(5, test_data_3);

    for (int i = 0; i < 11; ++i)
    {
        w1.next();
        w2.next();
        w3.next();

        ASSERT_TRUE(w1.minimum() == expected_1[i]);
        ASSERT_TRUE(w2.minimum() == expected_2[i]);
        ASSERT_TRUE(w3.minimum() == expected_3[i]);
    }
}


TEST(window, min_window_large)
{
    int test_data[] = { 2, 2, 2, 0, 2, 2, 2 };
    int expected[]  = { 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2 };

    ex::MinWindow<int> w1(8, test_data);

    for (int i = 0; i < 14; ++i)
    {
        w1.next();

        ASSERT_TRUE(w1.minimum() == expected[i]);
    }
}



TEST(window, max_window_3)
{
    int test_data_1[] = { 1, 2, 3, 4, 5, 6, 7 };
    int test_data_2[] = { 7, 6, 5, 4, 3, 2, 1 };
    int test_data_3[] = { 2, 2, 2, 4, 2, 2, 2 };

    int expected_1[]  = { 1, 2, 3, 4, 5, 6, 7, 7, 7 };
    int expected_2[]  = { 7, 7, 7, 6, 5, 4, 3, 2, 1 };
    int expected_3[]  = { 2, 2, 2, 4, 4, 4, 2, 2, 2 };

    ex::MaxWindow<int> w1(3, test_data_1);
    ex::MaxWindow<int> w2(3, test_data_2);
    ex::MaxWindow<int> w3(3, test_data_3);

    for (int i = 0; i < 9; ++i)
    {
        w1.next();
        w2.next();
        w3.next();

        ASSERT_TRUE(w1.maximum() == expected_1[i]);
        ASSERT_TRUE(w2.maximum() == expected_2[i]);
        ASSERT_TRUE(w3.maximum() == expected_3[i]);
    }
}


TEST(window, max_window_5)
{
    int test_data_1[] = { 1, 2, 3, 4, 5, 6, 7 };
    int test_data_2[] = { 7, 6, 5, 4, 3, 2, 1 };
    int test_data_3[] = { 2, 2, 2, 4, 2, 2, 2 };

    int expected_1[]   = { 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7 };
    int expected_2[]   = { 7, 7, 7, 7, 7, 6, 5, 4, 3, 2, 1 };
    int expected_3[]   = { 2, 2, 2, 4, 4, 4, 4, 4, 2, 2, 2 };
    int expected_cnt[] = { 1, 2, 3, 4, 5, 5, 5, 4, 3, 2, 1 };

    ex::MaxWindow<int> w1(5, test_data_1);
    ex::MaxWindow<int> w2(5, test_data_2);
    ex::MaxWindow<int> w3(5, test_data_3);

    for (int i = 0; i < 11; ++i)
    {
        w1.next();
        w2.next();
        w3.next();

        ASSERT_TRUE(w1.maximum() == expected_1[i]);
        ASSERT_TRUE(w2.maximum() == expected_2[i]);
        ASSERT_TRUE(w3.maximum() == expected_3[i]);

        ASSERT_TRUE(w1.count() == expected_cnt[i]);
        ASSERT_TRUE(w2.count() == expected_cnt[i]);
        ASSERT_TRUE(w3.count() == expected_cnt[i]);
    }
}


TEST(window, max_window_large)
{
    int test_data[] = { 2, 2, 2, 4, 2, 2, 2 };
    int expected[]  = { 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2 };

    ex::MaxWindow<int> w1(8, test_data);

    for (int i = 0; i < 14; ++i)
    {
        w1.next();
        ASSERT_TRUE(w1.maximum() == expected[i]);
    }
}


TEST(window, class_check)
{
    std::array<int, 7> data = { 2, 2, 2, 4, 2, 2, 2 };
    int expected[]  = { 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2 };

    using ConstIterator = std::array<int, 7>::const_iterator;

    ex::MaxWindow<int, ConstIterator> w1(8, data.begin(), data.end());

    for (int i = 0; i < 14; ++i)
    {
        w1.next();
        ASSERT_TRUE(w1.maximum() == expected[i]);
    }
}


TEST(window, reset_check)
{
    std::array<int, 7> data = { 2, 2, 2, 4, 2, 2, 2 };
    int expected[]  = { 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2 };

    using ConstIterator = std::array<int, 7>::const_iterator;

    ex::MaxWindow<int, ConstIterator> w1(8, data.begin(), data.end());

    for (int i = 0; i < 7; ++i)
    {
        w1.next();
        ASSERT_TRUE(w1.maximum() == expected[i]);
    }

    w1.reset();

    for (int i = 0; i < 14; ++i)
    {
        w1.next();

        ASSERT_TRUE(w1.maximum() == expected[i]);
    }
}