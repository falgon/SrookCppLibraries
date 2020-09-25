// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_PARTIAL_HEAD_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_PARTIAL_HEAD_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class>
struct partial_head;
template<std::size_t target,std::size_t head,std::size_t... tail>
struct partial_head<target,std::index_sequence<head,tail...>>{
	using type=concat_t<std::index_sequence<head>,typename partial_head<target-1,std::index_sequence<tail...>>::type>;
};
template<std::size_t tail,std::size_t... args>
struct partial_head<1,std::index_sequence<tail,args...>>{
	using type=std::index_sequence<tail>;
};

template<std::size_t target,class Sequence>
using partial_head_t=typename partial_head<target,Sequence>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
