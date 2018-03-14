// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_HAS_TRIVIAL_DESTRUCTOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_HAS_TRIVIAL_DESTRUCTOR_HPP

#include <srook/type_traits/detail/config.hpp>

#ifdef SROOK_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <srook/type_traits/intrinsics.hpp>
#include <srook/type_traits/bool_constant.hpp>

#ifdef SROOK_HAS_TRIVIAL_DESTRUCTOR

#if defined(SROOK_INTEL) || defined(SROOK_MSVC)
#   include <srook/type_traits/is_pod.hpp>
#endif
#ifdef SROOK_HAS_SGI_TYPE_TRAITS
#   include <srook/type_traits/is_same.hpp>
#endif

#if defined(SROOK_GCC) || defined(SROOK_CLANG) || defined(__SUNPRO_CC)
#   include <srook/type_traits/is_destructible.hpp>
#endif

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct has_trivial_destructor
    : bool_constant<SROOK_HAS_TRIVIAL_DESTRUCTOR(T)> {};

#else
#   include <srook/type_traits/is_pod.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct has_trivial_destructor
    : is_pod<T> {};

#endif

template <>
struct has_trivial_destructor<void> : SROOK_FALSE_TYPE {};
template <>
#ifndef SROOK_NO_CV_VOID_SPECIALIZATIONS
template <>
struct has_trivial_destructor<void const> : SROOK_FALSE_TYPE {};
template <>
struct has_trivial_destructor<void const volatile> : SROOK_FALSE_TYPE {};
template <>
struct has_trivial_destructor<void volatile> : SROOK_FALSE_TYPE {};
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool has_trivial_destructor_v = has_trivial_destructor<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::has_trivial_destructor;

} // namespace srook
#endif
