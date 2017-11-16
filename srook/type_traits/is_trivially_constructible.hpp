// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP

#if (defined(__GNUC__) && __GNUC__ >= 5 || __GNUC__ >= 4 && (__GNUC_MINOR__ >= 5 && __GNUC_PATCH_LEVEL__ >= 4)) || (defined(_MSC_VER) && _MSC_VER >= 1800) || defined(__clang__)
#    define SROOK_HAS_BUILTIN_IS_TRIVIALLY_CONSTRUCTIBLE
#elif defined(__has_builtin)
#    if __has_builtin(__is_trivially_constructible)
#        define SROOK_HAS_BUILTIN_IS_TRIVIALLY_CONSTRUCTIBLE
#    endif
#endif

#ifdef SROOK_HAS_BUILTIN_IS_TRIVIALLY_CONSTRUCTIBLE
#    include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <srook/config/feature.hpp>
#    include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T, class... Args>
struct is_trivially_constructible : public bool_constant<__is_trivially_constructible(T, Args...)> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_trivially_constructible;

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
template <class T, class... Args>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_trivially_constructible_v = is_trivially_constructible<T, Args...>::value;
#    endif

} // namespace srook

#endif
#        undef SROOK_HAS_BUILTIN_IS_TRIVIALLY_CONSTRUCTIBLE
#    else
#        error is_trivially_constructible: This environment is not supported.
#    endif

#endif
