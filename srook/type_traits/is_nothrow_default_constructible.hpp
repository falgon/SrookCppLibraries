// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_default_constructible.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct is_nothrow_default_constructible_atom
    : public conditional<noexcept(T()), SROOK_TRUE_TYPE, SROOK_FALSE_TYPE>::type {
};

template <class T, bool = is_array<T>::value>
struct is_nothrow_default_constructible_impl;

template <class T>
struct is_nothrow_default_constructible_impl<T, true>
    : public Land<is_array_known_bounds<T>, is_nothrow_default_constructible_atom<typename remove_all_extents<T>::type> > {
};

template <class T>
struct is_nothrow_default_constructible_impl<T, false> : public is_nothrow_default_constructible_atom<T> {
};

} // namespace detail

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class T>
struct is_nothrow_default_constructible
    : public detail::Land<is_default_constructible<T>, detail::is_nothrow_default_constructible_impl<T> > {
};
#else
template <class T>
struct is_nothrow_default_constructible : public SROOK_FALSE_TYPE {};
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_nothrow_default_constructible;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nothrow_default_constructible_v = type_traits::is_nothrow_default_constructible<T>::value;
#endif

} // namespace srook

#endif
