// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_SAMEVALUE_SEQUENCE
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_SAMEVALUE_SEQUENCE
#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <utility>

namespace srook {
inline namespace mpl {
namespace constant_sequence {
inline namespace v1 {
namespace detail {
template <std::size_t, std::size_t, class>
struct make_samevalue_sequence_impl;

template <std::size_t size, std::size_t fill_value, std::size_t... seq>
struct SROOK_DEPRECATED make_samevalue_sequence_impl<size, fill_value, std::index_sequence<seq...>> {
    typedef typename make_samevalue_sequence_impl<size - 1, fill_value, std::index_sequence<fill_value, seq...>>::type type;
};

template <std::size_t fill_value, std::size_t... seq>
struct SROOK_DEPRECATED make_samevalue_sequence_impl<0, fill_value, std::index_sequence<seq...>> {
    typedef std::index_sequence<seq...> type;
};
} // namespace detail

template <std::size_t size, std::size_t fill_value, class Sequence = std::index_sequence<>>
struct SROOK_DEPRECATED make_samevalue_sequence_type {
    typedef typename detail::make_samevalue_sequence_impl<size, fill_value, Sequence>::type type;
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t size, std::size_t fill_value, class Sequence = std::index_sequence<>>
using make_samevalue_sequence SROOK_DEPRECATED = typename detail::make_samevalue_sequence_impl<size, fill_value, Sequence>::type;
#endif

} // namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook
#endif
