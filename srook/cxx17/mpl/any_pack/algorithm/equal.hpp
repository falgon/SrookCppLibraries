// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_EQUAL_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_EQUAL_HPP
#include<srook/mpl/variadic_player.hpp>
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<srook/cxx17/mpl/any_pack/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{
namespace detail{

template<class,class>
struct equal;
template<auto l_head,auto... l_tail,auto r_head,auto... r_tail>
struct equal<any_pack<l_head,l_tail...>,any_pack<r_head,r_tail...>>{
	static constexpr bool value = std::conditional_t<l_head==r_head,equal<any_pack<l_tail...>,any_pack<r_tail...>>,std::false_type>::value;
};
template<>
struct equal<any_pack<>,any_pack<>>:std::true_type{};
template<class L,class R>
constexpr bool equal_v = std::conditional_t<L::size()==R::size(),equal<L,R>,std::false_type>::value;

} // namespace detail
} // inline namespace v1
} // inlnie namespace mpl 
} // namespace srook

#endif