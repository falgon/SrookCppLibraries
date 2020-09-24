// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_MISMATCH_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_MISMATCH_HPP
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

namespace{
	template<std::size_t l,std::size_t r>
	using equal_pred=std::integral_constant<bool,(l==r)>;
}

template<bool,class,class,template<std::size_t,std::size_t>class,std::size_t>
struct mismatch;

template<
	std::size_t head1,std::size_t... tail1,
	std::size_t head2,std::size_t... tail2,
	template<std::size_t,std::size_t>class BinaryPred,
	std::size_t result
>
struct mismatch<true,std::index_sequence<head1,tail1...>,std::index_sequence<head2,tail2...>,BinaryPred,result>{
	static constexpr int value=
		mismatch<BinaryPred<head1,head2>::value,std::index_sequence<tail1...>,std::index_sequence<tail2...>,BinaryPred,result+1>::value;
};

template<std::size_t prev_tail,std::size_t... tail,template<std::size_t,std::size_t>class BinaryPred,std::size_t result>
struct mismatch<true,std::index_sequence<>,std::index_sequence<prev_tail,tail...>,BinaryPred,result>{
	static constexpr int value=result+1;
};

template<std::size_t prev_tail,std::size_t... tail,template<std::size_t,std::size_t>class BinaryPred,std::size_t result>
struct mismatch<true,std::index_sequence<prev_tail,tail...>,std::index_sequence<>,BinaryPred,result>{
	static constexpr int value=result+1;
};

template<template<std::size_t,std::size_t>class BinaryPred,std::size_t result>
struct mismatch<true,std::index_sequence<>,std::index_sequence<>,BinaryPred,result>{
	static constexpr int value=-1;
};

template<std::size_t... seq1,std::size_t... seq2,template<std::size_t,std::size_t>class BinaryPred,std::size_t result>
struct mismatch<false,std::index_sequence<seq1...>,std::index_sequence<seq2...>,BinaryPred,result>{
	static constexpr int value=result;
};

template<class Seq1,class Seq2,template<std::size_t,std::size_t>class BinaryPred=equal_pred>
constexpr int mismatch_v=mismatch<BinaryPred<first_v<Seq1>,first_v<Seq2>>::value,pop_front_t<Seq1>,pop_front_t<Seq2>,BinaryPred,0>::value;

} // inline namespace v1
} // inline namespace constant_sequence
} // inline namespace mpl
} // namespace srook 
#endif
