// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_ALGORITHM_SPLIT_HPP
#define INCLUDED_SROOK_TUPLE_ALGORITHM_SPLIT_HPP

#include <srook/config.hpp>
#include <srook/tuple/algorithm/take.hpp>
#include <srook/tuple/algorithm/drop.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple) {
SROOK_INLINE_NAMESPACE(v1)

template <std::size_t I, class... Ts>
SROOK_CONSTEXPR
std::pair<
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::take<I + 1, Ts...>::type>::type, 
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::drop<I + 1, Ts...>::type>::type
>
split(const std::tuple<Ts...>& t) SROOK_NOEXCEPT_TRUE
{
    return std::make_pair(srook::tuple::take<I + 1>(t), srook::tuple::drop<I + 1>(t));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(tuple, srook)

#endif
