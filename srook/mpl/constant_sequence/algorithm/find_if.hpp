// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FIND_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FIND_HPP
#include<utility>
#include<type_traits>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

namespace find_if_tag_scope{
struct find_if_tag;
struct find_if_not_tag;
}

template<bool,template<std::size_t>class,class,std::size_t,class>
struct find_if;

template<template<std::size_t>class pred,std::size_t head,std::size_t... tail,std::size_t counter>
struct find_if<false,pred,std::index_sequence<head,tail...>,counter,find_if_tag_scope::find_if_tag>{
	static constexpr int value=1+find_if<pred<head>::value,pred,std::index_sequence<tail...>,counter+1,find_if_tag_scope::find_if_tag>::value;
};

template<template<std::size_t>class pred,std::size_t head,std::size_t... tail,std::size_t counter>
struct find_if<false,pred,std::index_sequence<head,tail...>,counter,find_if_tag_scope::find_if_not_tag>{
	static constexpr int value=1+find_if<!pred<head>::value,pred,std::index_sequence<tail...>,counter+1,find_if_tag_scope::find_if_not_tag>::value;
};

template<template<std::size_t>class pred,std::size_t counter,class tag>
struct find_if<false,pred,std::index_sequence<>,counter,tag>{
	static constexpr int value=-counter-1;
};

template<template<std::size_t>class pred,std::size_t... seq,std::size_t counter,class tag>
struct find_if<true,pred,std::index_sequence<seq...>,counter,tag>{
	static constexpr int value=0;
};

template<template<std::size_t>class pred,class Sequence>
constexpr int find_if_v=find_if<pred<first_v<Sequence>>::value,pred,pop_front_t<Sequence>,0,find_if_tag_scope::find_if_tag>::value;

} // inlin namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
