// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ITER_SWAP_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ITER_SWAP_HPP
#include<srook/mpl/constant_sequence/iterator/index_sequence_iterator.hpp>
#include<srook/mpl/constant_sequence/algorithm/at.hpp>
#include<srook/mpl/constant_sequence/algorithm/insert.hpp>
#include<srook/mpl/constant_sequence/algorithm/erase_n.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class,class>
struct iter_swap;

template<class Seq1,class Seq2>
struct iter_swap<
	index_sequence_iterator::index_sequence_iterator<Seq1>,
	index_sequence_iterator::index_sequence_iterator<Seq2>
>{
	using L_type=
		erase_n_t<
			index_sequence_iterator::index_sequence_iterator<Seq1>::index+1,
			insert_t<
				std::index_sequence<
					at_v<
						index_sequence_iterator::index_sequence_iterator<Seq2>::index,
						typename index_sequence_iterator::index_sequence_iterator<Seq2>::type
					>
				>,
				index_sequence_iterator::index_sequence_iterator<Seq1>::index,
				typename index_sequence_iterator::index_sequence_iterator<Seq1>::type
			>
		>;
	using R_type=
		erase_n_t<
			index_sequence_iterator::index_sequence_iterator<Seq2>::index+1,
			insert_t<
				std::index_sequence<
					at_v<
						index_sequence_iterator::index_sequence_iterator<Seq1>::index,
						typename index_sequence_iterator::index_sequence_iterator<Seq1>::type
					>
				>,
				index_sequence_iterator::index_sequence_iterator<Seq2>::index,
				typename index_sequence_iterator::index_sequence_iterator<Seq2>::type
			>
		>;
};

template<class Seq1,class Seq2>
struct iter_swap<index_sequence_iterator::increment<Seq1>,index_sequence_iterator::increment<Seq2>>{
	using L_type=
		erase_n_t<
			index_sequence_iterator::increment<Seq1>::index+1,
			insert_t<
				std::index_sequence<
					at_v<
						index_sequence_iterator::increment<Seq2>::index,
						typename index_sequence_iterator::increment<Seq2>::type
					>
				>,
				index_sequence_iterator::increment<Seq1>::index,
				typename index_sequence_iterator::increment<Seq1>::type
			>
		>;
	using R_type=
		erase_n_t<
			index_sequence_iterator::increment<Seq2>::index+1,
			insert_t<
				std::index_sequence<
					at_v<
						index_sequence_iterator::increment<Seq1>::index,
						typename index_sequence_iterator::increment<Seq1>::type
					>
				>,
				index_sequence_iterator::increment<Seq2>::index,
				typename index_sequence_iterator::increment<Seq2>::type
			>
		>;
};

template<class Seq1,class Seq2>
struct iter_swap<index_sequence_iterator::increment<Seq1>,index_sequence_iterator::decrement<Seq2>>{
	using L_type=
		erase_n_t<
			index_sequence_iterator::increment<Seq1>::index+1,
			insert_t<
				std::index_sequence<
					at_v<
						index_sequence_iterator::decrement<Seq2>::index,
						typename index_sequence_iterator::decrement<Seq2>::type
					>
				>,
				index_sequence_iterator::increment<Seq1>::index,
				typename index_sequence_iterator::increment<Seq1>::type
			>
		>;
	using R_type=
		erase_n_t<
			index_sequence_iterator::decrement<Seq2>::index+1,
			insert_t<
				std::index_sequence<
					at_v<
						index_sequence_iterator::increment<Seq1>::index,
						typename index_sequence_iterator::increment<Seq1>::type
					>
				>,
				index_sequence_iterator::decrement<Seq2>::index,
				typename index_sequence_iterator::decrement<Seq2>::type
			>
		>;
};

template<class Seq1,class Seq2>
struct iter_swap<index_sequence_iterator::decrement<Seq1>,index_sequence_iterator::increment<Seq2>>{
	using L_type=
		typename iter_swap<index_sequence_iterator::increment<Seq2>,index_sequence_iterator::decrement<Seq1>>::R_type;
	using R_type=
		typename iter_swap<index_sequence_iterator::increment<Seq2>,index_sequence_iterator::decrement<Seq1>>::L_type;
};

template<class Seq1,class Seq2>
struct iter_swap<index_sequence_iterator::decrement<Seq1>,index_sequence_iterator::decrement<Seq2>>{
	using L_type=
		erase_n_t<
			index_sequence_iterator::decrement<Seq1>::index+1,
			insert_t<
				std::index_sequence<
					at_v<
						index_sequence_iterator::decrement<Seq2>::index,
						typename index_sequence_iterator::decrement<Seq2>::type
					>
				>,
				index_sequence_iterator::decrement<Seq1>::index,
				typename index_sequence_iterator::decrement<Seq1>::type
			>
		>;
	using R_type=
		erase_n_t<
			index_sequence_iterator::decrement<Seq2>::index+1,
			insert_t<
				std::index_sequence<
					at_v<
						index_sequence_iterator::decrement<Seq1>::index,
						typename index_sequence_iterator::decrement<Seq1>::type
					>
				>,
				index_sequence_iterator::decrement<Seq2>::index,
				typename index_sequence_iterator::decrement<Seq2>::type
			>
		>;
};

template<class Seq_iter1,class Seq_iter2>
using iter_swap_L=typename iter_swap<Seq_iter1,Seq_iter2>::L_type;

template<class Seq_iter1,class Seq_iter2>
using iter_swap_R=typename iter_swap<Seq_iter1,Seq_iter2>::R_type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook

#endif
