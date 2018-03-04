#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/numeric/fixed_point.hpp>
#include <srook/limits/numeric_limits.hpp>

BOOST_AUTO_TEST_SUITE(numeric_fixed_point_test)

BOOST_AUTO_TEST_CASE(fixed_point_operator_test1)
{
    typedef srook::numeric::fixed_point<4, 4> fixed_point_type;
    fixed_point_type fp {};

    ~fp;
    +fp;
    -fp;
    !fp;
    ++fp;
    --fp;
    fp++;
    fp--;
}

BOOST_AUTO_TEST_CASE(fixed_point_operator_test2)
{
    typedef srook::numeric::fixed_point<4, 4> fixed_point_type;
    auto fp = srook::numeric_limits<fixed_point_type>::max();
    try {
        fp.increment();
    } catch (std::overflow_error) {}
    try {
        fp.post_increment();
    } catch (std::overflow_error) {}
    fp = srook::numeric_limits<fixed_point_type>::min();
    try {
        fp.decrement();
    } catch (std::underflow_error) {}
    try {
        fp.post_decrement();
    } catch (std::underflow_error) {}
}

BOOST_AUTO_TEST_CASE(fixed_point_operator_test3)
{
    typedef srook::numeric::fixed_point<4, 4> fixed_point_type;
    fixed_point_type fp1 = 2;
    auto fp2 = srook::numeric_limits<fixed_point_type>::max();
    auto fp3 = srook::numeric_limits<fixed_point_type>::min();
    
    fp1 /= fp1;
    fp1 += fp1;
    fp1 *= fp1;
    fp1 |= fp1;
    fp1 ^= fp1;
    fp1 &= fp1;
    fp1 >>= fp1;
    fp1 <<= fp1;
    fp1 -= fp1;

    try {
        fp2.iadd(fp2);
    } catch (std::overflow_error) {}
    try {
        fp3.isub(fp2);
    } catch (std::underflow_error) {}
    try {
        fp2.imul(fp2);
    } catch (std::overflow_error) {}
    fp3.idiv(fp2);
}

BOOST_AUTO_TEST_CASE(fixed_point_operator_test4)
{
    typedef srook::numeric::fixed_point<4, 4> fixed_point_type;
    fixed_point_type fp1 = 2;
    fp1 + 1;
    fp1 - 1;
    fp1 * 1;
    fp1 / 1;
}

BOOST_AUTO_TEST_SUITE_END()
