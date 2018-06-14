// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ARGUMENTS_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ARGUMENTS_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/type_traits/detail/config.hpp>
#include <srook/type_traits/is_function.hpp>
#include <srook/type_traits/is_member_function_pointer.hpp>
#include <srook/type_traits/is_callable.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/remove_pointer.hpp>
#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class... Args>
struct true_and_other_type : type_constant<srook::tmpl::vt::packer<Args...>> {
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST bool value = true;
};

template <bool, class>
struct param_selection;

template <class C>
struct param_selection<false, C>
    : param_selection<true, SROOK_DECLTYPE(&C::operator())> {};

template <class F, class C>
struct param_selection<true, F C::*>
    : param_selection<true, F> {};

#define SROOK_TT_PTS_DEF(ARGTYPE_, RESULTTYPE_)\
    template <class R, class... Args>\
    struct param_selection<true, ARGTYPE_>\
        : true_and_other_type<RESULTTYPE_> {}

SROOK_TT_PTS_DEF(R(Args...), Args...);
SROOK_TT_PTS_DEF(R(Args......), Args...);
SROOK_TT_PTS_DEF(R(Args...) const, Args...);
SROOK_TT_PTS_DEF(R(Args......) const, Args...);
SROOK_TT_PTS_DEF(R(Args...) volatile, Args...);
SROOK_TT_PTS_DEF(R(Args......) volatile, Args...);
SROOK_TT_PTS_DEF(R(Args...) const volatile, Args...);
SROOK_TT_PTS_DEF(R(Args......) const volatile, Args...);
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
SROOK_TT_PTS_DEF(R(Args...) noexcept, Args...);
SROOK_TT_PTS_DEF(R(Args......) noexcept, Args...);
SROOK_TT_PTS_DEF(R(Args...) const noexcept, Args...);
SROOK_TT_PTS_DEF(R(Args......) const noexcept, Args...);
SROOK_TT_PTS_DEF(R(Args...) volatile noexcept, Args...);
SROOK_TT_PTS_DEF(R(Args......) volatile noexcept, Args...);
SROOK_TT_PTS_DEF(R(Args...) const volatile noexcept, Args...);
SROOK_TT_PTS_DEF(R(Args......) const volatile noexcept, Args...);
#endif

#undef SROOK_TT_PTS_DEF

template <bool, class>
struct arguments_impl : SROOK_FALSE_TYPE {};

template <class F>
struct arguments_impl<true, F>
    : param_selection<type_traits::detail::Lor<is_function<F>, is_member_function_pointer<F>>::value, F> {};

} // namespace detail

template <class F>
struct arguments 
    : detail::arguments_impl<
        type_traits::detail::Lor<is_function<SROOK_DEDUCED_TYPENAME remove_pointer<F>::type>, is_member_function_pointer<F>, is_callable<F>>::value, 
        SROOK_DEDUCED_TYPENAME conditional<is_member_function_pointer<F>::value, F, SROOK_DEDUCED_TYPENAME remove_pointer<F>::type>::type
    > {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F>
using arguments_t = SROOK_DEDUCED_TYPENAME arguments<F>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class F>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST bool arguments_v = arguments<F>::value;
#endif

// helper classes
template <class F, template <class> class TrueType, template <class> class FalseType>
struct arguments_conditional
    : conditional<arguments<F>::value, TrueType<SROOK_DEDUCED_TYPENAME arguments<F>::type>, FalseType<SROOK_DEDUCED_TYPENAME arguments<F>::type>>::type {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F, template <class> class TrueType, template <class> class FalseType>
using arguments_conditional_t = SROOK_DEDUCED_TYPENAME arguments_conditional<F, TrueType, FalseType>::type;
#endif

template <class F, template <bool, class> class Specialized>
struct arguments_specialized
    : Specialized<arguments<F>::value, SROOK_DEDUCED_TYPENAME arguments<F>::type> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F, template <bool, class> class Specialized>
using arguments_specialized_t = SROOK_DEDUCED_TYPENAME arguments_specialized<F, Specialized>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::arguments;
using srook::type_traits::arguments_conditional;
using srook::type_traits::arguments_specialized;

} // namespace srook

#endif
