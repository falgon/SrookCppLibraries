// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/extent.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_array.hpp>
#include <srook/type_traits/is_default_constructible.hpp>
#include <srook/type_traits/is_function.hpp>
#include <srook/type_traits/is_reference.hpp>
#include <srook/type_traits/is_scalar.hpp>
#include <srook/type_traits/remove_all_extents.hpp>
#include <srook/utility/declval.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

struct is_destructible_impl_ {
    template <class T, typename = decltype(declval<T&>().~T())>
    static SROOK_TRUE_TYPE test(int);
    template <class>
    static SROOK_FALSE_TYPE test(...);
};

template <class T>
struct is_destructible_impl : public is_destructible_impl_ {
    typedef decltype(test<T>(0)) type;
};

template <class T,
          bool = is_void<T>::value || is_array_unknown_bounds<T>::value || is_function<T>::value,
          bool = is_reference<T>::value || is_scalar<T>::value>
struct is_safe_destructible;

template <class T>
struct is_safe_destructible<T, false, false> : public is_destructible_impl<typename remove_all_extents<T>::type>::type {
};

template <class T>
struct is_safe_destructible<T, true, false> : public SROOK_FALSE_TYPE {
};

template <class T>
struct is_safe_destructible<T, false, true> : public SROOK_TRUE_TYPE {
};

} // namespace detail

template <class T>
struct is_destructible : public detail::is_safe_destructible<T>::type {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_destructible;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_destructible_v = is_destructible<T>::value;
#endif

} // namespace srook

#endif
