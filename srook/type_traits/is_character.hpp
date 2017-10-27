// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_CHARACTER_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_CHARACTER_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/is_same.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <typename T>
struct is_character
    : std::integral_constant<bool,
                             srook::is_same<T, char>::value || srook::is_same<T, wchar_t>::value || srook::is_same<T, char16_t>::value || srook::is_same<T, char32_t>::value || srook::is_same<T, unsigned char>::value || srook::is_same<T, signed char>::value> {
};

#if SROOK_CPP_VARIABLE_TEMPLATES

template <typename T>
SROOK_INLINE_VARIABLE constexpr bool is_character_v = is_character<T>::value;

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_character;
using type_traits::is_character_v;

} // namespace srook

#endif
