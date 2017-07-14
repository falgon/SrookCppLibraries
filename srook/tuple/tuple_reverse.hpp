// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_TUPLE_REVERSE_HPP
#define INCLUDED_SROOK_TUPLE_REVERSE_HPP
#include<srook/mpl/variadic_player.hpp>
#include<srook/mpl/constant_sequence/reverse_sequence.hpp>
#include<tuple>

namespace srook{

namespace detail{

template<class... Ts,std::size_t... n>
constexpr Transfer_t<std::tuple,Reverse_t<Ts...>>
tuple_reverse_impl(const std::tuple<Ts...>& tpl,std::index_sequence<n...>)
{
	return std::make_tuple(std::get<n>(tpl)...);
}

} // namespace detail


template<class... Ts>
constexpr Transfer_t<std::tuple,Reverse_t<Ts...>> tuple_reverse(const std::tuple<Ts...>& tpl)
{
	return detail::tuple_reverse_impl(tpl,make_reverse_sequence<std::tuple_size<std::tuple<Ts...>>::value>());
}

} // namespace srook
#endif
