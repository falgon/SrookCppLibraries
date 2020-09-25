// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_LITERAL_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_LITERAL_HPP

#if (defined(__GNUC__) && __GNUC__ >= 5 || __GNUC__ >= 4 && (__GNUC_MINOR__ >= 0 && __GNUC_PATCH_LEVEL__ >= 7)) || (defined(_MSC_VER) && _MSC_VER >= 1800) || defined(__clang__)
#    define SROOK_HAS_BUILTIN_IS_LITERAL __is_literal_type
#elif defined(__has_builtin)
#    if __has_builtin(__is_literal)
#        define SROOK_HAS_BUILTIN_IS_LITERAL __is_literal
#    endif
#elif defined(__has_feature)
#    if __has_feature(is_literal) && defined(__clang__)
#        define SROOK_HAS_BUILTIN_IS_LITERAL __is_literal
#    endif
#endif

#ifdef SROOK_HAS_BUILTIN_IS_LITERAL
#    include <srook/config/cpp_predefined.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_literal : public bool_constant<SROOK_HAS_BUILTIN_IS_LITERAL(T)> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_literal;

#    if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_literal_v = is_literal<T>::value;
#    endif

} // namespace srook

#        undef SROOK_HAS_BUILTIN_IS_LITERAL
#    else
#        error is_literal: This environment is not supported.
#    endif

#endif
