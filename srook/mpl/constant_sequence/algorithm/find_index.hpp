// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FIND_INDEX_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FIND_INDEX_HPP
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class,std::size_t>
struct find_index;

template<std::size_t target,std::size_t head,std::size_t... tail,std::size_t counter>
struct find_index<target,std::index_sequence<head,tail...>,counter>{
	using type=
		concat_t<
			std::conditional_t<
				(target==head),
				std::index_sequence<counter>,
				std::index_sequence<>
			>,
			typename find_index<target,std::index_sequence<tail...>,counter+1>::type
		>;
};

template<std::size_t target,std::size_t counter>
struct find_index<target,std::index_sequence<>,counter>{
	using type=std::index_sequence<>;
};

template<std::size_t target,class Seq>
using find_index_t=typename find_index<target,Seq,0>::type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
