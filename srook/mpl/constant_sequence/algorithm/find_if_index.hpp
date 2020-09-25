// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FIND_IF_INDEX_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FIND_IF_INDEX_HPP
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<template<std::size_t>class,class,std::size_t>
struct find_if_index;

template<template<std::size_t>class pred,std::size_t head,std::size_t... tail,std::size_t counter>
struct find_if_index<pred,std::index_sequence<head,tail...>,counter>{
	using type=
		concat_t<
			std::conditional_t<
				pred<head>::value,
				std::index_sequence<counter>,
				std::index_sequence<>
			>,
			typename find_if_index<pred,std::index_sequence<tail...>,counter+1>::type
		>;
};

template<template<std::size_t>class pred,std::size_t counter>
struct find_if_index<pred,std::index_sequence<>,counter>{
	using type=std::index_sequence<>;
};

template<template<std::size_t>class pred,class Seq>
using find_if_index_t=typename find_if_index<pred,Seq,0>::type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
