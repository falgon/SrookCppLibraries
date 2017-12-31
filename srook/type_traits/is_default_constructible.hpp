// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/extent.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_array.hpp>
#include <srook/type_traits/is_void.hpp>
#include <srook/type_traits/remove_all_extents.hpp>
#include <srook/utility/declval.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct is_array_known_bounds : public integral_constant<bool, (extent<T>::value > 0)> {
};

template <class T>
struct is_array_unknown_bounds : public integral_constant<bool, is_array<T>::value && !extent<T>::value> {
};

struct is_default_constructible_impl_ {
    template <class T, class = decltype(T())>
    static SROOK_TRUE_TYPE test(int);

    template <class>
    static SROOK_FALSE_TYPE test(...);
};

template <class T>
struct is_default_constructible_impl : public is_default_constructible_impl_ {
    typedef decltype(test<T>(0)) type;
};

template <class T>
struct is_default_constructible_atom : public conditional<(!is_void<T>::value) && is_default_constructible_impl<T>::type::value,
                                                          SROOK_TRUE_TYPE, SROOK_FALSE_TYPE>::type {
};

template <class T, bool = is_array<T>::value>
struct is_safe_default_constructible;

template <class T>
struct is_safe_default_constructible<T, true> : public integral_constant<bool, is_array_known_bounds<T>::value && is_default_constructible_atom<typename remove_all_extents<T>::type>::value> {
};

template <class T>
struct is_safe_default_constructible<T, false> : public is_default_constructible_atom<T>::type {
};

} // namespace detail

template <class T>
struct is_default_constructible : public detail::is_safe_default_constructible<T>::type {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_default_constructible;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_default_constructible_v = is_default_constructible<T>::value;
#endif

} // namespace srook

#endif
