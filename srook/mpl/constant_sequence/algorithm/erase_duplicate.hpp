// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_ERASE_DUPLICATE_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_ERASE_DUPLICATE_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>
#include<srook/mpl/constant_sequence/algorithm/erase.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct erase_duplicate;

template<std::size_t head,std::size_t... tail>
struct erase_duplicate<std::index_sequence<head,tail...>>{
	using type=concat_t<std::index_sequence<head>,erase_t<head,typename erase_duplicate<std::index_sequence<tail...>>::type>>;
};

template<>
struct erase_duplicate<std::index_sequence<>>{
	using type=std::index_sequence<>;
};

template<class Seq>
using erase_duplicate_t=typename erase_duplicate<Seq>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
