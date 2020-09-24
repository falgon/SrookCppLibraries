// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ERASE_INDEX_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ERASE_INDEX_HPP
#include<srook/mpl/constant_sequence/algorithm/erase_all.hpp>
namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class,class>
struct erase_index;

template<std::size_t head,std::size_t... tail,std::size_t... seq>
struct erase_index<std::index_sequence<head,tail...>,std::index_sequence<seq...>>{
	using type=typename erase_index<std::index_sequence<tail...>,erase_all_t<head,std::index_sequence<seq...>>>::type;
};

template<std::size_t... seq>
struct erase_index<std::index_sequence<>,std::index_sequence<seq...>>{
	using type=std::index_sequence<seq...>;
};

template<class DelSeq,class Seq>
using erase_index_t=typename erase_index<DelSeq,Seq>::type;

} // namespace v1
} // inline namespace constant_sequence
} // namespace mpl
} // namespace srook
#endif
