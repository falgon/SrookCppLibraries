// Copyright (C) 2017 roki

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/optional.hpp>

BOOST_AUTO_TEST_SUITE(sroptional_test)
BOOST_AUTO_TEST_CASE(optional)
{
    const int i = 42;
    {
        auto o = srook::make_optional(i);
        SROOK_ST_ASSERT((srook::is_same<SROOK_DECLTYPE(o), srook::optional<int>>{}));
        BOOST_TEST(( o && *o == 42 ));
        BOOST_TEST(( &*o != &i ));
    }
    {
        auto o = srook::make_safe_optional(i);
        SROOK_ST_ASSERT((srook::is_same<SROOK_DECLTYPE(o), srook::optional<int, srook::optionally::safe_optional_payload>>{}));
    }
}
BOOST_AUTO_TEST_SUITE_END()
