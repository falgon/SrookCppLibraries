// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_LAST_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_LAST_HPP
#include<type_traits>
#include<utility>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct last;

template<std::size_t head,std::size_t... tail>
struct last<std::index_sequence<head,tail...>>{
	static constexpr std::size_t value=last<std::index_sequence<tail...>>::value;
};

template<std::size_t tail>
struct last<std::index_sequence<tail>>{
	static constexpr std::size_t value=tail;
};

template<class Seq>
static constexpr std::size_t last_v=last<Seq>::value;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
