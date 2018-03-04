#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/numeric/fixed_point.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <type_traits>

BOOST_AUTO_TEST_SUITE(numeric_fixed_point_test)

BOOST_AUTO_TEST_CASE(fixed_point_construct_test1)
{
    typedef srook::numeric::fixed_point<4, 4> fixed_point_type;
    SROOK_ATTRIBUTE_UNUSED fixed_point_type fp1 = srook::uint16_t(0xf);
    try {
        SROOK_ATTRIBUTE_UNUSED fixed_point_type fp2 = srook::uint16_t(0x1f);
    } catch (std::overflow_error) {}
}

BOOST_AUTO_TEST_CASE(fixed_point_construct_test2)
{
    typedef srook::numeric::fixed_point<4, 4> fixed_point_type;
    typedef srook::numeric_limits<float> float_limits;
    try {
        SROOK_ATTRIBUTE_UNUSED fixed_point_type fp = float_limits::quiet_NaN();
    } catch (std::overflow_error) {}
    try {
        SROOK_ATTRIBUTE_UNUSED fixed_point_type fp = float_limits::infinity();
    } catch (std::overflow_error) {}
    try {
        SROOK_ATTRIBUTE_UNUSED fixed_point_type fp = float_limits::max();
    } catch (std::overflow_error) {}
}

BOOST_AUTO_TEST_CASE(fixed_point_construct_test3)
{
    typedef srook::numeric::fixed_point<4, 4> fixed_point_type;
    SROOK_ST_ASSERT(std::is_nothrow_default_constructible<fixed_point_type>::value);
    SROOK_ST_ASSERT(std::is_nothrow_copy_constructible<fixed_point_type>::value);
    SROOK_ST_ASSERT(std::is_nothrow_move_constructible<fixed_point_type>::value);
    SROOK_ST_ASSERT(std::is_nothrow_copy_assignable<fixed_point_type>::value);
    SROOK_ST_ASSERT(std::is_nothrow_move_assignable<fixed_point_type>::value);

    SROOK_ATTRIBUTE_UNUSED fixed_point_type fp1{}, fp2 = fp1, fp3 = srook::move(fp2);
    fp1 = fp3;
    fp1 = srook::move(fp3);
}

BOOST_AUTO_TEST_CASE(fixed_point_construct_test4)
{
    typedef srook::numeric::fixed_point<4, 4> fixed_point_type;
    typedef srook::numeric_limits<SROOK_DEDUCED_TYPENAME fixed_point_type::value_type> value_limits;
    auto fp = fixed_point_type::from_value(value_limits::max());
    BOOST_TEST((fp == srook::numeric_limits<fixed_point_type>::max()));
    fp = fixed_point_type::from_value(value_limits::min());
    BOOST_TEST((fp == srook::numeric_limits<fixed_point_type>::min()));
}

BOOST_AUTO_TEST_SUITE_END()
