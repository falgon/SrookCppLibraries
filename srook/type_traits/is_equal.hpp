// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_EQUAL_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_EQUAL_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/mpl/variadic_types/pack.hpp>
#include <srook/config/feature.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T1, class T2>
struct is_equal : is_same<T1, T2> {};

namespace detail {

template <bool, class, class>
struct is_equal_impl;

template <class LHead, class... LTail, class RHead, class... RTail>
struct is_equal_impl<true, pack<LHead, LTail...>, pack<RHead, RTail...>> 
	: public is_equal_impl<is_same<LHead, RHead>::value, pack<LTail...>, pack<RTail...>> {};

template <class... L, class... R>
struct is_equal_impl<false, pack<L...>, pack<R...>> : SROOK_FALSE_TYPE {};

template <class L, class R>
struct is_equal_impl<true, pack<L>, pack<R>> : is_equal<L, R> {};

} // namespace detail

template <class LHead, class... LTail, class RHead, class... RTail>
struct is_equal<pack<LHead, LTail...>, pack<RHead, RTail...>> 
	: public detail::is_equal_impl<sizeof...(LTail) == sizeof...(RTail) && is_same<LHead, RHead>::value, pack<LTail...>, pack<RTail...>> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_equal;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_equal_v = is_equal<L, R>::value;
#endif

} // namespace srook


#endif
#endif
