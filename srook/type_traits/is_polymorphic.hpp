// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_POLYMORPHIC_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_POLYMORPHIC_HPP

#if (defined(__GNUC__) && __GNUC__ >= 5 || __GNUC__ >= 4 && (__GNUC_MINOR__ >= 5 && __GNUC_PATCH_LEVEL__ >= 4)) || (defined(_MSC_VER) && _MSC_VER >= 1800) || defined(__clang__)
#    define SROOK_HAS_BUILTIN_IS_POLYMORPHIC
#elif defined(__has_builtin)
#    if __has_builtin(__is_polymorphic)
#        define SROOK_HAS_BUILTIN_IS_POLYMORPHIC
#    endif
#elif defined(__has_feature)
#    if __has_feature(is_polymorphic)
#        define SROOK_HAS_BUILTIN_IS_POLYMORPHIC
#    endif
#elif defined(__clang__)
#    if !(__clang_major__ >= 4 || (__clang_major__ >= 3 && __clang_minor__ >= 2))
#        undef SROOK_HAS_BUILTIN_IS_POLYMORPHIC
#    endif
#endif

#ifdef SROOK_HAS_BUILTIN_IS_POLYMORPHIC
#    include <srook/config/cpp_predefined.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_polymorphic : public bool_constant<__is_polymorphic(T)> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_polymorphic;

#    if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_polymorphic_v = is_polymorphic<T>::value;
#    endif

} // namespace srook

#        undef SROOK_HAS_BUILTIN_IS_POLYMORPHIC
#    else
#        error is_polymorphic: This environment is not supported.
#    endif

#endif
