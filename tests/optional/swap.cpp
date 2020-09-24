// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/optional.hpp>

BOOST_AUTO_TEST_SUITE(sroptional_test)

BOOST_AUTO_TEST_CASE(optional_swap)
{
    srook::optional<int> sro1 = 42, sro2 = 43;
    std::optional<int> stdo = 44;
    boost::optional<int> boo = 45;

    std::swap(sro1, sro2);
    sro1.swap(sro2);
    sro1.swap(stdo);
    sro1.swap(boo);

    BOOST_TEST((sro1 && *sro1 == 45));
}

BOOST_AUTO_TEST_SUITE_END()
