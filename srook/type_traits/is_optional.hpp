// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_OPTIONAL_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_OPTIONAL_HPP

#include <srook/type_traits/detail/config.hpp>
#include <srook/type_traits/detail/has_type_gen.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/optional/optional.h>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

SROOK_TT_DEF_HAS_TYPE_IMPL(srook_optional_tag);
SROOK_TT_DEF_HAS_TYPE(srook_optional_tag);

template <class T>
struct is_optional_impl : SROOK_FALSE_TYPE {};

#ifdef SROOK_HAS_STD_OPTIONAL
template <class T>
struct is_optional_impl<std::optional<T>> : SROOK_TRUE_TYPE {};
#endif
#ifdef SROOK_HAS_BOOST_OPTIONAL
template <class T>
struct is_optional_impl<boost::optional<T>> : SROOK_TRUE_TYPE {};
#endif

} // namespace detail

template <class T>
struct is_optional 
    : type_traits::detail::Lor<detail::has_srook_optional_tag<T>, detail::is_optional_impl<T>> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_optional_v = is_optional<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_optional;

} // namespace srook

#endif
