// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_CONCAT_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_CONCAT_HPP
#include<type_traits>
#include<utility>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class,class>
struct concat;
template<std::size_t... l,std::size_t... r>
struct concat<std::index_sequence<l...>,std::index_sequence<r...>>{
	using type=std::index_sequence<l...,r...>;
};

template<class L,class R>
using concat_t=typename concat<L,R>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
