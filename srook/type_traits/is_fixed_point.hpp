// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_FIXED_POINT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_FIXED_POINT_HPP

#include <srook/type_traits/detail/config.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/detail/has_type_gen.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

SROOK_TT_DEF_HAS_TYPE_IMPL(fixed_point_tag);
SROOK_TT_DEF_HAS_TYPE(fixed_point_tag);

} // namespace detail

template <class T>
struct is_fixed_point : detail::has_fixed_point_tag<T> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_fixed_point_v = is_fixed_point<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_fixed_point;

} // namespace srook

#endif
