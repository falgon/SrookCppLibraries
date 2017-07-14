// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_SAMEVALUE_SEQUENCE
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_SAMEVALUE_SEQUENCE
#include<utility>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,std::size_t,class>
struct make_samevalue_sequence_impl;

template<std::size_t size,std::size_t fill_value,std::size_t... seq>
struct make_samevalue_sequence_impl<size,fill_value,std::index_sequence<seq...>>{
	using type=typename make_samevalue_sequence_impl<size-1,fill_value,std::index_sequence<fill_value,seq...>>::type;
};

template<std::size_t fill_value,std::size_t... seq>
struct make_samevalue_sequence_impl<0,fill_value,std::index_sequence<seq...>>{
	using type=std::index_sequence<seq...>;
};

template<std::size_t size,std::size_t fill_value,class Sequence=std::index_sequence<>>
using make_samevalue_sequence=typename make_samevalue_sequence_impl<size,fill_value,Sequence>::type;

} // inline namespace v1
} // constant_sequence
} // inline namespace mpl 
} // namespace srook
#endif
