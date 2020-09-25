// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#define  BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/optional.hpp>
#include <srook/type_traits/is_same.hpp>

BOOST_AUTO_TEST_SUITE(sroptional_test)

using srook::is_same;

BOOST_AUTO_TEST_CASE(optional_applicative1)
{
    auto result = 
        srook::applicative(
            [](int x, int y, int z) SROOK_CXX17_CONSTEXPR noexcept -> int { return x + y + z; }, 
            srook::make_optionals(1, 2, 3)
        );
    SROOK_ST_ASSERT((is_same<SROOK_DECLTYPE(result), srook::optional<int>>::value));
    BOOST_TEST(*(result >>= [](int x) noexcept -> srook::optional<bool> { return x == 6; }));
}

BOOST_AUTO_TEST_CASE(optional_applicative2)
{
    auto result =
        srook::applicative(
            [](int x, int y, int z) SROOK_CXX17_CONSTEXPR noexcept -> int { return x * y * z; }, 
            srook::make_optionals(1, 2, 3)
        ) >>= [](int x) noexcept -> srook::optional<int> { return { x / 2 }; };
    SROOK_ST_ASSERT((is_same<SROOK_DECLTYPE(result), srook::optional<int>>::value));
    BOOST_TEST(*(result >>= [](int x) noexcept -> srook::optional<bool> { return x == 3; }));
}

BOOST_AUTO_TEST_CASE(optional_applicative3)
{
    auto result =
        srook::applicative(
            [](int x) SROOK_CXX17_CONSTEXPR noexcept -> int { return x * 2; },
            srook::applicative(
                [](int x, int y) SROOK_CXX17_CONSTEXPR noexcept -> int { return x * y; },
                srook::make_optional(2), srook::make_optional(3)
            )
        );
    SROOK_ST_ASSERT((is_same<SROOK_DECLTYPE(result), srook::optional<int>>::value));
    BOOST_TEST(*(result >>= [](int x) noexcept -> srook::optional<bool> { return x == 12; }));
}

BOOST_AUTO_TEST_CASE(optional_applicative4)
{
    using namespace srook::optionally::applicative_operators;

    {
        auto result = [](int x) SROOK_CXX17_CONSTEXPR noexcept -> int { return x * 2; } & srook::make_optional(2);
        SROOK_ST_ASSERT((is_same<SROOK_DECLTYPE(result), srook::optional<int>>::value));
        BOOST_TEST(*(result >>= [](int x) noexcept -> srook::optional<bool> { return x == 4; }));
    }

    const auto l = [](int x, int y, int z) SROOK_CXX17_CONSTEXPR noexcept -> int { return x * y * z; };
    {
        auto result = l & srook::make_optional(2) * srook::make_optional(3) * srook::make_optional(4);
        SROOK_ST_ASSERT((is_same<SROOK_DECLTYPE(result), srook::optional<int>>::value));
        BOOST_TEST(*(result >>= [](int x) noexcept -> srook::optional<bool> { return x == 24; }));
    }
    {
        auto result = l & srook::make_optionals(2, 3, 4);
        SROOK_ST_ASSERT((is_same<SROOK_DECLTYPE(result), srook::optional<int>>::value));
        BOOST_TEST(*(result >>= [](int x) noexcept -> srook::optional<bool> { return x == 24; }));

        result = l & srook::make_optionals(2, 3) * srook::make_optional(4);
        BOOST_TEST(*(result >>= [](int x) noexcept -> srook::optional<bool> { return x == 24; }));
    }
}

BOOST_AUTO_TEST_SUITE_END()
