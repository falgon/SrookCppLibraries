// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_EQU_DOUBLE_SEQUENCE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_EQU_DOUBLE_SEQUENCE_HPP
#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/mpl/constant_sequence/algorithm/concat.hpp>
#include <srook/mpl/constant_sequence/samevalue_sequence.hpp>
#include <type_traits>
#include <utility>

namespace srook {
inline namespace mpl {
namespace constant_sequence {
inline namespace v1 {
namespace detail {
template <std::size_t, class>
struct make_equ_sequence_impl;

template <std::size_t n, std::size_t... seq>
struct SROOK_DEPRECATED make_equ_sequence_impl<n, std::index_sequence<seq...>> {
    using type = concat_t<typename make_equ_sequence_impl<n - 1, std::index_sequence<seq...>>::type, make_samevalue_sequence<n, n>>;
};

template <std::size_t... seq>
struct SROOK_DEPRECATED make_equ_sequence_impl<0, std::index_sequence<seq...>> {
    using type = std::index_sequence<0, seq...>;
};
} // namespace detail

template <std::size_t n, class Seq = std::index_sequence<>>
struct make_equ_sequence_type {
    typedef typename detail::make_equ_sequence_impl<n, Seq>::type type;
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t n, class Seq = std::index_sequence<>>
using make_equ_sequence SROOK_DEPRECATED = typename detail::make_equ_sequence_impl<n, Seq>::type;
#endif

} // namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook

#endif
