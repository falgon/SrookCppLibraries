// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_COUNT_IF_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_COUNT_IF_HPP
#include<utility>
#include<type_traits>
#include<srook/mpl/constant_sequence/algorithm/filter.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<template<std::size_t>class,class>
struct count_if;

template<template<std::size_t>class pred,std::size_t... seq>
struct count_if<pred,std::index_sequence<seq...>>{
	static constexpr std::size_t value=filter_t<pred,std::index_sequence<seq...>>::size();
};

template<template<std::size_t>class pred,class Seq>
constexpr std::size_t count_if_v=count_if<pred,Seq>::value;


} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook

#endif
