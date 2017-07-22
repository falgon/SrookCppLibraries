// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TUPLE_ERASE_AT_HPP
#define INCLUDED_SROOK_TUPLE_ERASE_AT_HPP
#include<srook/mpl/variadic_player.hpp>
#include<srook/tuple/tuple_split.hpp>
#include<tuple>

namespace srook{

template<std::size_t target,class... Args>
constexpr Transfer_t<std::tuple,Erase_At_t<target,Args...>> tuple_erase_at(const std::tuple<Args...>& tpl)
{
	static_assert(std::tuple_size<std::tuple<Args...>>::value>=target,"The index value is out of range.");
	return std::tuple_cat(tuple_split_first<target>(tpl),tuple_split_last<target+1>(tpl));
}

} // namespace srook

#endif
