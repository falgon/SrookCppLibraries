// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_ALGORITHM_BINARY_SEARCH_HPP
#define INCLUDED_SROOK_MPL_ALGORITHM_BINARY_SEARCH_HPP
#include<utility>
#include<type_traits>
#include<srook/mpl/constant_sequence/algorithm/partial_head.hpp>
#include<srook/mpl/constant_sequence/algorithm/partial_tail.hpp>
#include<srook/mpl/constant_sequence/algorithm/at.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<bool,std::size_t,class,bool>
struct binary_search;

template<std::size_t target,std::size_t... seq>
struct binary_search<true,target,std::index_sequence<seq...>,false>{
	static constexpr bool value=
		binary_search<
			(at_v<
				partial_tail_t<std::index_sequence<seq...>::size()/2,std::index_sequence<seq...>>::size()/2,
				partial_tail_t<std::index_sequence<seq...>::size()/2,std::index_sequence<seq...>>
			> <= target),
			target,
			partial_tail_t<std::index_sequence<seq...>::size()/2,std::index_sequence<seq...>>,
			false
		>::value;
};

template<std::size_t target,std::size_t... seq>
struct binary_search<false,target,std::index_sequence<seq...>,false>{
	static constexpr bool value=
		binary_search<
			(at_v<
				partial_head_t<std::index_sequence<seq...>::size()/2,std::index_sequence<seq...>>::size()/2,
				partial_head_t<std::index_sequence<seq...>::size()/2,std::index_sequence<seq...>>
			> <= target),
			target,
			partial_head_t<std::index_sequence<seq...>::size()/2,std::index_sequence<seq...>>,
			false
		>::value;
};

template<std::size_t target,std::size_t last1,std::size_t last2>
struct binary_search<true,target,std::index_sequence<last1,last2>,false>{
	static constexpr bool value=(target==last1)or(target==last2);
};

template<std::size_t target,std::size_t last1,std::size_t last2>
struct binary_search<false,target,std::index_sequence<last1,last2>,false>{
	static constexpr bool value=(target==last1)or(target==last2);
};

template<std::size_t target,std::size_t last>
struct binary_search<true,target,std::index_sequence<last>,false>{
	static constexpr bool value=(target==last);
};

template<std::size_t target,std::size_t last>
struct binary_search<false,target,std::index_sequence<last>,false>{
	static constexpr bool value=(target==last);
};

template<bool b,std::size_t target,std::size_t... seq>
struct binary_search<b,target,std::index_sequence<seq...>,true>:std::true_type{};


template<std::size_t target,class Seq>
constexpr bool binary_search_v=binary_search<(at_v<Seq::size()/2,Seq> < target),target,Seq,(target==at_v<Seq::size()/2,Seq>)>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
