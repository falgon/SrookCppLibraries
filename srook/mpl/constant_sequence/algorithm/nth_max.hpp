// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_NTH_MAX_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_NTH_MAX_HPP
#include<srook/mpl/constant_sequence/algorithm/minmax.hpp>
#include<srook/mpl/constant_sequence/algorithm/find.hpp>
#include<srook/mpl/constant_sequence/algorithm/erase_n.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class>
struct nth_max;

template<std::size_t n,std::size_t... seq>
struct nth_max<n,std::index_sequence<seq...>>{
	static constexpr std::size_t value=
		nth_max<
			n-1,
			erase_n_t<
				find_v<max_v<std::index_sequence<seq...>>,std::index_sequence<seq...>>,
				std::index_sequence<seq...>
			>
		>::value;
};

template<std::size_t... seq>
struct nth_max<1,std::index_sequence<seq...>>{
	static constexpr std::size_t value=max_v<std::index_sequence<seq...>>;
};

template<std::size_t n,class Seq>
constexpr std::size_t nth_max_v=nth_max<n,Seq>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
