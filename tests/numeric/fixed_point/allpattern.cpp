#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/numeric/fixed_point.hpp>
#include <srook/utility/index_sequence.hpp>
#include <srook/limits/numeric_limits.hpp>

namespace detail {

template <
    std::size_t begin_integer_bits, std::size_t end_integer_bits, 
    std::size_t begin_fractional_bits, std::size_t end_fractional_bits
>
struct all_pattern {
    static SROOK_CXX14_CONSTEXPR void do_pattern()
    {
        typedef srook::numeric::fixed_point<begin_integer_bits, begin_fractional_bits> fixed_point_type;
        SROOK_ATTRIBUTE_UNUSED fixed_point_type fp = srook::numeric_limits<fixed_point_type>::max();
        all_pattern<begin_integer_bits + 1, end_integer_bits, begin_fractional_bits - 1, end_fractional_bits>::do_pattern();
    }
};

template <std::size_t integer_bits, std::size_t fractional_bits>
struct all_pattern<integer_bits, integer_bits, fractional_bits, fractional_bits> {
    static SROOK_CXX14_CONSTEXPR void do_pattern()
    {
        typedef srook::numeric::fixed_point<integer_bits, fractional_bits> fixed_point_type;
        SROOK_ATTRIBUTE_UNUSED fixed_point_type fp = srook::numeric_limits<fixed_point_type>::max();
    }
};

} // namespace detail

BOOST_AUTO_TEST_SUITE(numeric_fixed_point_test)

BOOST_AUTO_TEST_CASE(fixed_point_all_pattern_test)
{
    detail::all_pattern<1, 8, 7, 0>::do_pattern(); // 8 bits pattern
    detail::all_pattern<1, 16, 15, 0>::do_pattern(); // 16 bits pattern
    detail::all_pattern<1, 32, 31, 0>::do_pattern(); // 32 bits pattern
    detail::all_pattern<1, 64, 63, 0>::do_pattern(); // 64 bits pattern
#if defined(SROOK_HAS_INT128) && !defined(__STRICT_ANSI__)
    detail::all_pattern<1, 128, 127, 0>::do_pattern(); // 128 bits pattern
#endif
}

BOOST_AUTO_TEST_SUITE_END()
