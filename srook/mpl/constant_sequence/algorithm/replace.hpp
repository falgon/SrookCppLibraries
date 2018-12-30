// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_REPLACE_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_REPLACE_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,std::size_t,class>
struct replace;
template<std::size_t target,std::size_t replace_value,std::size_t head,std::size_t... tail>
struct replace<target,replace_value,std::index_sequence<head,tail...>>{
	using type=concat_t<std::index_sequence<head>,typename replace<target,replace_value,std::index_sequence<tail...>>::type>;
};
template<std::size_t target,std::size_t replace_value,std::size_t... tail>
struct replace<target,replace_value,std::index_sequence<target,tail...>>{
	using type=concat_t<std::index_sequence<replace_value>,std::index_sequence<tail...>>;
};
template<std::size_t target,std::size_t replace_value>
struct replace<target,replace_value,std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<std::size_t target,std::size_t replace_value,class Seq>
using replace_t=typename replace<target,replace_value,Seq>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
