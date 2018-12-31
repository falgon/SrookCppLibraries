// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_EQUAL_RANGE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_EQUAL_RANGE_HPP
#include<srook/mpl/constant_sequence/algorithm/bound.hpp>
namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class>
struct equal_range;

template<std::size_t target,std::size_t... seq>
struct equal_range<target,std::index_sequence<seq...>>{
	static constexpr std::pair<int,int> value{lower_bound_v<target,std::index_sequence<seq...>>,upper_bound_v<target,std::index_sequence<seq...>>};
};

template<std::size_t target,class Seq>
constexpr std::pair<int,int> equal_range_v=equal_range<target,Seq>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
