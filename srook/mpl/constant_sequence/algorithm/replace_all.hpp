// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_REPLACE_ALL_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_REPLACE_ALL_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,std::size_t,class>
struct replace_all;
template<std::size_t target,std::size_t replace_value,std::size_t head,std::size_t... tail>
struct replace_all<target,replace_value,std::index_sequence<head,tail...>>{
	using type=concat_t<std::index_sequence<head>,typename replace_all<target,replace_value,std::index_sequence<tail...>>::type>;
};
template<std::size_t target,std::size_t replace_value,std::size_t... tail>
struct replace_all<target,replace_value,std::index_sequence<target,tail...>>{
	using type=concat_t<std::index_sequence<replace_value>,typename replace_all<target,replace_value,std::index_sequence<tail...>>::type>;
};
template<std::size_t target,std::size_t replace_value>
struct replace_all<target,replace_value,std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<std::size_t target,std::size_t replace_value,class Sequence>
using replace_all_t=typename replace_all<target,replace_value,Sequence>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
