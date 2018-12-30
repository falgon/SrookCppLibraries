// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ADJACENT_FIND_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ADJACENT_FIND_HPP
#include<utility>
#include<srook/config/compiler.hpp>
#include<srook/utility/integer_sequence.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct adjacent_find;

template<class T,T head,T second,T... tail>
struct adjacent_find<srook::integer_sequence<T,head,second,tail...>>{
	static constexpr int value = adjacent_find<srook::integer_sequence<T,second,tail...>>::value;
	constexpr operator int(){return value;}
};

template<class T,T head,T... tail>
struct adjacent_find<srook::integer_sequence<T,head,head,tail...>>{
	static constexpr int value = head;
};

template<class T>
struct adjacent_find<srook::integer_sequence<T>>{
	static constexpr int value = -1;
};

#ifndef SROOK_IS_CXX11_EARLIER
template<class T,T head,T second,T... tail>
struct adjacent_find<std::integer_sequence<T,head,second,tail...>>{
	static constexpr int value = adjacent_find<std::integer_sequence<T,second,tail...>>::value;
	constexpr operator int()const{return value;}
};

template<class T,T head,T... tail>
struct adjacent_find<std::integer_sequence<T,head,head,tail...>>{
	static constexpr int value = head;
};

template<class T>
struct adjacent_find<std::integer_sequence<T>>{
	static constexpr int value = -1;
};

template<class Sequence>
constexpr int adjacent_find_v = adjacent_find<Sequence>::value;
#endif

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
