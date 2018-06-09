// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_PARAM_TYPES_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_PARAM_TYPES_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/type_traits/detail/config.hpp>
#include <srook/type_traits/is_function.hpp>
#include <srook/type_traits/is_member_function_pointer.hpp>
#include <srook/type_traits/is_callable.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class... Args>
struct true_and_other_type : type_constant<srook::tmpl::vt::packer<Args...>> {
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST bool value = true;
};

template <bool, class C>
struct param_selection
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

#undef SROOK_TT_PTS_DEF

template <bool, class>
struct param_types_impl : SROOK_FALSE_TYPE {};

template <class F>
struct param_types_impl<true, F>
    : param_selection<type_traits::detail::Lor<is_function<F>, is_member_function_pointer<F>>::value, F> {};

} // namespace detail

template <class F>
struct param_types 
    : detail::param_types_impl<type_traits::detail::Lor<is_function<F>, is_member_function_pointer<F>, is_callable<F>>::value, F> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F>
using param_types_t = SROOK_DEDUCED_TYPENAME param_types<F>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class F>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST bool param_types_v = param_types<F>::value;
#endif

// helper classes
template <class F, template <class> class TrueType, template <class> class FalseType>
struct param_types_conditional
    : conditional<param_types<F>::value, TrueType<SROOK_DEDUCED_TYPENAME param_types<F>::type>, FalseType<SROOK_DEDUCED_TYPENAME param_types<F>::type>>::type {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F, template <class> class TrueType, template <class> class FalseType>
using param_types_conditional_t = SROOK_DEDUCED_TYPENAME param_types_conditional<F, TrueType, FalseType>::type;
#endif

template <class F, template <bool, class> class Specialized>
struct param_types_specialized
    : Specialized<param_types<F>::value, SROOK_DEDUCED_TYPENAME param_types<F>::type> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F, template <bool, class> class Specialized>
using param_types_specialized_t = SROOK_DEDUCED_TYPENAME param_types_specialized<F, Specialized>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::param_types;
using srook::type_traits::param_types_conditional;
using srook::type_traits::param_types_specialized;

} // namespace srook

#endif
