// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP

#include <srook/type_traits/is_trivially_constructible.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_trivially_default_constructible : public is_trivially_constructible<T>::type {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_trivially_default_constructible;

#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
template <class T, class>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_trivially_default_constructible_v = is_trivially_default_constructible<T>::value;
#    endif

} // namespace srook

#endif
