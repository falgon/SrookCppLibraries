// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_IS_PARTITIONED_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_IS_PARTITIONED_HPP
#include<type_traits>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

namespace{

struct none_tag;
struct true_tag;
struct false_tag;

}

template<
	bool,
	template<std::size_t>class,
	class,
	class,
	class,
	class
>
struct is_partitioned;

template<template<std::size_t>class pred,std::size_t head,std::size_t... tail>
struct is_partitioned<true,pred,std::index_sequence<head,tail...>,true_tag,none_tag,none_tag>{
	static constexpr bool value=
		is_partitioned<
			pred<head>::value,
			pred,
			std::index_sequence<tail...>,
			true_tag,
			std::conditional_t<pred<head>::value,none_tag,false_tag>,
			none_tag
		>::value;
};

template<template<std::size_t>class pred,std::size_t head,std::size_t... tail>
struct is_partitioned<false,pred,std::index_sequence<head,tail...>,true_tag,false_tag,none_tag>{
	static constexpr bool value=
		is_partitioned<
			pred<head>::value,
			pred,
			std::index_sequence<tail...>,
			false_tag,
			std::conditional_t<pred<head>::value,true_tag,none_tag>,
			none_tag
		>::value;
};

template<bool b,template<std::size_t>class pred>
struct is_partitioned<b,pred,std::index_sequence<>,true_tag,none_tag,none_tag>:std::true_type{};
template<bool b,template<std::size_t>class pred>
struct is_partitioned<b,pred,std::index_sequence<>,false_tag,none_tag,none_tag>:std::true_type{};

template<bool b,template<std::size_t>class pred>
struct is_partitioned<b,pred,std::index_sequence<>,true_tag,false_tag,none_tag>:std::true_type{};

template<bool b,template<std::size_t>class pred>
struct is_partitioned<b,pred,std::index_sequence<>,false_tag,true_tag,none_tag>:std::true_type{};

template<bool b,template<std::size_t>class pred,std::size_t... seq>
struct is_partitioned<b,pred,std::index_sequence<seq...>,true_tag,false_tag,true_tag>:std::false_type{};

template<bool b,template<std::size_t>class pred,std::size_t... seq>
struct is_partitioned<b,pred,std::index_sequence<seq...>,false_tag,true_tag,false_tag>:std::false_type{};


template<template<std::size_t>class pred,std::size_t head,std::size_t... tail>
struct is_partitioned<false,pred,std::index_sequence<head,tail...>,false_tag,none_tag,none_tag>{
	static constexpr bool value=
		is_partitioned<
			pred<head>::value,
			pred,
			std::index_sequence<tail...>,
			false_tag,
			std::conditional_t<pred<head>::value,true_tag,none_tag>,
			none_tag
		>::value;
};

template<template<std::size_t>class pred,std::size_t head,std::size_t... tail>
struct is_partitioned<true,pred,std::index_sequence<head,tail...>,false_tag,true_tag,none_tag>{
	static constexpr bool value=
		is_partitioned<
			pred<head>::value,
			pred,
			std::index_sequence<tail...>,
			false_tag,
			true_tag,
			std::conditional_t<pred<head>::value,none_tag,false_tag>
		>::value;
};

template<template<std::size_t>class pred,class Seq>
static constexpr bool is_partitioned_v=
	is_partitioned<
		pred<first_v<Seq>>::value,
		pred,
		pop_front_t<Seq>,
		std::conditional_t<pred<first_v<Seq>>::value,true_tag,false_tag>,
		none_tag,
		none_tag
	>::value;


} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
