// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ALL_OF_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ALL_OF_HPP
#include<utility>
#include<type_traits>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

namespace{
template<bool,template<std::size_t>class,class>
struct all_of_core;
}

template<template<std::size_t>class,class>
struct all_of;

template<template<std::size_t>class pred,std::size_t head,std::size_t... tail>
struct all_of<pred,std::index_sequence<head,tail...>>{
	static constexpr bool value=all_of_core<pred<head>::value,pred,std::index_sequence<tail...>>::value;
};

namespace{
template<template<std::size_t>class pred,std::size_t... seq>
struct all_of_core<true,pred,std::index_sequence<seq...>>{
	static constexpr bool value=all_of<pred,std::index_sequence<seq...>>::value;
};

template<template<std::size_t>class pred>
struct all_of_core<true,pred,std::index_sequence<>>{
	static constexpr bool value=true;
};

template<template<std::size_t>class pred,std::size_t... seq>
struct all_of_core<false,pred,std::index_sequence<seq...>>{
	static constexpr bool value=false;
};
}

template<template<std::size_t>class pred,class Sequence>
constexpr bool all_of_v=all_of<pred,Sequence>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namesapce mpl
} // namespace srook

#endif
