#include <gtest/gtest.h>
#include <ex/encoding/word16>


TEST(word16_test, ctor_default_check)
{
    ex::word16 w;

    w.value = 0xFFAA;

    ASSERT_TRUE(w.low == 0xAA);
    ASSERT_TRUE(w.hi  == 0xFF);
}


TEST(word16_test, ctor_conversion_check)
{
    ex::word16 w(0xFFAA);

    ASSERT_TRUE(w.low == 0xAA);
    ASSERT_TRUE(w.hi  == 0xFF);

    ex::word16 w2 = 0xFFAA;

    ASSERT_TRUE(w2.low == 0xAA);
    ASSERT_TRUE(w2.hi  == 0xFF);
}


TEST(word16_test, ctor_combine_check)
{
    ex::word16 w(0xFF, 0xAA);

    ASSERT_TRUE(w.low == 0xAA);
    ASSERT_TRUE(w.hi  == 0xFF);
    ASSERT_TRUE(w.value  == 0xFFAA);
}


TEST(word16_test, ctor_initilizer_list_check)
{
    ex::word16 w = { 0xFF, 0xAA };

    ASSERT_TRUE(w.low == 0xAA);
    ASSERT_TRUE(w.hi  == 0xFF);
    ASSERT_TRUE(w.value  == 0xFFAA);

    ex::word16 w1 { 0xFF, 0xAA };

    ASSERT_TRUE(w1.low == 0xAA);
    ASSERT_TRUE(w1.hi  == 0xFF);
    ASSERT_TRUE(w1.value  == 0xFFAA);
}


TEST(word16_test, size_check)
{
    ex::word16 w;

    ASSERT_TRUE(sizeof(w) == 2);
}


TEST(word16_test, swap_check)
{
    ex::word16 w1 = 0xFF00;
    ex::word16 w2 = 0x00FF;

    swap(w1, w2);

    ASSERT_TRUE(w2.low == 0x00);
    ASSERT_TRUE(w2.hi  == 0xFF);
    ASSERT_TRUE(w2.value  == 0xFF00);

    ASSERT_TRUE(w1.low == 0xFF);
    ASSERT_TRUE(w1.hi  == 0x00);
    ASSERT_TRUE(w1.value  == 0x00FF);
}


TEST(word16_test, copy_check)
{
    ex::word16 w1 = 0xFF00;
    ex::word16 w2;

    w2 = w1;

    ASSERT_TRUE(w2.value  == 0xFF00);

    w2 = 0x00FF;

    ASSERT_TRUE(w2.value  == 0x00FF);
}


TEST(word16_test, cmp_operator_check)
{
    ex::word16 w1 = 0x00FF;

    ASSERT_TRUE(w1 == 0x00FF);
    ASSERT_FALSE(w1 != 0x00FF);
    ASSERT_TRUE(w1 > 0x000F);
    ASSERT_TRUE(w1 < 0xFFFF);
}


TEST(word16_test, sum_operator_check)
{
    ex::word16 w1 = 0x00FF;
    ex::word16 w2 = 0x000F;

    w1 += 0xFF00;

    ASSERT_TRUE(w1 == 0xFFFF);

    w1 -= 0x00FF;

    ASSERT_TRUE(w1 == 0xFF00);

    w1 += w2;

    ASSERT_TRUE(w1 == 0xFF0F);

    w1 -= w2;

    ASSERT_TRUE(w1 == 0xFF00);

    ASSERT_TRUE(w1 + 0x000F == 0xFF0F);
    ASSERT_TRUE(w1 + w2 == 0xFF0F);
    ASSERT_TRUE(w1 - w2 == 0xFEF1);
    ASSERT_TRUE(w1 - 0x000F == 0xFEF1);
}


TEST(word16_test, mul_operator_check)
{
    ex::word16 w1 = 0x0004;
    ex::word16 w2 = 0x0002;

    w1 *= 0x0002;

    ASSERT_TRUE(w1 == 0x0008);

    w1 /= 0x0002;

    ASSERT_TRUE(w1 == 0x0004);

    w1 *= w2;

    ASSERT_TRUE(w1 == 0x0008);

    w1 /= w2;

    ASSERT_TRUE(w1 == 0x0004);

    ASSERT_TRUE(w1 * 0x0002 == 0x0008);
    ASSERT_TRUE(w1 * w2 == 0x0008);
    ASSERT_TRUE(w1 / w2 == 0x0002);
    ASSERT_TRUE(w1 / 0x0002 == 0x0002);
}


TEST(word16_test, binary_operator_check)
{
    ex::word16 w1 = 0x00FF;
    ex::word16 w2 = 0x000F;
    ex::word16 w3 = 0x0F00;

    w1 |= 0x0F00;
    ASSERT_TRUE(w1 == 0x0FFF);
    w1 ^= 0x0F00;
    ASSERT_TRUE(w1 == 0x00FF);

    w1 |= w3;
    ASSERT_TRUE(w1 == 0x0FFF);
    w1 ^= w3;
    ASSERT_TRUE(w1 == 0x00FF);

    ASSERT_TRUE((w1 | 0x0F00) == 0x0FFF);
    ASSERT_TRUE((w1 ^ 0x000F) == 0x00F0);
    ASSERT_TRUE((w1 | w3) == 0x0FFF);
    ASSERT_TRUE((w1 ^ w2) == 0x00F0);
    
    ASSERT_TRUE((w1 << 4) == 0x0FF0);
    ASSERT_TRUE((w1 >> 4) == 0x000F);

    w1 <<= 4;
    ASSERT_TRUE(w1 == 0x0FF0);

    w1 >>= 4;
    ASSERT_TRUE(w1 == 0x00FF);

    w2 = 4;

    w1 <<= w2;
    ASSERT_TRUE(w1 == 0x0FF0);

    w1 >>= w2;
    ASSERT_TRUE(w1 == 0x00FF);
}