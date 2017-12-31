// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_FIND_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_FIND_HPP
#include<type_traits>
#include<utility>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

// find
template<std::size_t,class>
struct find;
template<std::size_t target,std::size_t head,std::size_t... tail>
struct find<target,std::index_sequence<head,tail...>>{
	static constexpr int value=
		find<target,std::index_sequence<tail...>>::value==-1?
			find<target,std::index_sequence<tail...>>::value:
			1+find<target,std::index_sequence<tail...>>::value;
};
template<std::size_t head,std::size_t... tail>
struct find<head,std::index_sequence<head,tail...>>{
	static constexpr int value=0;
};
template<std::size_t target>
struct find<target,std::index_sequence<>>{
	static constexpr int value=-1;
};
template<std::size_t index,class Sequence>
constexpr int find_v=find<index,Sequence>::value;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
