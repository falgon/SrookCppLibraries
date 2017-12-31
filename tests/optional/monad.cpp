// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#define  BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/optional.hpp>

BOOST_AUTO_TEST_SUITE(sroptional_test)

srook::optional<int> f(int x) { return { x }; }
srook::optional<int> g(int) { return srook::nullopt; }

BOOST_AUTO_TEST_CASE(optional_monad1)
{
    srook::optional<int> result = 
        f(42) >>= [](int x) {
            return f(x) >>= [](int y) {
                return f(y) >>= [](int z) {
                    return f(z);
                };
            };
        };

    BOOST_CHECK_EQUAL(result.value(), 42);
}

BOOST_AUTO_TEST_CASE(optional_monad2)
{
    srook::optional<int> result = 
        f(42) | 0 >>= [](int x) { // The function f is always success
            BOOST_CHECK_EQUAL(x, 42);
            return f(x) | 1 >>= [](int y) { // The function f is always success
                BOOST_CHECK_EQUAL(y, 42);
                return g(y) | 2 >>= [](int z) { // call value_or
                    BOOST_CHECK_EQUAL(z, 2);
                    return f(z);
                };
            };
        };
    BOOST_CHECK_EQUAL(result.value(), 2);
}

BOOST_AUTO_TEST_CASE(optional_monad3)
{
    srook::optional<int> result =
        f(42) >>= [](int x) {
            return g(x);
        };
    BOOST_TEST(!bool(result));
}


BOOST_AUTO_TEST_SUITE_END()
