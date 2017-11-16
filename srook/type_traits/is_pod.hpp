// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_POD_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_POD_HPP

#if (defined(__GNUC__) && __GNUC__ >= 5 || __GNUC__ >= 4 && (__GNUC_MINOR__ >= 5 && __GNUC_PATCH_LEVEL__ >= 4)) || (defined(_MSC_VER) && _MSC_VER >= 1800) || defined(__clang__)
#    define SROOK_HAS_BUILTIN_IS_POD
#elif defined(__has_builtin)
#    if __has_builtin(__is_pod)
#        define SROOK_HAS_BUILTIN_IS_POD
#    endif
#elif defined(__has_feature)
#    if __has_feature(is_pod)
#        define SROOK_HAS_BUILTIN_IS_POD
#    endif
#elif defined(__clang__)
#    if !(__clang_major__ >= 4 || (__clang_major__ >= 3 && __clang_minor__ >= 2))
#        undef SROOK_HAS_BUILTIN_IS_POD
#    endif
#endif

#ifdef SROOK_HAS_BUILTIN_IS_POD
#    include <srook/config/cpp_predefined.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_pod : public bool_constant<__is_pod(T)> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_pod;

#    if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_pod_v = is_pod<T>::value;
#    endif

} // namespace srook

#        undef SROOK_HAS_BUILTIN_IS_POD
#    else
#        error is_pod: This environment is not supported.
#    endif

#endif
