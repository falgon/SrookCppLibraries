// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FIND_END_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FIND_END_HPP
#include<srook/mpl/constant_sequence/algorithm/search.hpp>
#include<srook/mpl/constant_sequence/algorithm/reverse.hpp>
namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class Subseq,class Seq>
constexpr int find_end_v=Seq::size()-Subseq::size()-search_v<reverse_t<Subseq>,reverse_t<Seq>>;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook 
#endif
