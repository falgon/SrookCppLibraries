// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ANY_OF_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ANY_OF_HPP
#include<utility>
#include<type_traits>
#include<srook/config/compiler.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

#ifndef SROOK_IS_CXX11_EARLIER
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
#endif

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
