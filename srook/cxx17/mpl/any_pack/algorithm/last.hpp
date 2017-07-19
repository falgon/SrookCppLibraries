// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_LAST_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_LAST_HPP
#include<srook/mpl/variadic_player.hpp>
#include<optional>

namespace srook{
inline namespace mpl{
inline namespace v1{

namespace detail{

template<auto...>
struct last;
template<auto head,auto... tail>
struct last<head,tail...>{
	static constexpr Last_t<decltype(tail)...> value = last<tail...>::value;
};
template<auto tail>
struct last<tail>{
	static constexpr decltype(tail) value = tail;
};
template<>
struct last<>{
	static constexpr std::nullopt_t value = std::nullopt;
};

template<auto... v>
constexpr std::conditional_t<!sizeof...(v),std::nullopt_t,Last_t<decltype(v)...>> last_v = last<v...>::value;

} // namespace detail
} // inline namespace v1
} // inlnie namespace mpl 
} // namespace srook

#endif