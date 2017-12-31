// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FIND_IF_NOT_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_FIND_IF_NOT_HPP
#include"find_if.hpp"
namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<template<std::size_t>class pred,class Sequence>
constexpr int find_if_not_v=find_if<!pred<first_v<Sequence>>::value,pred,pop_front_t<Sequence>,0,find_if_tag_scope::find_if_not_tag>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
