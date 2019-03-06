// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_REVERSE_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_REVERSE_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_back.hpp>
#include<srook/mpl/constant_sequence/algorithm/last.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct reverse;
template<std::size_t... seq>
struct reverse<std::index_sequence<seq...>>{
	using type=
		concat_t<
			std::index_sequence<last_v<std::index_sequence<seq...>>>,
			typename reverse<pop_back_t<std::index_sequence<seq...>>>::type
		>;
};
template<>
struct reverse<std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<class Sequence>
using reverse_t=typename reverse<Sequence>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
