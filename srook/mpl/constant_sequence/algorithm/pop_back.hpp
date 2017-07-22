// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_POP_BACK_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_POP_BACK_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct pop_back;
template<std::size_t head,std::size_t... tail>
struct pop_back<std::index_sequence<head,tail...>>{
	using type=concat_t<std::index_sequence<head>,typename pop_back<std::index_sequence<tail...>>::type>;
};
template<std::size_t tail>
struct pop_back<std::index_sequence<tail>>{
	using type=std::index_sequence<>;
};
template<class Sequence>
using pop_back_t=typename pop_back<Sequence>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
