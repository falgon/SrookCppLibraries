// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_BOOL_CONSTANT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_BOOL_CONSTANT_HPP

#include <srook/type_traits/integral_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_ALIAS_TEMPLATES
template <bool B>
using bool_constant = srook::integral_constant<bool, B>;
#else
template <bool B>
struct bool_constant : srook::integral_constant<bool, B> {};
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::bool_constant;

} // namespace srook
#endif
