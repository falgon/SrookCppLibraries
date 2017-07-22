// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_PREV_ROTATE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_PREV_ROTATE_HPP
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct prev_rotate;

template<std::size_t... seq>
struct prev_rotate<std::index_sequence<seq...>>{
	using type=concat_t<pop_front_t<std::index_sequence<seq...>>,std::index_sequence<first_v<std::index_sequence<seq...>>>>;
};

template<class Seq>
using prev_rotate_t=typename prev_rotate<Seq>::type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
