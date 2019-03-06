// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_POD_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_POD_HPP

#include <cstddef>
#include <srook/type_traits/detail/config.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/type_traits/intrinsics.hpp>
#include <srook/type_traits/is_scalar.hpp>
#include <srook/type_traits/is_void.hpp>

#ifdef __SUNPRO_CC
#   include <srook/type_traits/is_function.hpp>
#endif

#ifndef SROOK_IS_POD
#   define SROOK_INTERNAL_IS_POD(T) false
#else
#   define SROOK_INTERNAL_IS_POD(T) SROOK_IS_POD(T)
#endif

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_pod
    : type_traits::detail::Lor<is_scalar<T>, is_void<T>, bool_constant<SROOK_INTERNAL_IS_POD(T)>> {};

#ifndef SROOK_NO_ARRAY_TYPE_SPECIALIZATIONS
template <class T, std::size_t N>
struct is_pod<T[N]> : is_pod<T> {};
#endif

#define SROOK_IS_POD_TRUE_DEF(T)\
template <> struct is_pod<T> : SROOK_TRUE_TYPE {}

SROOK_IS_POD_TRUE_DEF(void);
#if SROOK_NO_CV_VOID_SPECIALIZATIONS
SROOK_IS_POD_TRUE_DEF(void const);
SROOK_IS_POD_TRUE_DEF(void const volatile);
SROOK_IS_POD_TRUE_DEF(void volatile);
#endif
#undef SROOK_IS_POD_TRUE_DEF
#undef SROOK_INTERNAL_IS_POD

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_pod_v = is_pod<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_pod;

} // namespace srook

#endif
