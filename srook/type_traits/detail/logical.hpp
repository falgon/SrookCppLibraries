// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_DETAIL_LOGICAL_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_DETAIL_LOGICAL_HPP
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/true_false_type.hpp>
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT && !SROOK_CPP_VARIADIC_TEMPLATES
#    include <srook/preprocessor/detail/loop_delim.hpp>
#    include <srook/preprocessor/detail/loop_comma.hpp>
#    include <srook/preprocessor/detail/iterate_def.hpp>
#    include <srook/type_traits/bool_constant.hpp>
#endif

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

template <class...>
struct Lor;
template <>
struct Lor<> : public SROOK_FALSE_TYPE {};
template <class B>
struct Lor<B> : public B {};
template <class B1, class B2>
struct Lor<B1, B2> : public conditional<B1::value, B1, B2>::type {};
template <class B1, class B2, class B3, class... Bn>
struct Lor<B1, B2, B3, Bn...> : public conditional<B1::value, B1, Lor<B2, B3, Bn...> >::type {};

template <class...>
struct Land;
template <>
struct Land<> : public SROOK_TRUE_TYPE {};
template <class B>
struct Land<B> : public B {};
template <class B1, class B2>
struct Land<B1, B2> : public conditional<B1::value, B2, B1>::type {};
template <class B1, class B2, class B3, class... Bn>
struct Land<B1, B2, B3, Bn...> : public conditional<B1::value, Land<B2, B3, Bn...>, B1>::type {};

template <class T>
struct Lnot : public conditional<T::value, SROOK_FALSE_TYPE, SROOK_TRUE_TYPE>::type {};
#else

#define CLASS_DECL(N) class T##N
#define GET_P(N) T##N::value
#define LOR_DEF(N)\
	template <SROOK_PP_LOOP_COMMA(CLASS_DECL, N)>\
	struct Lor_##N : public bool_constant<SROOK_PP_LOOP_DELIM(GET_P, N, ||)> {};
#define LAND_DEF(N)\
	template <SROOK_PP_LOOP_COMMA(CLASS_DECL, N)>\
	struct Land_##N : public bool_constant<SROOK_PP_LOOP_DELIM(GET_P, N, &&)> {};
SROOK_PP_ITERATE(LOR_DEF, 32)
SROOK_PP_ITERATE(LAND_DEF, 32)

template <class T>
struct Lnot : public bool_constant<!T::value> {};

#undef LOR_DEF
#undef LAND_DEF
#undef CLASS_DECL
#undef GET_P
#endif
} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits
} // namespace srook

#endif
