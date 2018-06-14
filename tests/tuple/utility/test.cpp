#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/tuple/utility.hpp>

BOOST_AUTO_TEST_SUITE(srtuple_utilities_test)

BOOST_AUTO_TEST_CASE(srtuple_test1)
{
    auto a = srook::tuple::utility::dupe(42);
    BOOST_CHECK_EQUAL(a.first, 42);
    BOOST_CHECK_EQUAL(a.first, a.second);
}

BOOST_AUTO_TEST_CASE(srtuple_test2)
{
    auto a = srook::tuple::utility::nth<0>([](int x) SROOK_CXX17_CONSTEXPR noexcept { return x * 2; });
    auto b = a(std::make_pair(42, 42));
    BOOST_CHECK_EQUAL(std::get<0>(b), 84);
    BOOST_CHECK_EQUAL(std::get<1>(b), 42);

    auto d = srook::tuple::utility::nth<0>([](int x) SROOK_CXX17_CONSTEXPR noexcept { return x * 2; });
    auto c = d(std::make_tuple(42, 84, 168));
    BOOST_CHECK_EQUAL(std::get<0>(c), 84);
    BOOST_CHECK_EQUAL(std::get<1>(c), 84);
    BOOST_CHECK_EQUAL(std::get<2>(c), 168);
}

BOOST_AUTO_TEST_CASE(srtuple_test3)
{
    auto a = srook::tuple::utility::uncurry([](int x, int) SROOK_CXX17_CONSTEXPR noexcept { return x; });
    a(std::make_pair(42, 42));
}

BOOST_AUTO_TEST_CASE(srtuple_test4)
{
    auto a = srook::tuple::utility::curry([](std::pair<int, int> x) SROOK_CXX17_CONSTEXPR noexcept { return x; });
    a(42, 42);
}

BOOST_AUTO_TEST_CASE(srtuple_test5)
{
    using namespace srook::tuple::utility::pipeop;

    auto a =
        srook::tuple::utility::dupe(42) |
        srook::tuple::utility::nth<0>([](int x) SROOK_CXX17_CONSTEXPR noexcept { return x * 2; }) |
        srook::tuple::utility::uncurry([](int x, int y) SROOK_CXX17_CONSTEXPR noexcept { return x + y; });
    BOOST_CHECK_EQUAL(a, 126);
}

BOOST_AUTO_TEST_CASE(srtuple_test6)
{
    using namespace srook::tuple::utility::pipeop;

    auto a =
        srook::tuple::utility::ampersand([](int x) SROOK_CXX17_CONSTEXPR noexcept { return x + 42; }, [](int x) SROOK_CXX17_CONSTEXPR noexcept { return x * 2; })(42) |
        srook::tuple::utility::uncurry([](int x, int y) SROOK_CXX17_CONSTEXPR noexcept { return x + y; });
    BOOST_CHECK_EQUAL(a, 168);
}

BOOST_AUTO_TEST_SUITE_END()
