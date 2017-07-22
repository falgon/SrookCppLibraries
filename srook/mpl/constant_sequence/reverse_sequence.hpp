// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_REVERSE_SEQUENCE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_REVERSE_SEQUENCE_HPP

#include<utility>

namespace srook{

namespace detail{

template<std::size_t,class>
struct make_reverse_sequence_impl;

template<std::size_t n,std::size_t... v>
struct make_reverse_sequence_impl<n,std::index_sequence<v...>>{
	using type=typename make_reverse_sequence_impl<n-1,std::index_sequence<v...,n-1>>::type;
};

template<std::size_t... v>
struct make_reverse_sequence_impl<0,std::index_sequence<v...>>{
	using type=std::index_sequence<v...>;
};


} // namespace detail


template<std::size_t n,class Seq=std::index_sequence<>>
using make_reverse_sequence=typename detail::make_reverse_sequence_impl<n,Seq>::type;

} // namespace srook

#endif
