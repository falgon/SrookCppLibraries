// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_BOUNDER_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_BOUNDER_HPP
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t l,std::size_t r>
using comp_exp1=std::integral_constant<bool,(l<=r)>;

template<std::size_t l,std::size_t r>
using comp_exp2=std::integral_constant<bool,(l<r)>;


template<bool,template<std::size_t,std::size_t>class,std::size_t,class,int>
struct bounder;

template<template<std::size_t,std::size_t>class comp,std::size_t target,std::size_t... seq,int count>
struct bounder<true,comp,target,std::index_sequence<seq...>,count>{
	static constexpr int value=0;
};

template<template<std::size_t,std::size_t>class comp,std::size_t target,std::size_t head,std::size_t... tail,int count>
struct bounder<false,comp,target,std::index_sequence<head,tail...>,count>{
	static constexpr int value=1+bounder<comp<target,head>::value,comp,target,std::index_sequence<tail...>,count+1>::value;
};

template<template<std::size_t,std::size_t>class comp,std::size_t target,int count>
struct bounder<false,comp,target,std::index_sequence<>,count>{
	static constexpr int value=-count-1;
};

template<std::size_t target,class Sequence>
constexpr int lower_bound_v=bounder<comp_exp1<target,first_v<Sequence>>::value,comp_exp1,target,pop_front_t<Sequence>,0>::value;

template<std::size_t target,class Sequence>
constexpr int upper_bound_v=bounder<comp_exp2<target,first_v<Sequence>>::value,comp_exp2,target,pop_front_t<Sequence>,0>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
