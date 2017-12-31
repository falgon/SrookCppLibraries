// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ENABLE_IF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ENABLE_IF_HPP
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <bool, class
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
	= void
#endif
>
struct enable_if;

template <class T>
struct enable_if<true, T> {
    typedef T type;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::enable_if;

#if SROOK_CPP_ALIAS_TEMPLATES
template <bool b, class T = void>
using enable_if_t = typename enable_if<b, T>::type;
#endif

} // namespace srook

#endif
