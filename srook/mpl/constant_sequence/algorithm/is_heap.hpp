// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_MPL_CONSTANT_SEQUENCE_ALGORITHM_IS_HEAP_HPP
#define INCLUDED_MPL_CONSTANT_SEQUENCE_ALGORITHM_IS_HEAP_HPP
#include<srook/mpl/constant_sequence/algorithm/minmax.hpp>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<srook/mpl/constant_sequence/algorithm/partial_head.hpp>
#include<srook/mpl/constant_sequence/algorithm/partial_tail.hpp>
#include<srook/mpl/constant_sequence/algorithm/is_all_comp.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<
	template<std::size_t,std::size_t>class,
	bool,
	class,
	std::size_t,
	std::size_t
>
struct is_heap;

template<
	template<std::size_t,std::size_t>class comp,
	std::size_t... seq,
	std::size_t counter,
	std::size_t size
>
struct is_heap<comp,true,std::index_sequence<seq...>,counter,size>{
	static constexpr bool value=
		is_heap<
			comp,
			is_all_comp<
				comp<
					first_v<partial_head_t<counter*2,std::index_sequence<seq...>>>,
					first_v<partial_tail_t<counter*2,std::index_sequence<seq...>>>
				>::value,
				comp,
				pop_front_t<partial_head_t<counter*2,std::index_sequence<seq...>>>,
				pop_front_t<partial_tail_t<counter*2,std::index_sequence<seq...>>>
			>::value,
			partial_tail_t<counter*2,std::index_sequence<seq...>>,
			counter+1,
			size-1
		>::value;
};

template<
	template<std::size_t,std::size_t>class comp,
	std::size_t... seq,
	std::size_t counter
>
struct is_heap<comp,true,std::index_sequence<seq...>,counter,0>{
	static constexpr bool value=true;
};

template<
	template<std::size_t,std::size_t>class comp,
	std::size_t... seq,
	std::size_t counter,
	std::size_t size
>
struct is_heap<comp,false,std::index_sequence<seq...>,counter,size>{
	static constexpr bool value=false;
};

template<template<std::size_t,std::size_t>class,class>
struct minmax_returner;

template<std::size_t... seq>
struct minmax_returner<less,std::index_sequence<seq...>>{
	static constexpr bool value=
		(min_v<std::index_sequence<seq...>> == first_v<std::index_sequence<seq...>>);
};

template<std::size_t... seq>
struct minmax_returner<greater,std::index_sequence<seq...>>{
	static constexpr bool value=
		(max_v<std::index_sequence<seq...>> == first_v<std::index_sequence<seq...>>);
};

template<class Seq,template<std::size_t,std::size_t>class comp=greater>
static constexpr bool is_heap_v=
	is_heap<
		comp,
		minmax_returner<comp,Seq>::value,
		Seq,
		1,
		(Seq::size()/2+Seq::size()%2==0?1:0)
	>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
