// Copyright (C) 2017 Roki
#ifndef INCULDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_EQUAL_HPP
#define INCULDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_EQUAL_HPP
#include<utility>
#include<type_traits>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class,class,bool>
struct equal;

template<std::size_t head1,std::size_t... tail1,std::size_t head2,std::size_t... tail2>
struct equal<std::index_sequence<head1,tail1...>,std::index_sequence<head2,tail2...>,true>{
	static constexpr bool value=equal<std::index_sequence<tail1...>,std::index_sequence<tail2...>,head1==head2>::value;
};

template<>
struct equal<std::index_sequence<>,std::index_sequence<>,true>:std::true_type{};

template<std::size_t... seq1,std::size_t... seq2>
struct equal<std::index_sequence<seq1...>,std::index_sequence<seq2...>,false>:std::false_type{};
	

template<class Seq1,class Seq2>
constexpr bool equal_v=equal<Seq1,Seq2,Seq1::size()==Seq2::size()>::value;

} // inline namespace v1
} // namesapce constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
