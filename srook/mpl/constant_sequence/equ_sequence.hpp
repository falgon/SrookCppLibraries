#ifndef INCLUDED_SROOK_MPL_CONSTANT_EQU_DOUBLE_SEQUENCE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_EQU_DOUBLE_SEQUENCE_HPP
#include<utility>
#include<type_traits>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>
#include<srook/mpl/constant_sequence/samevalue_sequence.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class>
struct make_equ_sequence_impl;

template<std::size_t n,std::size_t... seq>
struct make_equ_sequence_impl<n,std::index_sequence<seq...>>{
	using type=concat_t<typename make_equ_sequence_impl<n-1,std::index_sequence<seq...>>::type,make_samevalue_sequence<n,n>>;
};

template<std::size_t... seq>
struct make_equ_sequence_impl<0,std::index_sequence<seq...>>{
	using type=std::index_sequence<0,seq...>;
};

template<std::size_t n,class Seq=std::index_sequence<>>
using make_equ_sequence=typename make_equ_sequence_impl<n,Seq>::type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook

#endif
