// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SWAP_AT_HPP
#define INCLUDED_SROOK_CONSTANT_SWAP_AT_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>
#include<srook/mpl/constant_sequence/algorithm/at.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class,std::size_t,class>
struct swap_at;
template<
	std::size_t left_target_index,std::size_t lhead,std::size_t... ltail,
	std::size_t right_target_index,std::size_t rhead,std::size_t... rtail
>
struct swap_at<left_target_index,std::index_sequence<lhead,ltail...>,right_target_index,std::index_sequence<rhead,rtail...>>{
	using L_type=
		concat_t<
			std::index_sequence<lhead>,
			typename swap_at<
				left_target_index-1,
				std::index_sequence<ltail...>,
				right_target_index,
				std::index_sequence<rhead,rtail...>
			>::L_type
		>;
	using R_type=
		concat_t<
			std::index_sequence<rhead>,
			typename swap_at<
				left_target_index,
				std::index_sequence<lhead,ltail...>,
				right_target_index-1,
				std::index_sequence<rtail...>
			>::R_type
		>;
};

template<
	std::size_t lhead,std::size_t... ltail,
	std::size_t right_target_index,std::size_t rhead,std::size_t... rtail
>
struct swap_at<0,std::index_sequence<lhead,ltail...>,right_target_index,std::index_sequence<rhead,rtail...>>{
	using L_type=
		std::index_sequence<at_v<right_target_index,std::index_sequence<rhead,rtail...>>,ltail...>;
	using R_type=
		std::index_sequence<>;
};

template<
	std::size_t left_target_index,std::size_t lhead,std::size_t... ltail,
	std::size_t rhead,std::size_t... rtail
>
struct swap_at<left_target_index,std::index_sequence<lhead,ltail...>,0,std::index_sequence<rhead,rtail...>>{
	using Ltype=
		std::index_sequence<>;
	using R_type=
		std::index_sequence<at_v<left_target_index,std::index_sequence<lhead,ltail...>>,rtail...>;
};

template<std::size_t left_target_index,class Seq1,std::size_t right_target_index,class Seq2>
using swap_at_L=typename swap_at<left_target_index,Seq1,right_target_index,Seq2>::L_type;
template<std::size_t left_target_index,class Seq1,std::size_t right_target_index,class Seq2>
using swap_at_R=typename swap_at<left_target_index,Seq1,right_target_index,Seq2>::R_type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
