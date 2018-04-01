#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/foldl.hpp>
#include <srook/tmpl/vt/foldr.hpp>
#include <srook/tmpl/vt/reverse.hpp>
#include <srook/tmpl/vt/max.hpp>
#include <srook/tmpl/vt/filterD.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <srook/tmpl/vt/tt_proxy.hpp>
#include <srook/tmpl/vt/sort/qsort.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/cstdint.hpp>

BOOST_AUTO_TEST_SUITE(srook_tmpl_vt_fold_test)

template <class L, class... R>
struct snoc : srook::tmpl::vt::concat<R..., L> {};

template <class Li, class X>
struct f
    : srook::tmpl::vt::concat<
        SROOK_DEDUCED_TYPENAME srook::tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME srook::tmpl::vt::filterD<srook::tmpl::vt::bind<srook::tmpl::vt::tt_proxy<srook::tmpl::vt::lt>::template type, srook::tmpl::vt::placeholders::_1, X>, Li>::type, X
        >::type,
        SROOK_DEDUCED_TYPENAME srook::tmpl::vt::filterD<srook::tmpl::vt::bind<srook::tmpl::vt::geq, srook::tmpl::vt::placeholders::_1, X>, Li>::type
    > {};
      
BOOST_AUTO_TEST_CASE(fold_test1)
{
    typedef srook::tmpl::vt::packer<srook::uint32_t, srook::uint8_t, srook::uint64_t, srook::uint16_t> type;

    // reverse
    typedef SROOK_DEDUCED_TYPENAME srook::tmpl::vt::foldr<snoc, srook::tmpl::vt::packer<>, type>::type rev;
    SROOK_ST_ASSERT(srook::is_same<SROOK_DEDUCED_TYPENAME srook::tmpl::vt::reverse<type>::type, rev>::value);

    // deriving the maximum type where `maximum` is defined by <srook/tmpl/vt/compare.hpp>
    typedef SROOK_DEDUCED_TYPENAME srook::tmpl::vt::foldr<srook::tmpl::vt::max, srook::tmpl::vt::packer<>, type>::type maxi; 
    SROOK_ST_ASSERT(srook::is_same<srook::uint64_t, maxi>::value);

    // insertion sort with foldl
    typedef SROOK_DEDUCED_TYPENAME srook::tmpl::vt::foldl<f, srook::tmpl::vt::packer<>, type>::type isorted;
    SROOK_ST_ASSERT(srook::is_same<SROOK_DEDUCED_TYPENAME srook::tmpl::vt::qsort<type>::type, isorted>::value);
}

BOOST_AUTO_TEST_SUITE_END()
