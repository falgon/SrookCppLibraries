// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_SET_INTERSECTION_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_SET_INTERSECTION_HPP
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>
#include<srook/mpl/constant_sequence/algorithm/binary_search.hpp>
#include<srook/mpl/constant_sequence/algorithm/erase_duplicate.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

namespace{
template<class,class,class,class>
struct set_intersection;

template<class,class>
struct set_inter;

template<std::size_t l,std::size_t r>
struct set_inter<std::index_sequence<l>,std::index_sequence<r>>{
	using type=std::conditional_t<(l==r),std::index_sequence<l>,std::index_sequence<(l<r)?l:r,(l<r)?r:l>>;
};

template<std::size_t l>
struct set_inter<std::index_sequence<l>,std::index_sequence<>>{
	using type=std::index_sequence<l>;
};

template<std::size_t r>
struct set_inter<std::index_sequence<>,std::index_sequence<r>>:set_inter<std::index_sequence<r>,std::index_sequence<>>{};

template<>
struct set_inter<std::index_sequence<>,std::index_sequence<>>{
	using type=std::index_sequence<>;
};

template<class L,class R>
using set_inter_t=typename set_inter<L,R>::type;
}

template<std::size_t head1,std::size_t... tail1,std::size_t head2,std::size_t... tail2,std::size_t... seq1,std::size_t... seq2>
struct set_intersection<
	std::index_sequence<head1,tail1...>,std::index_sequence<head2,tail2...>,
	std::index_sequence<seq1...>,std::index_sequence<seq2...>
>{
	using type=
		erase_duplicate_t<
			concat_t<
				set_inter_t<
					std::conditional_t<binary_search_v<head1,std::index_sequence<seq2...>>,std::index_sequence<head1>,std::index_sequence<>>,
					std::conditional_t<binary_search_v<head2,std::index_sequence<seq1...>>,std::index_sequence<head2>,std::index_sequence<>>
				>,
				typename set_intersection<
					std::index_sequence<tail1...>,std::index_sequence<tail2...>,std::index_sequence<seq1...>,std::index_sequence<seq2...>
				>::type
			>
		>;
};

template<std::size_t head,std::size_t... tail,std::size_t...seq1,std::size_t... seq2>
struct set_intersection<
	std::index_sequence<>,std::index_sequence<head,tail...>,
	std::index_sequence<seq1...>,std::index_sequence<seq2...>
>{
	using type=
		concat_t<
			std::conditional_t<binary_search_v<head,std::index_sequence<seq1...>>,std::index_sequence<head>,std::index_sequence<>>,
			typename set_intersection<
				std::index_sequence<>,std::index_sequence<tail...>,std::index_sequence<seq1...>,std::index_sequence<seq2...>
			>::type
		>;
};


template<std::size_t head,std::size_t... tail,std::size_t... seq1,std::size_t... seq2>
struct set_intersection<
	std::index_sequence<head,tail...>,
	std::index_sequence<>,
	std::index_sequence<seq1...>,
	std::index_sequence<seq2...>
>:set_intersection<std::index_sequence<>,std::index_sequence<head,tail...>,std::index_sequence<seq2...>,std::index_sequence<seq1...>>{};


template<std::size_t... seq1,std::size_t... seq2>
struct set_intersection<std::index_sequence<>,std::index_sequence<>,std::index_sequence<seq1...>,std::index_sequence<seq2...>>{
	using type=std::index_sequence<>;
};

template<class Seq1,class Seq2>
using set_intersection_t=typename set_intersection<Seq1,Seq2,Seq1,Seq2>::type;


} // inline namespace v1
} // namespace constant_sequence 
} // inline namespace mpl
} // namespace srook 
#endif
