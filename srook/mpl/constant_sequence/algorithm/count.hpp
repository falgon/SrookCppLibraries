// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_COUNT_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_COUNT_HPP
#include<utility>
#include<type_traits>
#include<srook/mpl/constant_sequence/algorithm/filter.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class>
struct count;

template<std::size_t target,std::size_t... seq>
struct count<target,std::index_sequence<seq...>>{
private:
	template<std::size_t head>
	using equal_binder=std::integral_constant<bool,(head==target)>;
public:
	static constexpr std::size_t value=filter_t<equal_binder,std::index_sequence<seq...>>::size();
};


template<std::size_t target,class Sequence>
constexpr std::size_t count_v=count<target,Sequence>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook

#endif
