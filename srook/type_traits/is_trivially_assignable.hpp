// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP

#if (defined(__GNUC__) && __GNUC__ >= 5 || __GNUC__ >= 4 && (__GNUC_MINOR__ >= 5 && __GNUC_PATCH_LEVEL__ >= 4)) || (defined(_MSC_VER) && _MSC_VER >= 1800) || defined(__clang__)
#    define SROOK_HAS_BUILTIN_IS_TRIVIALLY_ASSIGNABLE
#elif defined(__has_builtin)
#    if __has_builtin(__is_trivially_assignable)
#        define SROOK_HAS_BUILTIN_IS_TRIVIALLY_ASSIGNABLE
#    endif
#endif

#ifdef SROOK_HAS_BUILTIN_IS_TRIVIALLY_ASSIGNABLE
#    include <srook/config/cpp_predefined.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T, class U>
struct is_trivially_assignable : public bool_constant<__is_trivially_assignable(T, U)> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_trivially_assignable;

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
template <class T, class U>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_trivially_assignable_v = is_trivially_assignable<T, U>::value;
#    endif

} // namespace srook

#        undef SROOK_HAS_BUILTIN_IS_TRIVIALLY_ASSIGNABLE
#    else
#        error is_trivially_assignable: This environment is not supported.
#    endif

#endif
