#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/algorithm/sorting/intro_sort.hpp>
#include <srook/numeric/algorithm/iota.hpp>
#include <srook/random/algorithm/shuffle.hpp>
#include <srook/execution.hpp>
#include <srook/array.hpp>
#include <algorithm>
#include <random>
#include <chrono>

BOOST_AUTO_TEST_SUITE(srook_algorithm_sorting_intro_sort_test)

template <class SinglePassRange>
inline void do_shuffle(SinglePassRange&& range)
{
    srook::random::algorithm::fisher_yates(srook::forward<SinglePassRange>(range), std::mt19937(std::random_device{}()));
}

template <class SinglePassRange, class... P>
inline void do_sort(SinglePassRange&& range, P... p)
{
    static_assert(sizeof...(p) == 1 || sizeof...(p) == 0);

    const auto start = std::chrono::system_clock::now();
    srook::algorithm::intro_sort(p..., srook::begin(range), srook::end(range));
    const auto end = std::chrono::system_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << '\n';
}

BOOST_AUTO_TEST_CASE(intro_sort1)
{
    srook::array<int, 1000000> ar;

    srook::numeric::algorithm::iota(srook::execution::par, ar, 0);
    do_shuffle(ar);
    do_sort(ar);
    BOOST_TEST(std::is_sorted(srook::begin(ar), srook::end(ar)));
    
    do_shuffle(ar);
    do_sort(ar, srook::execution::par);
    BOOST_TEST(std::is_sorted(srook::begin(ar), srook::end(ar)));
}

BOOST_AUTO_TEST_SUITE_END()
