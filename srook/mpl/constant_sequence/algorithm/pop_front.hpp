// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_POP_FRONT_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_POP_FRONT_HPP
#include<type_traits>
#include<utility>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct pop_front;
template<std::size_t head,std::size_t... tail>
struct pop_front<std::index_sequence<head,tail...>>{
	using type=std::index_sequence<tail...>;
};
template<class Sequence>
using pop_front_t=typename pop_front<Sequence>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
