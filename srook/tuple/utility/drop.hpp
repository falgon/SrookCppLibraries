// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_UTILITY_DROP_HPP
#define INCLUDED_SROOK_TUPLE_UTILITY_DROP_HPP

#include <srook/tuple/utility/detail/utils.hpp>
#include <srook/tmpl/vt/drop.hpp>
#include <srook/tmpl/vt/drop.hpp>
#include <iostream>

SROOK_NESTED_NAMESPACE(srook, tuple, utility) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, std::size_t>
struct drop_impl;

template <std::size_t... Is, std::size_t I>
struct drop_impl<srook::index_sequence<Is...>, I> {
    template <class... Ts>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
    srook::tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME srook::tmpl::vt::drop<I, Ts...>::type>::type
    operator()(const std::tuple<Ts...>& t) SROOK_NOEXCEPT_TRUE
    {
        return std::make_tuple(std::get<Is + I>(t)...);
    }
};

} // namespace detail

template <std::size_t I, class... Ts>
SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
srook::tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME srook::tmpl::vt::drop<I, Ts...>::type>::type
drop(const std::tuple<Ts...>& t) SROOK_NOEXCEPT_TRUE
{
    return detail::drop_impl<SROOK_DEDUCED_TYPENAME make_index_sequence_type<sizeof...(Ts) - I>::type, I>()(t);
}

template <std::size_t I, class L, class R>
SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
srook::tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME srook::tmpl::vt::drop<I, L, R>::type>::type
drop(const std::pair<L, R>& p) SROOK_NOEXCEPT_TRUE
{
    return srook::tuple::utility::drop<I>(std::make_tuple(p.first, p.second));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(utility, tuple, srook)

#endif
