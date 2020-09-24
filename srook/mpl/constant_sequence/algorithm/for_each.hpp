// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FOR_EACH_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FOR_EACH_HPP
#include<utility>
#include<type_traits>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>
namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<template<std::size_t>class,class>
struct for_each;

template<template<std::size_t>class Ap,std::size_t head,std::size_t... tail>
struct for_each<Ap,std::index_sequence<head,tail...>>{
	using type=concat_t<std::index_sequence<Ap<head>::value>,typename for_each<Ap,std::index_sequence<tail...>>::type>;
};

template<template<std::size_t>class Ap>
struct for_each<Ap,std::index_sequence<>>{
	using type=std::index_sequence<>;
};

template<template<std::size_t>class Ap,class Seq>
using for_each_t=typename for_each<Ap,Seq>::type;

} // inline namespace mpl
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
