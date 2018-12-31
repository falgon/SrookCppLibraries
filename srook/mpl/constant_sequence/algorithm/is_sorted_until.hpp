// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_IS_SORTED_UNTIL_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_IS_SORTED_UNTIL_HPP
#include<srook/mpl/constant_sequence/algorithm/sort.hpp>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<bool,class,template<std::size_t,std::size_t>class,std::size_t>
struct is_sorted_until;

template<std::size_t head,std::size_t head_next,std::size_t... tail,template<std::size_t,std::size_t>class comp,std::size_t counter>
struct is_sorted_until<true,std::index_sequence<head,head_next,tail...>,comp,counter>{
	static constexpr int value=
		is_sorted_until<comp<head,head_next>::value,std::index_sequence<head_next,tail...>,comp,counter+1>::value;
};

template<std::size_t last1,std::size_t last2,template<std::size_t,std::size_t>class comp,std::size_t counter>
struct is_sorted_until<true,std::index_sequence<last1,last2>,comp,counter>{
	static constexpr int value=comp<last1,last2>::value?-1:counter+1;
};

template<std::size_t... seq,template<std::size_t,std::size_t>class comp,std::size_t counter>
struct is_sorted_until<false,std::index_sequence<seq...>,comp,counter>{
	static constexpr int value=counter;
};

template<class Sequence,template<std::size_t,std::size_t>class comp=less>
constexpr int is_sorted_until_v=
	is_sorted_until<comp<first_v<Sequence>,first_v<pop_front_t<Sequence>>>::value,pop_front_t<Sequence>,comp,1>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
