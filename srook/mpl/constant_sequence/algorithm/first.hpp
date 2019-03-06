// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_FIRST_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_FIRST_HPP
#include<type_traits>
#include<utility>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct first;

template<std::size_t head,std::size_t... tail>
struct first<std::index_sequence<head,tail...>>{
	static constexpr std::size_t value=head;
};

template<class Seq>
static constexpr std::size_t first_v=first<Seq>::value;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
