// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_STRONG_VARIADIC_CHECK_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_STRONG_VARIADIC_CHECK_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <srook/config/feature.hpp>
#    include <srook/mpl/variadic_types/pack.hpp>
#    include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <bool, template <class, class> class, class, class>
struct strong_variadic_check_impl;

template <template <class, class> class Checker, class... L, class... R>
struct strong_variadic_check_impl<false, Checker, pack<L...>, pack<R...> >
    : public SROOK_FALSE_TYPE {};

template <template <class, class> class Checker, class L, class R>
struct strong_variadic_check_impl<true, Checker, pack<L>, pack<R> >
    : public Checker<L, R> {};

template <template <class, class> class Checker, class LH, class... LT, class RH, class... RT>
struct strong_variadic_check_impl<true, Checker, pack<LH, LT...>, pack<RH, RT...> >
    : public strong_variadic_check_impl<Checker<LH, RH>::value,Checker,
          pack<LT...>,
          pack<RT...> > {};

} // namespace detail

template <template <class, class> class, class, class>
struct strong_variadic_check;

template <template <class, class> class Checker, class LH, class... L, class RH, class... R>
struct strong_variadic_check<Checker, pack<LH, L...>, pack<RH, R...> >
    : public detail::strong_variadic_check_impl<((sizeof...(L) == sizeof...(R)) && Checker<LH, RH>::value), Checker, pack<L...>, pack<R...> > {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::strong_variadic_check;

#    if SROOK_CPP_VARIABLE_TEMPLATES
template <template <class, class> class Checker, class L, class R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool strong_variadic_check_v = strong_variadic_check<Checker, L, R>::value;
#    endif

} // namespace srook

#    endif
#endif
