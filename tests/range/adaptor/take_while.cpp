#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/range/adaptor/take_while.hpp>
#include <srook/range/adaptor/moved.hpp>
#include <srook/execution.hpp>
#include <algorithm>
#include <vector>

BOOST_AUTO_TEST_SUITE(srook_range_adaptor_take_test)

BOOST_AUTO_TEST_CASE(intro_sort1)
{
    std::vector<int> v(1 << 10, 0);
    std::fill(srook::begin(v), srook::begin(v) + (v.size() >> 1), 1);
    std::vector<int> r = v 
        | srook::range::adaptors::take_while([](SROOK_DEDUCED_TYPENAME SROOK_DECLTYPE(v)::value_type x) { return x > 0; })
        | srook::range::adaptors::moved;
    BOOST_CHECK_EQUAL(v.size() >> 1, r.size());
}

BOOST_AUTO_TEST_SUITE_END()
