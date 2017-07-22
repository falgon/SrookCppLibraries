// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_INPLACE_MERGE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_INPLACE_MERGE_HPP
#include<srook/mpl/constant_sequence/algorithm/sort.hpp>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class,class,template<std::size_t,std::size_t>class>
struct inplace_merge;

template<
	std::size_t head1,std::size_t head_next1,std::size_t... tail1,
	std::size_t head2,std::size_t head_next2,std::size_t... tail2,
	template<std::size_t,std::size_t>class comp
>
struct inplace_merge<std::index_sequence<head1,head_next1,tail1...>,std::index_sequence<head2,head_next2,tail2...>,comp>{
private:
	template<bool,std::size_t value>
	struct inplmr_returner{
		using type=std::index_sequence<>;
	};
	template<std::size_t value>
	struct inplmr_returner<true,value>{
		using type=std::index_sequence<value>;
	};

	static constexpr std::size_t put_value=comp<head1,head2>::value?head1:head2;
	
	using put_type=concat_t<
		std::index_sequence<put_value>,
		typename inplmr_returner<(head1==head2),put_value==head1?head2:head1>::type
	>;
public:
	using type=
		concat_t<
			put_type,
			typename inplace_merge<
				concat_t<
					typename inplmr_returner<(put_type::size()!=2 and put_value==head2),head1>::type,
					std::index_sequence<head_next1,tail1...>
				>,
				concat_t<
					typename inplmr_returner<(put_type::size()!=2 and put_value==head1),head2>::type,
					std::index_sequence<head_next2,tail2...>
				>,
				comp
			>::type
		>;
};

template<std::size_t last,std::size_t... seq,template<std::size_t,std::size_t>class comp>
struct inplace_merge<std::index_sequence<last>,std::index_sequence<seq...>,comp>{
	using type=std::index_sequence<last,seq...>;
};

template<std::size_t... seq,std::size_t last,template<std::size_t,std::size_t>class comp>
struct inplace_merge<std::index_sequence<seq...>,std::index_sequence<last>,comp>{
	using type=std::index_sequence<last,seq...>;
};

template<template<std::size_t,std::size_t>class comp>
struct inplace_merge<std::index_sequence<>,std::index_sequence<>,comp>{
	using type=std::index_sequence<>;
};

template<class Seq1,class Seq2,template<std::size_t,std::size_t>class comp=less_or_equal>
using inplace_merge_t=typename inplace_merge<Seq1,Seq2,comp>::type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
