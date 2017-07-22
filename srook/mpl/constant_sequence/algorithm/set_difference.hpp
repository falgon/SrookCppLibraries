// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_SET_DIFFERENCE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_SET_DIFFERENCE_HPP
#include<srook/mpl/constant_sequence/algorithm/binary_search.hpp>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{
namespace{

template<class,class>
struct set_diff;
template<std::size_t l,std::size_t r>
struct set_diff<std::index_sequence<l>,std::index_sequence<r>>{
	using type=std::index_sequence<(l<r)?l:r,(l<r)?r:l>;
};
template<std::size_t l>
struct set_diff<std::index_sequence<l>,std::index_sequence<>>{
	using type=std::index_sequence<l>;
};
template<std::size_t r>
struct set_diff<std::index_sequence<>,std::index_sequence<r>>:set_diff<std::index_sequence<r>,std::index_sequence<>>{};

template<>
struct set_diff<std::index_sequence<>,std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<class L,class R>
using set_diff_t=typename set_diff<L,R>::type;
}

template<class,class,class,class>
struct set_difference;

template<std::size_t head1,std::size_t... tail1,std::size_t head2,std::size_t... tail2,std::size_t... seq1,std::size_t... seq2>
struct set_difference<
	std::index_sequence<head1,tail1...>,std::index_sequence<head2,tail2...>,
	std::index_sequence<seq1...>,std::index_sequence<seq2...>
>{
	using type=
		concat_t<
			set_diff_t<
				std::conditional_t<binary_search_v<head1,std::index_sequence<seq2...>>,std::index_sequence<>,std::index_sequence<head1>>,
				std::conditional_t<binary_search_v<head2,std::index_sequence<seq1...>>,std::index_sequence<>,std::index_sequence<head2>>
			>,
			typename set_difference<
					std::index_sequence<tail1...>,std::index_sequence<tail2...>,std::index_sequence<seq1...>,std::index_sequence<seq2...>
			>::type
		>;
};

template<std::size_t head,std::size_t... tail,std::size_t...seq1,std::size_t... seq2>
struct set_difference<
	std::index_sequence<>,std::index_sequence<head,tail...>,
	std::index_sequence<seq1...>,std::index_sequence<seq2...>
>{
	using type=
		concat_t<
			std::conditional_t<binary_search_v<head,std::index_sequence<seq1...>>,std::index_sequence<>,std::index_sequence<head>>,
			typename set_difference<
				std::index_sequence<>,std::index_sequence<tail...>,std::index_sequence<seq1...>,std::index_sequence<seq2...>
			>::type
		>;
};


template<std::size_t head,std::size_t... tail,std::size_t... seq1,std::size_t... seq2>
struct set_difference<
	std::index_sequence<head,tail...>,
	std::index_sequence<>,
	std::index_sequence<seq1...>,
	std::index_sequence<seq2...>
>:set_difference<std::index_sequence<>,std::index_sequence<head,tail...>,std::index_sequence<seq2...>,std::index_sequence<seq1...>>{};


template<std::size_t... seq1,std::size_t... seq2>
struct set_difference<std::index_sequence<>,std::index_sequence<>,std::index_sequence<seq1...>,std::index_sequence<seq2...>>{
	using type=std::index_sequence<>;
};

template<class Seq1,class Seq2>
using set_difference_t=typename set_difference<Seq1,Seq2,Seq1,Seq2>::type;


} // inline namespace v1
} // namespace constant_sequence 
} // inline namespace mpl
} // namespace srook 
#endif
