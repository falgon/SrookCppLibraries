// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_TRANSFER_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_TRANSFER_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<template<class...>class,class>
struct transfer;

template<template<class...>class Range,std::size_t... seq>
struct transfer<Range,std::index_sequence<seq...>>{
	static Range<decltype(first_v<std::index_sequence<seq...>>)> value;
};

template<template<class...>class Range,std::size_t... seq>
Range<decltype(first_v<std::index_sequence<seq...>>)> transfer<Range,std::index_sequence<seq...>>::value={{seq...}};

template<template<class...>class Range,class Seq>
Range<decltype(first_v<Seq>)> transfer_v=transfer<Range,Seq>::value;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
