// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_MOVE_AT_HPP
#define INCLUDED_SROOK_TMPL_VT_MOVE_AT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/move_head.hpp>
#include <srook/tmpl/vt/move_tail.hpp>
#include <srook/tmpl/vt/insert_at.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t from, std::size_t to, class... Xs>
struct move_at_impl2
    : insert_at<
        to, SROOK_DEDUCED_TYPENAME at<from, Xs...>::type,
        SROOK_DEDUCED_TYPENAME concat<
            SROOK_DEDUCED_TYPENAME conditional<
                bool(from), 
                SROOK_DEDUCED_TYPENAME partial_head<from, Xs...>::type,
                packer<>
            >::type,
            SROOK_DEDUCED_TYPENAME partial_tail<from, Xs...>::type
        >::type
      > {};

template <std::size_t from, std::size_t to, class... Xs>
struct move_at_impl1 :
        conditional<
            sizeof...(Xs) ? sizeof...(Xs) - 1 == to : 0,
            SROOK_DEDUCED_TYPENAME move_tail<from, Xs...>::type,
            SROOK_DEDUCED_TYPENAME conditional<
                from == to,
                packer<Xs...>,
                SROOK_DEDUCED_TYPENAME move_at_impl2<from, to, Xs...>::type
            >::type
        > {};

template <std::size_t from, class... Xs>
struct move_at_impl1<from, 0, Xs...> : move_head<from, Xs...> {};

} // namespace detail

template <std::size_t from, std::size_t to, class... Xs>
struct move_at : detail::move_at_impl1<from, to, Xs...> {};

template <std::size_t from, std::size_t to, class... Xs>
struct move_at<from, to, packer<Xs...>>
    : move_at<from, to, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t from, std::size_t to, class... Xs>
using move_at_t = SROOK_DEDUCED_TYPENAME move_at<from, to, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
