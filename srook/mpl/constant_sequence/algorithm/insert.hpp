// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_INSERT_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_INSERT_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class,std::size_t,class,bool>
struct insert;
template<std::size_t... seq,std::size_t index,std::size_t head,std::size_t... tail>
struct insert<std::index_sequence<seq...>,index,std::index_sequence<head,tail...>,true>{
	using type=concat_t<std::index_sequence<head>,typename insert<std::index_sequence<seq...>,index-1,std::index_sequence<tail...>,static_cast<bool>(index-1)>::type>;
};
template<std::size_t... seq1,std::size_t... seq2>
struct insert<std::index_sequence<seq1...>,0,std::index_sequence<seq2...>,false>{
	using type=std::index_sequence<seq1...,seq2...>;
};
template<class Sequence1,std::size_t index,class Sequence2>
using insert_t=typename insert<Sequence1,index,Sequence2,static_cast<bool>(index)>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
