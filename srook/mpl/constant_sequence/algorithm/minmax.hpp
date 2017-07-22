// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_MINMAX_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_MINMAX_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

namespace{
template<std::size_t L,std::size_t R>
struct Greater_minmax{
	using type=typename std::conditional<(L > R),std::index_sequence<L>,std::index_sequence<R>>::type;
};
template<std::size_t L,std::size_t R>
struct Less_minmax{
	using type=typename std::conditional<(L < R),std::index_sequence<L>,std::index_sequence<R>>::type;
};

template<template<std::size_t,std::size_t>class,class>
struct maxmin_impl;
template<template<std::size_t,std::size_t>class Comp,std::size_t head1,std::size_t head2,std::size_t... tail>
struct maxmin_impl<Comp,std::index_sequence<head1,head2,tail...>>{
	static constexpr std::size_t value=maxmin_impl<Comp,concat_t<typename Comp<head1,head2>::type,std::index_sequence<tail...>>>::value;
};
template<template<std::size_t,std::size_t>class Comp,std::size_t target>
struct maxmin_impl<Comp,std::index_sequence<target>>{
	static constexpr std::size_t value=target;
};
}

template<class Sequence>
constexpr std::size_t max_v=maxmin_impl<Greater_minmax,Sequence>::value;
template<class Sequence>
constexpr std::size_t min_v=maxmin_impl<Less_minmax,Sequence>::value;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
