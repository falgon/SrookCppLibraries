// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP

#if (defined(__GNUC__) && __GNUC__ >= 5 || __GNUC__ >= 4 && (__GNUC_MINOR__ >= 5 && __GNUC_PATCH_LEVEL__ >= 4)) || (defined(_MSC_VER) && _MSC_VER >= 1800) || defined(__clang__)
#    define SROOK_HAS_BUILTIN_IS_TRIVIALLY_COPYABLE
#elif defined(__has_builtin)
#    if __has_builtin(__is_trivially_copyable)
#        define SROOK_HAS_BUILTIN_IS_TRIVIALLY_COPYABLE
#    endif
#endif

#ifdef SROOK_HAS_BUILTIN_IS_TRIVIALLY_COPYABLE
#    include <srook/config/cpp_predefined.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_trivially_copyable : public bool_constant<__is_trivially_copyable(T)> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_trivially_copyable;

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_trivially_copyable_v = is_trivially_copyable<T>::value;
#    endif

} // namespace srook

#        undef SROOK_HAS_BUILTIN_IS_TRIVIALLY_COPYABLE
#    else
#        error is_trivially_copyable: This environment is not supported.
#    endif

#endif
