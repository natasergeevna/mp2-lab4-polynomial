#include "polynomial.h"

#include <gtest.h>

TEST(polynom_string, can_create_polynom_string)
{
    ASSERT_NO_THROW(polynom_string p("x1y2z3+4.5-x2y4z4"));
}

TEST(polynom_string, cant_create_polynom_string_with_more_variables)
{
    ASSERT_ANY_THROW(polynom_string p("x1y2z3x4+x2"));
}

TEST(polynom_string, cant_create_polynom_string_with_negative_degree)
{
    ASSERT_ANY_THROW(polynom_string p("x1y2z3+x-2"));
}

TEST(polynom_string, cant_create_polynom_string_with_big_degree)
{
    ASSERT_ANY_THROW(polynom_string p("x20y3z5"));
}

TEST(polynom_string, cant_create_polynom_string_with_double_degree)
{
    ASSERT_ANY_THROW(polynom_string p("-5x7.6y5z4"));
}

TEST(polynom_string, cant_create_polynom_string_with_unacceptable_symbols)
{
    ASSERT_ANY_THROW(polynom_string p("!19x^6y8*_"));
}

TEST(polynom_string, cant_create_polynom_string_with_many_pluses_or_minuses)
{
    ASSERT_ANY_THROW(polynom_string p("5+++67x1"));
    ASSERT_ANY_THROW(polynom_string p1("5---67x1"));
}

TEST(polynom_string, cant_create_polynom_string_without_degree)
{
    ASSERT_ANY_THROW(polynom_string p("5.5xy2z2"));
}

TEST(polynom_string, cant_create_polynom_with_wrong_coefficient)
{
    ASSERT_ANY_THROW(polynom_string p("-5.5x4+.2x7"));
}

TEST(polynom_string, cant_create_empty_polynom_string)
{
    ASSERT_ANY_THROW(polynom_string p("     "));
}

TEST(polynom_string, getstr_is_correct)
{
    polynom_string p("x4y6z7-5.6x8y5 +  5");
    EXPECT_EQ(p.getstr(), "x4y6z7-5.6x8y5+5");
}

TEST(Polynom, can_create_polynom)
{
    polynom_string temp("x1y2z3 + 4.5z3");
    ASSERT_NO_THROW(Polynom p(temp));
}

TEST(Polynom, can_create_empty_polinom)
{
    ASSERT_NO_THROW(Polynom p);
}

TEST(Polynom, add_is_correct)
{
    polynom_string str1("x1y2z3+4.5z3");
    polynom_string str2("x1y2z3+4.5z3");
    polynom_string str3("2x1y2z3+9z3");
    Polynom p1(str1), p2(str2), p3(str3);
    bool flag = ((p1+p2) == p3);
    EXPECT_EQ(flag, true);
}

TEST(Polynom, can_multiply)
{
    polynom_string str1("2x1+y2");
    polynom_string str2("z2+3x1");
    polynom_string str3("6x2+3x1y2+y2z2+2x1z2");
    Polynom p1(str1), p2(str2), p3(str3);
    bool flag = ((p1 * p2) == p3);
    EXPECT_EQ(flag, true);
}

TEST(Polynom, can_multiply_on_const)
{
    polynom_string str1("2x1+y2");
    polynom_string str2("10x1+5y2");
    Polynom p1(str1), p2(str2);
    bool flag = (p1.MultConst(5) == p2);
    EXPECT_EQ(flag, true);
}

TEST(Polynom, count_at_the_point)
{
    polynom_string str1("2x1y1z2+y2-5z3");
    Polynom p1(str1);
    EXPECT_EQ(p1.ValuePoint(2, -3, -1), 2);
}

TEST(Polynom, different_polynoms_not_equal)
{
    polynom_string str1("2x1y1z2+y2-5z3");
    polynom_string str2("10x1+5y2");
    Polynom p1(str1);
    Polynom p2(str2);
    bool flag = p1 == p2;
    EXPECT_EQ(flag, false);
}

TEST(Polynom, create_polynom_with_exist_polynom)
{
    polynom_string str1("5x7y4+8y6");
    Polynom p1(str1);
    Polynom p2(p1);
    bool flag = (p1 == p2);
    EXPECT_EQ(flag, true);
    p2 = p2 + p1;
    flag = p1 != p2;
    EXPECT_EQ(flag, true);
}

TEST(Polynom, can_mult_polynom_on_zero)
{
    polynom_string str1("5x7y4+8y6");
    Polynom p1(str1);
    polynom_string str2("0");
    Polynom p2(str2);
    bool flag = p1.MultConst(0) == p2;
    EXPECT_EQ(flag, true);
}

TEST(Polynom, plus_equal_is_correct)
{
    polynom_string str1("4x2+y6-z3");
    polynom_string str2("2x2+y8-y6");
    polynom_string str3("6x2+y8-z3");
    Polynom p1(str1), p2(str2), p3(str3);
    p1 += p2;
    bool flag = p1 == p3;
    EXPECT_EQ(flag, true);
}
