// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MAKE_SAME_TYPE_SEQUENCE_HPP
#define INCLUDED_SROOK_MAKE_SAME_TYPE_SEQUENCE_HPP

#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/mpl/variadic_types/variadic_player.hpp>

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <bool, std::size_t, class...>
struct make_same_type_sequence_impl;

template <std::size_t n, class Head, class... Ts>
struct SROOK_DEPRECATED make_same_type_sequence_impl<true, n, pack<Head, Ts...>> {
    typedef typename make_same_type_sequence_impl<bool(n - 1), n - 1, pack<Head, Head, Ts...>>::type type;
};

template <class... Ts>
struct SROOK_DEPRECATED make_same_type_sequence_impl<false, 0, pack<Ts...>> {
    typedef PopBack_t<Ts...> type;
};

} // namespace detail

template <std::size_t n, class T>
struct make_same_type_sequence_type {
    typedef typename detail::make_same_type_sequence_impl<bool(n), n, pack<T>>::type type;
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t n, class T>
using make_same_type_sequence SROOK_DEPRECATED = typename detail::make_same_type_sequence_impl<bool(n), n, pack<T>>::type;
#endif

} // namespace v1
} // namespace mpl
} // namespace srook

#endif
