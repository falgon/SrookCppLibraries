// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_HAS_TRIVIAL_CONSTRUCTOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_HAS_TRIVIAL_CONSTRUCTOR_HPP

#include <srook/type_traits/detail/config.hpp>

#ifdef SROOK_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <srook/type_traits/intrinsics.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/type_traits/is_pod.hpp>

#ifdef SROOK_HAS_TRIVIAL_DESTRUCTOR
#ifdef SROOK_HAS_SGI_TYPE_TRAITS
#   include <srook/type_traits/is_same.hpp>
#elif defined(SROOK_GCC) || defined(__SUNPRO_CC)
#   include <srook/type_traits/is_volatile.hpp>
#endif
#endif

#if (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__ >= 409))\
    || defined(SROOK_CLANG)\
    || (defined(__SUNPRO_CC) && defined(SROOK_HAS_TRIVIAL_CONSTRUCTOR))
#   include <srook/type_traits/is_default_constructible.hpp>
#   define SROOK_TT_TRIVIAL_CONSTRUCT , is_default_constructible<T>
#else
#   define SROOK_TT_TRIVIAL_CONSTRUCT
#endif

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct has_trivial_constructor
#ifdef SROOK_HAS_TRIVIAL_CONSTRUCTOR
    : type_traits::detail::Land<
        type_traits::detail::Lor<is_pod<T>, bool_constant<SROOK_HAS_TRIVIAL_CONSTRUCTOR(T)>>
        SROOK_TT_TRIVIAL_CONSTRUCT
    >
#else
    : is_pod<T>
#endif
    {};
        
#define SROOK_HAS_TRIVIAL_CONSTRUCTOR_FALSE_DEF(X)\
template <> struct has_trivial_constructor<X> : SROOK_FALSE_TYPE {}

SROOK_HAS_TRIVIAL_CONSTRUCTOR_FALSE_DEF(void);
SROOK_HAS_TRIVIAL_CONSTRUCTOR_FALSE_DEF(void const);
SROOK_HAS_TRIVIAL_CONSTRUCTOR_FALSE_DEF(void const volatile);
SROOK_HAS_TRIVIAL_CONSTRUCTOR_FALSE_DEF(void volatile);

#undef SROOK_HAS_TRIVIAL_CONSTRUCTOR_FALSE_DEF
#undef SROOK_TT_TRIVIAL_CONSTRUCT

template <class T>
struct has_trivial_default_constructor : has_trivial_constructor<T> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool has_trivial_constructor_v = has_trivial_constructor<T>::value;
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool has_trivial_default_constructor_v = has_trivial_default_constructor<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::has_trivial_constructor;
using srook::type_traits::has_trivial_default_constructor;

} // namespace srook
#endif
