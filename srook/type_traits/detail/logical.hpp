// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_DETAIL_LOGICAL_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_DETAIL_LOGICAL_HPP
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/conditional.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class...> struct Lor;
template <>
struct Lor<> : public SROOK_FALSE_TYPE {};
template <class B>
struct Lor<B> : public B {};
template <class B1, class B2>
struct Lor<B1, B2> : public conditional<B1::value, B1, B2>::type {};
template <class B1, class B2, class B3, class... Bn>
struct Lor<B1, B2, B3, Bn...> : public conditional<B1::value, B1, Lor<B2, B3, Bn...>>::type {};

template <class...> struct Land;
template <>
struct Land<> : public SROOK_TRUE_TYPE {};
template <class B>
struct Land<B> : public B {};
template <class B1, class B2>
struct Land<B1, B2> : public conditional<B1::value, B2, B1>::type {};
template <class B1, class B2, class B3, class... Bn>
struct Land<B1, B2, B3, Bn...> : public conditional<B1::value, Land<B2, B3, Bn...>, B1>::type{};

template <class T>
struct Lnot : public conditional<T::value, SROOK_FALSE_TYPE, SROOK_TRUE_TYPE>::type {};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

} // namespace srook

#endif
