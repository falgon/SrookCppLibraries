// Copyright (C) 2011-2018 Roki. Distributed under the MIT License

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/optional.hpp>
#include <srook/type_traits/conjunction.hpp>

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
    {
        srook::optional<int> a, b, c;
        srook::optional<int, srook::optionally::safe_optional_payload> sa, sb, sc;
        std::tie(a, b, c) = srook::make_optionals(i, i, i);
        std::tie(sa, sb, sc) = srook::make_safe_optionals(i, i, i);
        BOOST_TEST((a && *a == 42 && b && *b == 42 && c && *c == 42));
        BOOST_TEST((sa && *sa == 42 && sb && *sb == 42 && sc && *sc == 42));
    }
#if SROOK_CPP_STRUCTURED_BINDINGS
    {
        auto [a, b, c] = srook::make_optionals(i, i, i);
        auto [sa, sb, sc] = srook::make_safe_optionals(i, i, i);
        SROOK_ST_ASSERT((
            srook::conjunction<
                srook::is_same<SROOK_DECLTYPE(a), srook::optional<int>>,
                srook::is_same<SROOK_DECLTYPE(b), srook::optional<int>>,
                srook::is_same<SROOK_DECLTYPE(c), srook::optional<int>>
            >::value
        ));
        SROOK_ST_ASSERT((
            srook::conjunction<
                srook::is_same<SROOK_DECLTYPE(sa), srook::optional<int, srook::optionally::safe_optional_payload>>,
                srook::is_same<SROOK_DECLTYPE(sb), srook::optional<int, srook::optionally::safe_optional_payload>>,
                srook::is_same<SROOK_DECLTYPE(sc), srook::optional<int, srook::optionally::safe_optional_payload>>
            >::value
        ));
        BOOST_TEST((a && *a == 42 && b && *b == 42 && c && *c == 42));
        BOOST_TEST((sa && *sa == 42 && sb && *sb == 42 && sc && *sc == 42));
    }
#endif
}
BOOST_AUTO_TEST_SUITE_END()
