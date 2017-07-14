// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_SWAP_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_SWAP_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class,class>
struct swap;
template<std::size_t target,std::size_t head1,std::size_t... tail1,std::size_t head2,std::size_t... tail2>
struct swap<target,std::index_sequence<head1,tail1...>,std::index_sequence<head2,tail2...>>{
	using L_type=
		concat_t<std::index_sequence<head1>,typename swap<target-1,std::index_sequence<tail1...>,std::index_sequence<tail2...>>::L_type>;
	using R_type=
		concat_t<std::index_sequence<head2>,typename swap<target-1,std::index_sequence<tail1...>,std::index_sequence<tail2...>>::R_type>;
};
template<std::size_t head1,std::size_t... tail1,std::size_t head2,std::size_t... tail2>
struct swap<0,std::index_sequence<head1,tail1...>,std::index_sequence<head2,tail2...>>{
	using L_type=concat_t<std::index_sequence<head2>,std::index_sequence<tail1...>>;
	using R_type=concat_t<std::index_sequence<head1>,std::index_sequence<tail2...>>;
};
template<std::size_t target,class Seq1,class Seq2>
using swap_L=typename swap<target,Seq1,Seq2>::L_type;
template<std::size_t target,class Seq1,class Seq2>
using swap_R=typename swap<target,Seq1,Seq2>::R_type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
