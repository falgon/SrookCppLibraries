// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_TRANSFER_ARRAY_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_TRANSFER_ARRAY_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<array>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct transfer_array;

template<std::size_t... seq>
struct transfer_array<std::index_sequence<seq...>>{
	static std::array<decltype(first_v<std::index_sequence<seq...>>),std::index_sequence<seq...>::size()> value;
};

template<std::size_t... seq>
std::array<decltype(first_v<std::index_sequence<seq...>>),std::index_sequence<seq...>::size()>
transfer_array<std::index_sequence<seq...>>::value={{seq...}};

template<class Seq>
std::array<decltype(first_v<Seq>),Seq::size()> transfer_array_v=transfer_array<Seq>::value;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
