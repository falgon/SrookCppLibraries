// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_SUMMATION_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_SUMMATION_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class,std::size_t>
struct summation;
template<std::size_t... seq,std::size_t n>
struct summation<std::index_sequence<seq...>,n>{
	static constexpr std::size_t value=
		((2*first_v<std::index_sequence<seq...>>)+
		((n-1)*(first_v<pop_front_t<std::index_sequence<seq...>>>-first_v<std::index_sequence<seq...>>)*n))/2;
};
template<class Sequence,std::size_t n=Sequence::size()>
constexpr std::size_t summation_v=summation<Sequence,n>::value;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
