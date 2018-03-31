#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/range/adaptor/take.hpp>
#include <srook/range/adaptor/moved.hpp>
#include <srook/execution.hpp>
#include <vector>

BOOST_AUTO_TEST_SUITE(srook_range_adaptor_take_test)

BOOST_AUTO_TEST_CASE(intro_sort1)
{
    std::vector<int> v(1 << 10, 0);
    std::vector<int> r = v | srook::range::adaptors::take(v.size() >> 1) | srook::range::adaptors::moved;
    BOOST_CHECK_EQUAL(v.size() >> 1, r.size());
}

BOOST_AUTO_TEST_SUITE_END()
