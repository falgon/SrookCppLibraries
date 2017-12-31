// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_AT_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_AT_HPP
#include<type_traits>
#include<utility>
#include<srook/config/compiler.hpp>
#include<srook/utility/integer_sequence.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class,std::size_t,class>
struct at;

template<class T,std::size_t index,T head,T... tail>
struct at<T,index,srook::integer_sequence<T,head,tail...>>{
	static constexpr T value = at<T,index-1,srook::integer_sequence<T,tail...>>::value;
};
template<class T,T head,T... tail>
struct at<T,0,srook::integer_sequence<T,head,tail...>>{
	static constexpr T value = head;
};

#ifndef SROOK_IS_CXX11_EARLIER

template<class T,std::size_t index,T head,T... tail>
struct at<T,index,std::integer_sequence<T,head,tail...>>{
	static constexpr T value = at<T,index-1,std::integer_sequence<T,tail...>>::value;
};
template<class T,T head,T... tail>
struct at<T,0,std::integer_sequence<T,head,tail...>>{
	static constexpr T value = head;
};
template<std::size_t index,class Sequence,class T = std::size_t>
static constexpr T at_v = at<T,index,Sequence>::value;

#endif

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
