// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_ALGORITHM_DROP_HPP
#define INCLUDED_SROOK_TUPLE_ALGORITHM_DROP_HPP

#include <srook/config.hpp>
#include <srook/tmpl/vt/drop.hpp>
#include <srook/tmpl/vt/at.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/map.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/utility/index_sequence.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class R, std::size_t I>
struct drop_impl2 {
    template <class T, class... Ts>
    SROOK_CONSTEXPR static R
    exec(T&&, Ts&&... ts) SROOK_NOEXCEPT_TRUE
    {
        return drop_impl2<R, I - 1>::exec(srook::forward<Ts>(ts)...);
    }

    SROOK_CONSTEXPR static std::tuple<> exec() SROOK_NOEXCEPT_TRUE
    {
        return std::make_tuple();
    }
};

template <class R>
struct drop_impl2<R, 0> {
    template <class... Ts>
    SROOK_CONSTEXPR static R 
    exec(Ts&&... ts) SROOK_NOEXCEPT_TRUE
    {
        return std::make_tuple(srook::forward<Ts>(ts)...);
    }
};

template <std::size_t I, std::size_t... Is, class... Ts>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::drop<I, Ts...>::type>::type
drop_impl1(index_sequence<Is...>, const std::tuple<Ts...>& t) SROOK_NOEXCEPT_TRUE
{
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::drop<I, Ts...>::type>::type result_type;
    return drop_impl2<result_type, I>::exec(std::get<Is>(t)...);
}

} // namespace detail

template <std::size_t I, class... Ts>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::drop<I, Ts...>::type>::type
drop(const std::tuple<Ts...>& t) SROOK_NOEXCEPT_TRUE
{
    return detail::drop_impl1<I>(SROOK_DEDUCED_TYPENAME make_index_sequence_type<std::tuple_size<std::tuple<Ts...>>::value>::type{}, t);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(tuple, srook)

#endif
