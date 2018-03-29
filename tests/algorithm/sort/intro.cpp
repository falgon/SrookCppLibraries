/*#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/cfenv/round_switch.hpp>*/

/*BOOST_AUTO_TEST_SUITE(srook_cfenv_round_switch_test)

BOOST_AUTO_TEST_CASE(round_switch1)
{
    namespace sc = srook::cfenv;*/

#include <srook/algorithm/sorting/intro_sort.hpp>
#include <srook/numeric/algorithm/iota.hpp>
#include <srook/random/algorithm/shuffle.hpp>
#include <srook/execution.hpp>
#include <srook/array.hpp>
#include <algorithm>
#include <random>

template <class SinglePassRange>
inline void do_shuffle(SinglePassRange&& range)
{
    srook::random::algorithm::fisher_yates(srook::forward<SinglePassRange>(range), std::mt19937(std::random_device{}()));
}

int main()
{
    srook::array<int, 1024> ar;
    srook::numeric::algorithm::iota(srook::execution::par, ar, 0);
    do_shuffle(ar);
    srook::algorithm::intro_sort(srook::begin(ar), srook::end(ar));
    assert(std::is_sorted(srook::begin(ar), srook::end(ar)));
}
