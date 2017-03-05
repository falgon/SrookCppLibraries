#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ERASE_IF_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ERASE_IF_HPP
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<bool,template<std::size_t>class,class>
struct erase_if;

template<template<std::size_t>class pred,std::size_t head,std::size_t head_next,std::size_t... tail>
struct erase_if<true,pred,std::index_sequence<head,head_next,tail...>>{
	using type=concat_t<
		std::index_sequence<head>,
		typename erase_if<pred<head_next>::value,pred,std::index_sequence<head_next,tail...>>::type
	>;
};

template<template<std::size_t>class pred,std::size_t head,std::size_t head_next,std::size_t... tail>
struct erase_if<false,pred,std::index_sequence<head,head_next,tail...>>{
	using type=typename erase_if<pred<head_next>::value,pred,std::index_sequence<head_next,tail...>>::type;
};

template<template<std::size_t>class pred,std::size_t last>
struct erase_if<true,pred,std::index_sequence<last>>{
	using type=std::index_sequence<last>;
};

template<template<std::size_t>class pred,std::size_t last>
struct erase_if<false,pred,std::index_sequence<last>>{
	using type=std::index_sequence<>;
};

template<template<std::size_t>class pred,class Seq>
using erase_if_t=typename erase_if<pred<first_v<Seq>>::value,pred,Seq>::type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
