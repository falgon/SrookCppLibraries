// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP

#if (defined(__GNUC__) && __GNUC__ >= 5 || __GNUC__ >= 4 && (__GNUC_MINOR__ >= 5 && __GNUC_PATCH_LEVEL__ >= 4)) || (defined(_MSC_VER) && _MSC_VER >= 1800) || defined(__clang__) // There is the __is_standard_layout in Visual C++ 11.0, but its implemention has bugs.
#    define SROOK_HAS_BUILTIN_IS_STANDARD_LAYOUT
#elif defined(__has_builtin)
#    if __has_builtin(__is_standard_layout)
#        define SROOK_HAS_BUILTIN_IS_STANDARD_LAYOUT
#    endif
#endif

#ifdef SROOK_HAS_BUILTIN_IS_STANDARD_LAYOUT
#    include <srook/config/cpp_predefined.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_standard_layout : public bool_constant<__is_standard_layout(T)> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_standard_layout;

#    if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_standard_layout_v = is_standard_layout<T>::value;
#    endif

} // namespace srook

#        undef SROOK_HAS_BUILTIN_IS_STANDARD_LAYOUT
#    else
#        error is_standard_layout: This environment is not supported.
#    endif

#endif
