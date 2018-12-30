// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_FILTER_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_FILTER_HPP
#include<type_traits>
#include<utility>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<template<std::size_t>class,class>
struct filter;
template<template<std::size_t>class Cond,std::size_t head,std::size_t... tail>
struct filter<Cond,std::index_sequence<head,tail...>>{
private:
	template<bool,class,class>
	struct if_append;
	template<std::size_t... seq1,std::size_t... seq2>
	struct if_append<true,std::index_sequence<seq1...>,std::index_sequence<seq2...>>{
		using type=std::index_sequence<seq1...,seq2...>;
	};
	template<std::size_t... seq1,std::size_t... seq2>
	struct if_append<false,std::index_sequence<seq1...>,std::index_sequence<seq2...>>{
		using type=std::index_sequence<seq2...>;
	};
	template<bool condition,class Seq1,class Seq2>
	using if_append_t=typename if_append<condition,Seq1,Seq2>::type;

public:
	using type=if_append_t<Cond<head>::value,std::index_sequence<head>,typename filter<Cond,std::index_sequence<tail...>>::type>;
};
template<template<std::size_t>class Cond>
struct filter<Cond,std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<template<std::size_t>class Cond,class Seq>
using filter_t=typename filter<Cond,Seq>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
