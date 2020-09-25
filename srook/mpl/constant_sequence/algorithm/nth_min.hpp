// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_NTH_MIN_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_NTH_MIN_HPP
#include<srook/mpl/constant_sequence/algorithm/minmax.hpp>
#include<srook/mpl/constant_sequence/algorithm/find.hpp>
#include<srook/mpl/constant_sequence/algorithm/erase_n.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class>
struct nth_min;

template<std::size_t n,std::size_t... seq>
struct nth_min<n,std::index_sequence<seq...>>{
	static constexpr std::size_t value=
		nth_min<
			n-1,
			erase_n_t<
				find_v<min_v<std::index_sequence<seq...>>,std::index_sequence<seq...>>,
				std::index_sequence<seq...>
			>
		>::value;
};

template<std::size_t... seq>
struct nth_min<1,std::index_sequence<seq...>>{
	static constexpr std::size_t value=min_v<std::index_sequence<seq...>>;
};

template<std::size_t n,class Seq>
constexpr std::size_t nth_min_v=nth_min<n,Seq>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
