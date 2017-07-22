// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ANY_OF_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ANY_OF_HPP
#include<utility>
#include<type_traits>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<template<std::size_t>class,class>
struct any_of;

namespace{
template<bool,template<std::size_t>class,class>
struct any_of_core;

template<template<std::size_t>class pred,std::size_t... seq>
struct any_of_core<true,pred,std::index_sequence<seq...>>{
	static constexpr bool value=true;
};

template<template<std::size_t>class pred,std::size_t... seq>
struct any_of_core<false,pred,std::index_sequence<seq...>>{
	static constexpr bool value=any_of<pred,std::index_sequence<seq...>>::value;
};
}

template<template<std::size_t>class pred,std::size_t head,std::size_t... tail>
struct any_of<pred,std::index_sequence<head,tail...>>{
	static constexpr bool value=any_of_core<pred<head>::value,pred,std::index_sequence<tail...>>::value;
};

template<template<std::size_t>class pred,class Sequence>
constexpr bool any_of_v=any_of<pred,Sequence>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
