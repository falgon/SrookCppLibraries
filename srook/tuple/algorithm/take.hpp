// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_ALGORITHM_TAKE_HPP
#define INCLUDED_SROOK_TUPLE_ALGORITHM_TAKE_HPP

#include <srook/config.hpp>
#include <srook/tmpl/vt/take.hpp>
#include <srook/tmpl/vt/at.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/utility/index_sequence.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t... I, class... Ts>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, Ts...>::type...>::type
take_impl(index_sequence<I...>, const std::tuple<Ts...>& t) SROOK_NOEXCEPT_TRUE
{
    return std::make_tuple(std::get<I>(t)...);
}

} // namespace detail

template <std::size_t I, class... Ts>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::take<I, Ts...>::type>::type
take(const std::tuple<Ts...>& t) SROOK_NOEXCEPT_TRUE
{
    return detail::take_impl(SROOK_DEDUCED_TYPENAME make_index_sequence_type<I>::type{}, t);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(tuple, srook)

#endif
