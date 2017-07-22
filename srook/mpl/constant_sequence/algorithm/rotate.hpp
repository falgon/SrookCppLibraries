// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ROTATE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_ROTATE_HPP
#include<srook/mpl/constant_sequence/algorithm/pop_back.hpp>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>
#include<srook/mpl/constant_sequence/algorithm/last.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct rotate;

template<std::size_t... seq>
struct rotate<std::index_sequence<seq...>>{
	using type=concat_t<std::index_sequence<last_v<std::index_sequence<seq...>>>,pop_back_t<std::index_sequence<seq...>>>;
};

template<class Seq>
using rotate_t=typename rotate<Seq>::type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
