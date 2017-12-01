// Copyright (C) 2017 roki
#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/optional.hpp>

BOOST_AUTO_TEST_SUITE(sroptional_test)
BOOST_AUTO_TEST_CASE(optional)
{
    using namespace srook;
    SROOK_ST_ASSERT((is_same<SROOK_DECLTYPE(nullopt), const nullopt_t>{}));
    SROOK_ST_ASSERT((is_empty<nullopt_t>{}));
    SROOK_ST_ASSERT((std::is_literal_type<nullopt_t>{}));
    SROOK_ST_ASSERT((type_traits::detail::Lnot<is_default_constructible<nullopt_t>>{}));

    {
        srook::optional<int> o = srook::nullopt;
        BOOST_TEST( !o );
    }
    {
        srook::optional<int> o = { srook::nullopt };
        BOOST_TEST( !o );
    }
    {
        srook::optional<int> o { srook::nullopt };
        BOOST_TEST( !o );
    }
    {
        srook::optional<int, srook::optionally::safe_optional_payload> o = srook::nullopt;
        BOOST_TEST( !o );
    }
    {
        srook::optional<int, srook::optionally::safe_optional_payload> o = { srook::nullopt };
        BOOST_TEST( !o );
    }
    {
        srook::optional<int, srook::optionally::safe_optional_payload> o { srook::nullopt };
        BOOST_TEST( !o );
    }
}
BOOST_AUTO_TEST_SUITE_END()
