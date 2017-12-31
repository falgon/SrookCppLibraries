// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_IS_SORTED_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_IS_SORTED_HPP
#include<srook/mpl/constant_sequence/algorithm/sort.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<bool,class,template<std::size_t,std::size_t>class>
struct is_sorted;

template<std::size_t head,std::size_t second,std::size_t... tail,template<std::size_t,std::size_t>class comp>
struct is_sorted<true,std::index_sequence<head,second,tail...>,comp>{
	static constexpr bool value=is_sorted<comp<head,second>::value,std::index_sequence<second,tail...>,comp>::value;
};

template<std::size_t last1,std::size_t last2,template<std::size_t,std::size_t>class comp>
struct is_sorted<true,std::index_sequence<last1,last2>,comp>{
	static constexpr bool value=comp<last1,last2>::value;
};

template<std::size_t... seq,template<std::size_t,std::size_t>class comp>
struct is_sorted<false,std::index_sequence<seq...>,comp>:std::false_type{};

template<class Sequence,template<std::size_t,std::size_t>class comp=less>
constexpr bool is_sorted_v=is_sorted<comp<first_v<Sequence>,first_v<pop_front_t<Sequence>>>::value,pop_front_t<Sequence>,comp>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
