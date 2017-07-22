// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TUPLE_ROTATE_HPP
#define INCLUDED_SROOK_TUPLE_ROTATE_HPP
#include<srook/mpl/variadic_player.hpp>
#include<tuple>

namespace srook{

namespace detail{

struct Applyer_Rotate{

struct invoker{
	template<class... Ts,std::size_t v,bool b,class... Args>
	static constexpr Transfer_t<std::tuple,Concat_t<Last_t<Ts...>,PopBack_t<Ts...>>>
	apply(const std::tuple<Ts...>&,std::integral_constant<std::size_t,v>,std::integral_constant<bool,b>,Args&&... args)
	{
		return std::make_tuple(std::forward<Args>(args)...);
	}
};

struct unpacker{
	struct first{
		template<class... Ts,std::size_t v,bool b,class... Args>
		static constexpr Transfer_t<std::tuple,Concat_t<Last_t<Ts...>,PopBack_t<Ts...>>>
		apply(const std::tuple<Ts...>& t,std::integral_constant<std::size_t,v> inc,std::integral_constant<bool,b>,Args&&... args)
		{
			return Applyer_Rotate::apply(t,std::move(inc),std::integral_constant<bool,false>(),std::get<std::tuple_size<std::tuple<Ts...>>::value-1>(t),std::forward<Args>(args)...);
		}
	};
	struct not_first{
		template<class... Ts,std::size_t v,bool b,class... Args>
		static constexpr Transfer_t<std::tuple,Concat_t<Last_t<Ts...>,PopBack_t<Ts...>>>
		apply(const std::tuple<Ts...>& t,std::integral_constant<std::size_t,v>,std::integral_constant<bool,b> ib,Args&&... args)
		{
			return Applyer_Rotate::apply(t,std::integral_constant<std::size_t,v+1>(),std::move(ib),std::forward<Args>(args)...,std::get<v>(t));
		}
	};

	template<class... Ts,std::size_t v,bool b,class... Args>
	static constexpr Transfer_t<std::tuple,Concat_t<Last_t<Ts...>,PopBack_t<Ts...>>>
	apply(const std::tuple<Ts...>& t,std::integral_constant<std::size_t,v> ic,std::integral_constant<bool,b> ib,Args&&... args)
	{
		return std::conditional_t<b,first,not_first>::apply(t,std::move(ic),std::move(ib),std::forward<Args>(args)...);
	}
};

template<class... Ts,std::size_t v,bool b,class... Args>
static constexpr Transfer_t<std::tuple,Concat_t<Last_t<Ts...>,PopBack_t<Ts...>>>
apply(const std::tuple<Ts...>& t,std::integral_constant<std::size_t,v> ic,std::integral_constant<bool,b> ib,Args&&... args)
{
	return std::conditional_t<sizeof...(args)==std::tuple_size<std::tuple<Ts...>>::value,invoker,unpacker>::apply(t,std::move(ic),std::move(ib),std::forward<Args>(args)...);
}

};

} // namespace detail

template<class... Ts>
constexpr Transfer_t<std::tuple,Concat_t<Last_t<Ts...>,PopBack_t<Ts...>>>
tuple_rotate(const std::tuple<Ts...>& t)
{
	return detail::Applyer_Rotate::apply(t,std::integral_constant<std::size_t,0>(),std::integral_constant<bool,true>());
}

} // namespace srook

#endif
