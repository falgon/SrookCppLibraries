#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/numeric/fixed_point.hpp>
#include <srook/limits/numeric_limits.hpp>

BOOST_AUTO_TEST_SUITE(numeric_fixed_point_test)

BOOST_AUTO_TEST_CASE(fixed_point_compare_test1)
{
    typedef srook::numeric::fixed_point<4, 4> fixed_point_type;
    const fixed_point_type fp1 = srook::uint8_t(0xf), fp2 = srook::uint8_t(0xe);
    BOOST_TEST((fp2 < fp1));
    BOOST_TEST((fp1 > fp2));
    BOOST_TEST((fp2 <= fp1));
    BOOST_TEST((fp1 >= fp2));
    BOOST_TEST(!(fp1 == fp2));
    BOOST_TEST((fp1 != fp2));
}

BOOST_AUTO_TEST_CASE(fixed_point_compare_test2)
{
    typedef srook::numeric::fixed_point<4, 4> fixed_point_type;
    const fixed_point_type fp = 2;
    const int i = 3;
    BOOST_TEST((fp < i));
    BOOST_TEST((i > fp));
    BOOST_TEST((fp <= i));
    BOOST_TEST((i >= fp));
    BOOST_TEST(!(fp == i));
    BOOST_TEST((fp != i));
}

BOOST_AUTO_TEST_CASE(fixed_point_compare_test3)
{
    typedef srook::numeric::fixed_point<4, 4> fixed_point_type;
    const float f = 2.5f;
    const fixed_point_type fp = f;
    BOOST_TEST(!(f < fp));
    BOOST_TEST(!(f > fp));
    BOOST_TEST((f <= fp));
    BOOST_TEST((f >= fp));
    BOOST_TEST((f == fp));
    BOOST_TEST(!(f != fp));
}

BOOST_AUTO_TEST_SUITE_END()
