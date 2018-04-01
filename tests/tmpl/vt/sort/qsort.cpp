#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/tmpl/vt/sort/qsort.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/cstdint.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE(srook_cfenv_round_switch_test)

BOOST_AUTO_TEST_CASE(round_switch1)
{
    typedef srook::tmpl::vt::packer<srook::uint16_t, srook::uint32_t, char, srook::uint64_t> type;
    typedef SROOK_DEDUCED_TYPENAME srook::tmpl::vt::qsort<type>::type lt_sorted;
    SROOK_ST_ASSERT(srook::is_same<lt_sorted, srook::tmpl::vt::packer<char, srook::uint16_t, srook::uint32_t, srook::uint64_t>>::value);

    typedef SROOK_DEDUCED_TYPENAME srook::tmpl::vt::qsort<type, srook::tmpl::vt::gt>::type gt_sorted;
    SROOK_ST_ASSERT(srook::is_same<gt_sorted, srook::tmpl::vt::packer<srook::uint64_t, srook::uint32_t, srook::uint16_t, char>>::value);
}

BOOST_AUTO_TEST_SUITE_END()
