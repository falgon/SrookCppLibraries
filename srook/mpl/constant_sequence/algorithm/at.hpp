// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_AT_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_AT_HPP
#include<type_traits>
#include<utility>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class>
struct at;
template<std::size_t index,std::size_t head,std::size_t... tail>
struct at<index,std::index_sequence<head,tail...>>{
	static constexpr std::size_t value=at<index-1,std::index_sequence<tail...>>::value;
};
template<std::size_t head,std::size_t... tail>
struct at<0,std::index_sequence<head,tail...>>{
	static constexpr std::size_t value=head;
};
template<std::size_t index,class Sequence>
static constexpr std::size_t at_v=at<index,Sequence>::value;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
