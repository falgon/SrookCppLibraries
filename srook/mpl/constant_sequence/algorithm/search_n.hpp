// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_SEARCH_N_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_SEARCH_N_HPP
#include<srook/mpl/constant_sequence/algorithm/search.hpp>
#include<srook/mpl/constant_sequence/samevalue_sequence.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class Seq,std::size_t size,std::size_t target>
constexpr int search_n_v=search_v<make_samevalue_sequence<size,target>,Seq>;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
