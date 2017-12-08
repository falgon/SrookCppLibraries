// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_STRING_STOI_HPP
#define INCLUDED_SROOK_MPL_STRING_STOI_HPP
#include <srook/config.hpp>
#include <srook/type_traits.hpp>
#include <srook/mpl/utility/ctoi.hpp>
#include <srook/utility/integer_sequence.hpp>
#include <srook/math/constants/algorithm/pow.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#include <srook/mpl/variadic_types.hpp>
#endif

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace string {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class IntegerSeq> 
struct remove_space
    : type_constant<IntegerSeq> {};
template <class charT, charT... s>
struct remove_space<integer_sequence<charT, ' ', s...>>
    : remove_space<integer_sequence<charT, s...>> {};

template <typename IntegralType, IntegralType x, std::size_t digit>
struct adjust_digit 
    : integral_constant<IntegralType, adjust_digit<IntegralType, x * 10, digit - 1>::value> {};
template <typename IntegralType, IntegralType x>
struct adjust_digit<IntegralType, x, 1> 
    : integral_constant<IntegralType, x> {};
template <typename IntegralType, IntegralType x>
struct adjust_digit<IntegralType, x, 0> {
    template <IntegralType> struct delayer : SROOK_FALSE_TYPE {};
    SROOK_STATIC_ASSERT((delayer<IntegralType(0)>::value), "invalid argument");
};

template <typename IntegralType, IntegralType, IntegralType, std::size_t, class = void> struct fx;
template <typename IntegralType, IntegralType decimal, IntegralType octal, std::size_t i>
struct fx<IntegralType, decimal, octal, i, SROOK_DEDUCED_TYPENAME enable_if<bool(octal)>::type> 
    : fx<IntegralType, IntegralType(decimal + (octal % 10) * pow(8, i)), octal / 10, i + 1> {};
template <typename IntegralType, IntegralType decimal, IntegralType octal, std::size_t i>
struct fx<IntegralType, decimal, octal, i, SROOK_DEDUCED_TYPENAME enable_if<!octal>::type>
    : integral_constant<IntegralType, decimal> {};

template <std::size_t, class, typename IntegralType, IntegralType = IntegralType(0)> struct computing_value;

template <char di, typename IntegralType, typename charT, charT... git, IntegralType r>
struct computing_value<10, integer_sequence<charT, di, git...>, IntegralType, r> {
private:
    static SROOK_CONSTEXPR_OR_CONST SROOK_OPTIONAL<unsigned short int> t = ctoi<di>::value;
    SROOK_STATIC_ASSERT((t.value_or(42) != 42), "invalid characters code");
    SROOK_STATIC_ASSERT((is_integral<IntegralType>::value), "type must be integral");
public:
    static SROOK_CONSTEXPR_OR_CONST IntegralType value = 
        r + computing_value<10, integer_sequence<charT, git...>,  IntegralType, adjust_digit<IntegralType, IntegralType(t.value()), sizeof...(git) + 1>::value>::value;
};

template <char di, typename IntegralType, typename charT, charT... git, IntegralType r>
struct computing_value<8, integer_sequence<charT, di, git...>, IntegralType, r> {
private:
    static SROOK_CONSTEXPR_OR_CONST IntegralType t = computing_value<10, integer_sequence<charT, di, git...>, IntegralType, r>::value;
public:
    static SROOK_CONSTEXPR_OR_CONST IntegralType value = fx<IntegralType, IntegralType((t % 10) * pow(8, 0)), t / 10, 1>::value;
};

template <typename IntegralType, IntegralType r, typename charT>
struct computing_value<8, integer_sequence<charT>, IntegralType, r> 
    : integral_constant<IntegralType, r> {};
template <typename IntegralType, IntegralType r, typename charT>
struct computing_value<10, integer_sequence<charT>, IntegralType, r> 
    : integral_constant<IntegralType, r> {};

template <typename charT, charT c, class = void> struct ch;
template <typename charT, charT c>
struct ch<charT, c, SROOK_DEDUCED_TYPENAME enable_if<('0' <= c && '9' >= c)>::type> 
    : integral_constant<charT, (c - 0x30)> {};
template <typename charT, charT c>
struct ch<charT, c, SROOK_DEDUCED_TYPENAME enable_if<('A' <= c && 'F' >= c)>::type> 
    : integral_constant<charT, (c + 0x0a - 0x41)> {};
template <typename charT, charT c>
struct ch<charT, c, SROOK_DEDUCED_TYPENAME enable_if<('a' <= c && 'f' >= c)>::type> 
    : integral_constant<charT, (c + 0x0a - 0x61)> {};

template <class, class> struct concat;
template <typename charT, charT... l, charT... r>
struct concat<integer_sequence<charT, l...>, integer_sequence<charT, r...>> 
    : type_constant<integer_sequence<charT, l..., r...>> {};

template <class> struct pop_back;
template <typename charT, charT c, charT h, charT... s>
struct pop_back<integer_sequence<charT, c, h, s...>> 
    : concat<integer_sequence<charT, c>, SROOK_DEDUCED_TYPENAME pop_back<integer_sequence<charT, h, s...>>::type> {};
template <typename charT, charT l>
struct pop_back<integer_sequence<charT, l>> 
    : type_constant<integer_sequence<charT>> {};

template <class> struct last;
template <typename charT, charT c>
struct last<integer_sequence<charT, c>> 
    : integral_constant<charT, c> {};
template <typename charT, charT c, charT... s>
struct last<integer_sequence<charT, c, s...>> 
    : last<integer_sequence<charT, s...>> {};

template <typename IntegralType, IntegralType r, std::size_t, std::size_t, class> struct htoi_impl;
template <typename IntegralType, IntegralType r, std::size_t i, std::size_t endpoint, typename charT, charT... hex>
struct htoi_impl <IntegralType, r, i, endpoint, integer_sequence<charT, hex...>> 
    : htoi_impl<
        IntegralType, 
        IntegralType(r + ch<IntegralType, last<integer_sequence<charT, hex...>>::value>::value * srook::math::pow(16, i)), 
        i + 1, 
        endpoint,
        SROOK_DEDUCED_TYPENAME pop_back<integer_sequence<charT, hex...>>::type
    > {};
template <typename IntegralType, IntegralType r, std::size_t endpoint, typename charT, charT... hex>
struct htoi_impl <IntegralType, r, endpoint, endpoint, integer_sequence<charT, hex...>>
    : integral_constant<IntegralType, r> {};

template <typename, class> struct htoi;
template <typename IntegralType, typename charT, charT o, charT x, charT he, charT... x1>
struct htoi<IntegralType, integer_sequence<charT, o, x, he, x1...>> 
    : htoi_impl<IntegralType, 0, 0, sizeof...(x1) + 1, integer_sequence<charT, he, x1...>>::type {};

template <typename charT, charT o, charT x>
struct check_16 
    : bool_constant<o == '0' && (x == 'X' || x == 'x')> {};
template <typename charT, charT o, charT x>
struct check_8
    : bool_constant<o == '0' && x != 'X' && x != 'x'> {};

template <typename charT, charT o, charT x> 
struct deduct_base 
    : integral_constant<std::size_t, check_16<charT, o, x>::value ? 16 : check_8<charT, o, x>::value ? 8 : 10> {};

template <typename IntegralType, class, class = void> struct stoi_impl;
template <typename IntegralType, typename charT, charT o, charT x, charT... s>
struct stoi_impl<IntegralType, integer_sequence<charT, o, x, s...>, SROOK_DEDUCED_TYPENAME enable_if<deduct_base<charT, o, x>::value == 8>::type>
    : computing_value<deduct_base<charT, o, x>::value, integer_sequence<charT, x, s...>, IntegralType> {};
template <typename IntegralType, typename charT, charT o, charT x, charT... s> 
struct stoi_impl<IntegralType, integer_sequence<charT, o, x, s...>, SROOK_DEDUCED_TYPENAME enable_if<deduct_base<charT, o, x>::value == 10>::type>
    : computing_value<deduct_base<charT, o, x>::value, integer_sequence<charT, o, x, s...>, IntegralType> {};
template <typename IntegralType, typename charT, charT o, charT x, charT... s> 
struct stoi_impl<IntegralType, integer_sequence<charT, o, x, s...>, SROOK_DEDUCED_TYPENAME enable_if<deduct_base<charT, o, x>::value == 16>::type> 
    : htoi<IntegralType, integer_sequence<charT, o, x, s...>>::type {};

} // namespace detail

SROOK_INLINE_NAMESPACE_END

// ascii only
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
template <auto... code>
struct stoi : detail::stoi_impl<int, SROOK_DEDUCED_TYPENAME detail::remove_space<integer_sequence<First_t<SROOK_DECLTYPE(code)...>, code...>>::type> {};
template <auto... code>
SROOK_CONSTEXPR int stoi_v = stoi<code...>::value;
#else
template <typename charT, charT... code>
struct stoi : detail::stoi_impl<int, SROOK_DEDUCED_TYPENAME detail::remove_space<integer_sequence<charT, code...>>::type> {};
#if SROOK_CPP_VARIABLE_TEMPLATES
template <typename charT, charT.... code>
SROOK_CONSTEXPR int stoi_v = stoi<code...>::value;
#endif
#endif

} // namespace string
SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
