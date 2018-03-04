#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/numeric/fixed_point.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/type_traits/is_static_castable.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/tmpl/vt.hpp>

BOOST_AUTO_TEST_SUITE(numeric_fixed_point_test)

namespace detail {
    typedef srook::tmpl::vt::packer<
        bool, 
        char, 
        char16_t, 
        char32_t, 
        wchar_t, 
        signed char, 
        short int, 
        int, 
        long int, 
        unsigned char, 
        unsigned short int, 
        unsigned int, 
        unsigned long int,
        float,
        double
#ifdef SROOK_HAS_LONG_LONG
        , long long int 
        , unsigned long long int
#endif
#ifdef SROOK_HAS_LONG_DOUBLE
        , long double
#endif
#if defined(SROOK_HAS_INT128) && !defined(__STRICT_ANSI__)
        , srook::int128_t
        , srook::uint128_t
#endif
#if defined(SROOK_HAS_FLOAT128) && !defined(__STRICT_ANSI__)
        , srook::float128_t
#endif
    > arithmetic_list;

typedef srook::numeric::fixed_point<4, 4> fixed_point_type;

template <std::size_t b, std::size_t e>
struct casting {
    static SROOK_CXX14_CONSTEXPR void do_casting()
    {
        fixed_point_type fp {};
        SROOK_ATTRIBUTE_UNUSED auto a = static_cast<SROOK_DEDUCED_TYPENAME srook::tmpl::vt::at<b, arithmetic_list>::type>(fp);
        casting<b + 1, e>::do_casting();
    }
};

template <std::size_t b>
struct casting<b, b> {
    static SROOK_CXX14_CONSTEXPR void do_casting()
    {
        fixed_point_type fp {};
        SROOK_ATTRIBUTE_UNUSED auto a = static_cast<SROOK_DEDUCED_TYPENAME srook::tmpl::vt::at<b, arithmetic_list>::type>(fp);
    }
};

} // namespace detail

BOOST_AUTO_TEST_CASE(fixed_point_cast_test1)
{
    typedef srook::tmpl::vt::bind<srook::is_static_castable, detail::fixed_point_type, srook::tmpl::vt::placeholders::_1> bind_type;
    SROOK_ST_ASSERT(
        srook::tmpl::vt::size<SROOK_DEDUCED_TYPENAME srook::tmpl::vt::take_whileD<bind_type, detail::arithmetic_list>::type>::value == srook::tmpl::vt::size<detail::arithmetic_list>::value
    );
}

BOOST_AUTO_TEST_CASE(fixed_point_cast_test2)
{
    detail::casting<0, srook::tmpl::vt::size<detail::arithmetic_list>::value - 1>::do_casting();
}

BOOST_AUTO_TEST_SUITE_END()
