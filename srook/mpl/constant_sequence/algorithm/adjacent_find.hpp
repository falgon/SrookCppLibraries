// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ADJACENT_FIND_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ADJACENT_FIND_HPP
#include<utility>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct adjacent_find;

template<std::size_t head,std::size_t second,std::size_t... tail>
struct adjacent_find<std::index_sequence<head,second,tail...>>{
	static constexpr int value=adjacent_find<std::index_sequence<second,tail...>>::value;
};

template<std::size_t head,std::size_t... tail>
struct adjacent_find<std::index_sequence<head,head,tail...>>{
	static constexpr int value=head;
};

template<>
struct adjacent_find<std::index_sequence<>>{
	static constexpr int value=-1;
};

template<class Sequence>
constexpr std::size_t adjacent_find_v=adjacent_find<Sequence>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
