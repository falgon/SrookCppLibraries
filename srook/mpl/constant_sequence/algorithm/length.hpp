// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_LENGTH_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_LENGTH_HPP
#include<type_traits>
#include<utility>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct length;

template<std::size_t... v>
struct length<std::index_sequence<v...>>{
	static constexpr std::size_t value=std::index_sequence<v...>::size();
};

template<class Seq>
constexpr std::size_t length_v=length<Seq>::value;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
