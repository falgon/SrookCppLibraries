// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_SIZE
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_SIZE
#include<srook/mpl/constant_sequence/algorithm/length.hpp>
namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class Sequence>
constexpr std::size_t size=length_v<Sequence>;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
