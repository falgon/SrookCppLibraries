// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_TUPLE_VECTOR_OPERATION_HPP
#define INCLUDED_SROOK_TUPLE_VECTOR_OPERATION_HPP
#include<tuple>
#include<type_traits>
#include<algorithm>
#include<functional> // for std::plus,std::minus ...
#include<srook/config/require.hpp>
#include<srook/type_traits/conjunction.hpp>
#include<srook/type_traits/is_tuple.hpp>
#include<srook/tuple/tuple_split.hpp>

namespace srook{

namespace detail{


template<std::size_t river_index>
struct tuple_split_adaptor{
	template<class... Ts>
	static constexpr auto apply(const std::tuple<Ts...>& t)
	->decltype(tuple_split<std::tuple_size<std::tuple<Ts...>>::value-river_index>(t).second)
	{
		return tuple_split<std::tuple_size<std::tuple<Ts...>>::value-river_index>(t).second;
	}
};

template<>
struct tuple_split_adaptor<0>{
	template<class... Ts>
	static constexpr std::tuple<> apply(const std::tuple<Ts...>&)
	{
		return std::make_tuple();
	}
};

template<bool>
struct tuple_vector_operation_resulter;

template<>
struct tuple_vector_operation_resulter<true>{
	template<template<class>class Operator,class... L_Tuple,class... R_Tuple,std::size_t index,bool rc,class... Args>
	static constexpr auto
	apply(const std::tuple<L_Tuple...>&,const std::tuple<R_Tuple...>& r,std::integral_constant<std::size_t,index>,std::integral_constant<bool,rc>,Args&&... args)
	{
		constexpr std::size_t river_index=std::tuple_size<std::tuple<R_Tuple...>>::value-std::tuple_size<std::tuple<L_Tuple...>>::value;
		return std::tuple_cat(std::make_tuple(std::forward<Args>(args)...),tuple_split_adaptor<river_index>::apply(r));
	}
};

template<>
struct tuple_vector_operation_resulter<false>{
	template<template<class>class Operator,class... L_Tuple,class... R_Tuple,std::size_t index,bool rc,class... Args>
	static constexpr auto
	apply(const std::tuple<L_Tuple...>& l,const std::tuple<R_Tuple...>&,std::integral_constant<std::size_t,index>,std::integral_constant<bool,rc>,Args&&... args)
	{
		constexpr std::size_t river_index=std::tuple_size<std::tuple<L_Tuple...>>::value-std::tuple_size<std::tuple<R_Tuple...>>::value;
		return std::tuple_cat(std::make_tuple(std::forward<Args>(args)...),tuple_split_adaptor<river_index>::apply(l));
	}
};

struct tuple_Vec_impl{
	struct unpacker{
		template<template<class>class Operator,class... L_Tuple,class... R_Tuple,std::size_t index,bool right_is_bigger,class... Args>
		static constexpr auto
		apply(const std::tuple<L_Tuple...>& l,const std::tuple<R_Tuple...>& r,std::integral_constant<std::size_t,index>,std::integral_constant<bool,right_is_bigger> rc,Args&&... args)
		{
			return 
				tuple_Vec_impl::apply<Operator>(
						l,r,
						std::integral_constant<std::size_t,index-1>(),
						std::move(rc),
						Operator< std::decay_t<decltype(std::get<index>(l))> >()(std::get<index>(l),std::get<index>(r)),
						std::forward<Args>(args)...
				);
		}
	};

	template<template<class>class Operator,class... L_Tuple,class... R_Tuple,std::size_t index,bool right_is_bigger,class... Args>
	static constexpr auto 
	apply(const std::tuple<L_Tuple...>& l,const std::tuple<R_Tuple...>& r,std::integral_constant<std::size_t,index> ic,std::integral_constant<bool,right_is_bigger> rc,Args&&... args)
	{
		return 
			std::conditional_t<
				(right_is_bigger?std::tuple_size<std::tuple<L_Tuple...>>::value:std::tuple_size<std::tuple<R_Tuple...>>::value)==sizeof...(args),
				detail::tuple_vector_operation_resulter<right_is_bigger>,
				detail::tuple_Vec_impl::unpacker
			>::template apply<Operator>(l,r,std::move(ic),std::move(rc),std::forward<Args>(args)...);
	}

	template<template<class>class Operator,class... L_Tuple,class... R_Tuple>
	static constexpr auto tuple_Vec(const std::tuple<L_Tuple...>& l,const std::tuple<R_Tuple...>& r)
	{
		return
			apply<Operator>(
					l,r,
					std::integral_constant<std::size_t,std::min(std::tuple_size<std::tuple<L_Tuple...>>::value,std::tuple_size<std::tuple<R_Tuple...>>::value)-1>(),
					std::integral_constant<bool,std::tuple_size<std::tuple<L_Tuple...>>::value < std::tuple_size<std::tuple<R_Tuple...>>::value>()
			);
	}
};

struct TPL_impl{
	template<template<class>class Operator,class Tuple,class Head_tuple,class... Tpl>
	static constexpr auto tuple_vector_operation_impl(Tuple&& t,Head_tuple&& head,Tpl&&... tpl)
	{
		return tuple_vector_operation_impl<Operator>(tuple_Vec_impl::tuple_Vec<Operator>(std::forward<Tuple>(t),std::forward<Head_tuple>(head)),std::forward<Tpl>(tpl)...);
	}

	template<template<class>class Operator,class Tuple>
	static constexpr Tuple tuple_vector_operation_impl(Tuple&& t)
	{
		return t;
	}
};

} // namespace detail

template<template<class>class Operator,class FirstTpl,class... Tpl,REQUIRES(is_tuple_v<FirstTpl> and conjunction_v<is_tuple<Tpl>...>)>
constexpr auto tuple_vector_operation(FirstTpl&& tpl,Tpl&&... tpls)
->decltype(detail::TPL_impl::template tuple_vector_operation_impl<Operator>(std::forward<FirstTpl>(tpl),std::forward<Tpl>(tpls)...))
{
	return detail::TPL_impl::template tuple_vector_operation_impl<Operator>(std::forward<FirstTpl>(tpl),std::forward<Tpl>(tpls)...);
}

} // namespace srook
#endif
