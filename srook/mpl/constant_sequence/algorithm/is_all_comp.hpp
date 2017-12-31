// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_IS_ALL_COMP_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_IS_ALL_COMP_HPP
#include<utility>
#include<type_traits>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>
#include<srook/mpl/constant_sequence/algorithm/sort.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<bool,template<std::size_t,std::size_t>class,class,class>
struct is_all_comp;

template<
	template<std::size_t,std::size_t>class comp,
	std::size_t head1,std::size_t... tail1,
	std::size_t head2,std::size_t... tail2
>
struct is_all_comp<true,comp,std::index_sequence<head1,tail1...>,std::index_sequence<head2,tail2...>>{
	static constexpr bool value=
		is_all_comp<comp<head1,head2>::value,comp,std::index_sequence<tail1...>,std::index_sequence<tail2...>>::value;
};

template<
	template<std::size_t,std::size_t>class comp,
	std::size_t last1,
	std::size_t head2,std::size_t head_next,std::size_t... seq
>
struct is_all_comp<true,comp,std::index_sequence<last1>,std::index_sequence<head2,head_next,seq...>>{
	static constexpr bool value=comp<last1,head2>::value;
};

template<
	template<std::size_t,std::size_t>class comp,
	std::size_t head1,std::size_t head_next,std::size_t... seq,
	std::size_t last2
>
struct is_all_comp<true,comp,std::index_sequence<head1,head_next,seq...>,std::index_sequence<last2>>{
	static constexpr bool value=comp<head1,last2>::value;
};

template<
	template<std::size_t,std::size_t>class comp,
	std::size_t last1,
	std::size_t last2
>
struct is_all_comp<true,comp,std::index_sequence<last1>,std::index_sequence<last2>>{
	static constexpr bool value=comp<last1,last2>::value;
};

template<template<std::size_t,std::size_t>class comp,std::size_t... seq1,std::size_t... seq2>
struct is_all_comp<false,comp,std::index_sequence<seq1...>,std::index_sequence<seq2...>>:std::false_type{};

template<class Seq1,class Seq2>
constexpr bool is_all_less_v=
	is_all_comp<less<first_v<Seq1>,first_v<Seq2>>::value,less,pop_front_t<Seq1>,pop_front_t<Seq2>>::value;

template<class Seq1,class Seq2>
constexpr bool is_all_greater_v=
	is_all_comp<greater<first_v<Seq1>,first_v<Seq2>>::value,greater,pop_front_t<Seq1>,pop_front_t<Seq2>>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
