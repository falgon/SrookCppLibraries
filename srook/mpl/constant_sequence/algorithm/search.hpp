// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_SEARCH_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_SEARCH_HPP
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class,class,class,int>
struct search;

template<std::size_t subseq_head,std::size_t... subseq_tail,std::size_t head,std::size_t... tail,std::size_t... subseq,int counter>
struct search<
	std::index_sequence<subseq_head,subseq_tail...>,
	std::index_sequence<head,tail...>,
	std::index_sequence<subseq...>,
	counter
>{
	static constexpr int value=
		search<
			std::conditional_t<
				(subseq_head==head),
				std::index_sequence<subseq_tail...>,
				std::index_sequence<subseq...>
			>,
			std::index_sequence<tail...>,
			std::index_sequence<subseq...>,
			counter+1
		>::value;
};

template<std::size_t seq,std::size_t... seqtail,std::size_t... subseq,int counter>
struct search<
	std::index_sequence<>,
	std::index_sequence<seq,seqtail...>,
	std::index_sequence<subseq...>,
	counter
>{
	static constexpr int value=counter-(std::index_sequence<subseq...>::size()-1);
};

template<std::size_t subseqs,std::size_t... subseqstail,std::size_t... subseq,int counter>
struct search<
	std::index_sequence<subseqs,subseqstail...>,
	std::index_sequence<>,
	std::index_sequence<subseq...>,
	counter
>{
	static constexpr int value=-1;
};

template<std::size_t... subseq,int counter>
struct search<
	std::index_sequence<>,
	std::index_sequence<>,
	std::index_sequence<subseq...>,
	counter
>{
	static constexpr int value=counter-(std::index_sequence<subseq...>::size()-1);
};


template<class SubSeq,class Seq>
constexpr int search_v=
	search<
		std::conditional_t<(first_v<SubSeq> ==first_v<Seq>),pop_front_t<SubSeq>,SubSeq>,
		pop_front_t<Seq>,
		SubSeq,
		0
	>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
