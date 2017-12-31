// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ERASE_N
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ERASE_N
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class>
struct erase_n;

template<std::size_t target_index,std::size_t head,std::size_t... tail>
struct erase_n<target_index,std::index_sequence<head,tail...>>{
	using type=concat_t<std::index_sequence<head>,typename erase_n<target_index-1,std::index_sequence<tail...>>::type>;
};

template<std::size_t head,std::size_t... tail>
struct erase_n<0,std::index_sequence<head,tail...>>{
	using type=std::index_sequence<tail...>;
};

template<std::size_t target_index>
struct erase_n<target_index,std::index_sequence<>>{
	using type=std::index_sequence<>;
};


template<std::size_t target_index,class Seq>
using erase_n_t=typename erase_n<target_index,Seq>::type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
