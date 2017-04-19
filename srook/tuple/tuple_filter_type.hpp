#ifndef INCLUDED_SROOK_TUPLE_FILTER_TYPE_HPP
#define INCLUDED_SROOK_TUPLE_FILTER_TYPE_HPP
#include<srook/mpl/variadic_player.hpp>
#include<srook/config/require.hpp>
#include<tuple>

namespace srook{

namespace detail{

struct Apply_Filter_Type{
	struct invoker{
		template<template<class>class Pred,class... Ts,std::size_t n,class... Args>
		static constexpr auto apply(const std::tuple<Ts...>&,const std::integral_constant<std::size_t,n>&,Args&&... args)
		-> Transfer_t<std::tuple,Erase_if_t<Pred,Ts...>>
		{
			return std::make_tuple(std::forward<Args>(args)...);
		}
	};

	struct unpacker{
		template<template<class>class Pred,class... Ts,std::size_t n,class... Args>
		static constexpr auto apply(const std::tuple<Ts...>& tpl,const std::integral_constant<std::size_t,n>&,Args&&... args)
		-> std::enable_if_t<Pred<std::decay_t<decltype(std::get<n>(tpl))>>::value,Transfer_t<std::tuple,Erase_if_t<Pred,Ts...>>>
		{
			return Apply_Filter_Type::template apply<Pred>(tpl,std::integral_constant<std::size_t,n-1>(),std::get<n>(tpl),std::forward<Args>(args)...);
		}
		
		template<template<class>class Pred,class... Ts,std::size_t n,class... Args>
		static constexpr auto apply(const std::tuple<Ts...>& tpl,const std::integral_constant<std::size_t,n>&,Args&&... args)
		-> std::enable_if_t<!Pred<std::decay_t<decltype(std::get<n>(tpl))>>::value,Transfer_t<std::tuple,Erase_if_t<Pred,Ts...>>>
		{
			return Apply_Filter_Type::template apply<Pred>(tpl,std::integral_constant<std::size_t,n-1>(),std::forward<Args>(args)...);
		}
	};

	template<template<class>class Pred,class... Ts,std::size_t n,class... Args>
	static constexpr auto apply(const std::tuple<Ts...>& tpl,std::integral_constant<std::size_t,n> ic,Args&&... args)
	-> Transfer_t<std::tuple,Erase_if_t<Pred,Ts...>>
	{
		return std::conditional_t<Erase_if_t<Pred,Ts...>::size==sizeof...(Args),invoker,unpacker>::template apply<Pred>(tpl,std::move(ic),std::forward<Args>(args)...);
	}
};

} // namespace detail

template<template<class>class Pred,class... Args>
constexpr Transfer_t<std::tuple,Erase_if_t<Pred,Args...>> tuple_filter_type(const std::tuple<Args...>& tpl)
{
	return detail::Apply_Filter_Type::apply<Pred>(tpl,std::integral_constant<std::size_t,std::tuple_size<std::tuple<Args...>>::value-1>());
}


} // namespace srook

#endif
