// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_NONE_OF_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_NONE_OF_HPP
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<bool,template<std::size_t>class,class>
struct none_of;

template<template<std::size_t>class pred,std::size_t head,std::size_t... tail>
struct none_of<false,pred,std::index_sequence<head,tail...>>{
	static constexpr bool value=none_of<pred<head>::value,pred,std::index_sequence<tail...>>::value;
};

template<template<std::size_t>class pred>
struct none_of<false,pred,std::index_sequence<>>:std::true_type{};

template<template<std::size_t>class pred,std::size_t... seq>
struct none_of<true,pred,std::index_sequence<seq...>>:std::false_type{};

template<template<std::size_t>class pred,class Seq>
constexpr bool none_of_v=none_of<pred<first_v<Seq>>::value,pred,pop_front_t<Seq>>::value;

} // inline namespace v1
} // namespace constant_sequence 
} // inline namespace mpl 
} // namespace srook
#endif
