#define BOOST_TEST_MAIN
#include <array>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/algorithm/generate.hpp>
#include <boost/test/included/unit_test.hpp>
#include <cstdint>
#include <random>
#include <srook/cxx17/mpl/any_pack/any_pack.hpp>
#include <vector>

BOOST_AUTO_TEST_SUITE(random_test)

BOOST_AUTO_TEST_CASE(mersenne_twister_test)
{
    std::mt19937 mt_engine;
    std::mt19937_64 mt64_engine;

    std::array<std::uint_fast32_t, 10> mt19937;     boost::generate(mt19937, std::ref(mt_engine));
    std::array<std::uint_fast64_t, 10> mt19937_64;  boost::generate(mt19937_64, std::ref(mt64_engine));

    const auto anypack_mt19937 = srook::any_pack<>::make_random_sequence<10, srook::random::mt19937<>>::range<std::vector>;
    const auto anypack_mt19937_64 = srook::any_pack<>::make_random_sequence<10, srook::random::mt19937_64<>>::range<std::vector>;

    BOOST_CHECK(boost::equal(mt19937, anypack_mt19937));
    BOOST_CHECK(boost::equal(mt19937_64, anypack_mt19937_64));
}

BOOST_AUTO_TEST_SUITE_END()
