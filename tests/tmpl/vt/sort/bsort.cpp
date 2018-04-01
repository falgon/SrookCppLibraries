#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/tmpl/vt/sort/bsort.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/cstdint.hpp>

BOOST_AUTO_TEST_SUITE(srook_cfenv_round_switch_test)

BOOST_AUTO_TEST_CASE(round_switch1)
{
    typedef srook::tmpl::vt::packer<srook::uint16_t, srook::uint32_t, char, srook::uint64_t> type;
    typedef SROOK_DEDUCED_TYPENAME srook::tmpl::vt::bsort<type>::type lt_sorted;
    SROOK_ST_ASSERT(srook::is_same<lt_sorted, srook::tmpl::vt::packer<char, srook::uint16_t, srook::uint32_t, srook::uint64_t>>::value);
}

BOOST_AUTO_TEST_SUITE_END()
