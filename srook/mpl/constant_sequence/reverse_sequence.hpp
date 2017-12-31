// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_REVERSE_SEQUENCE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_REVERSE_SEQUENCE_HPP
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/libraries/type_traits/index_sequence.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <std::size_t, class>
struct make_reverse_sequence_impl;

template <std::size_t n, std::size_t... v>
struct make_reverse_sequence_impl<n, SROOK_INDEX_SEQUENCE<v...>> {
    using type = typename make_reverse_sequence_impl<n - 1, SROOK_INDEX_SEQUENCE<v..., n - 1>>::type;
};

template <std::size_t... v>
struct make_reverse_sequence_impl<0, SROOK_INDEX_SEQUENCE<v...>> {
    using type = SROOK_INDEX_SEQUENCE<v...>;
};

} // namespace detail

template <std::size_t n, class Seq
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
= SROOK_INDEX_SEQUENCE<>
#endif
>
struct make_reverse_sequence_type {
    typedef typename detail::make_reverse_sequence_impl<n, Seq>::type type;
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t n, class Seq
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT   
	= SROOK_INDEX_SEQUENCE<>
#endif
>
using make_reverse_sequence = typename detail::make_reverse_sequence_impl<n, Seq>::type;
#endif

SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
