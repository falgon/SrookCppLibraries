// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_EMPTY_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_EMPTY_HPP

#if (defined(__GNUC__) && __GNUC__ >= 5 || __GNUC__ >= 4 && (__GNUC_MINOR__ >= 5 && __GNUC_PATCH_LEVEL__ >= 4)) || (defined(_MSC_VER) && _MSC_VER >= 1800) || defined(__clang__)
#    define SROOK_HAS_BUILTIN_IS_EMPTY
#elif defined(__has_builtin)
#    if __has_builtin(__is_empty)
#        define SROOK_HAS_BUILTIN_IS_EMPTY
#    endif
#elif defined(__has_feature)
#    if __has_feature(is_empty)
#        define SROOK_HAS_BUILTIN_IS_EMPTY
#    endif
#elif defined(__clang__)
#    if !(__clang_major__ >= 4 || (__clang_major__ >= 3 && __clang_minor__ >= 2))
#        undef SROOK_HAS_BUILTIN_IS_EMPTY
#    endif
#endif

#ifdef SROOK_HAS_BUILTIN_IS_EMPTY
#    include <srook/config/cpp_predefined.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_empty : public bool_constant<__is_empty(T)> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_empty;

#    if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_empty_v = is_empty<T>::value;
#    endif

} // namespace srook

#        undef SROOK_HAS_BUILTIN_IS_EMPTY
#    else
#        error is_empty: This environment is not supported.
#    endif

#endif
