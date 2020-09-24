// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_ERASE_ALL_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_ERASE_ALL_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class>
struct erase_all;
template<std::size_t target,std::size_t head,std::size_t... tail>
struct erase_all<target,std::index_sequence<head,tail...>>{
	using type=concat_t<std::index_sequence<head>,typename erase_all<target,std::index_sequence<tail...>>::type>;
};
template<std::size_t target,std::size_t... pack>
struct erase_all<target,std::index_sequence<target,pack...>>{
	using type=typename erase_all<target,std::index_sequence<pack...>>::type;
};
template<std::size_t target>
struct erase_all<target,std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<std::size_t target,class Sequence=std::index_sequence<>>
using erase_all_t=typename erase_all<target,Sequence>::type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook 

#endif
