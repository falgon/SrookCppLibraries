// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_CONCAT_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_CONCAT_HPP
#include<srook/mpl/variadic_player.hpp>
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>

namespace srook{
inline namespace mpl{
inline namespace v1{

namespace detail{

template<class,class> struct concat;
template<auto... l,auto... r>
struct concat<any_pack<l...>,any_pack<r...>>{
	using type = any_pack<l...,r...>;
};
template<class L,class R>
using concat_t = typename concat<L,R>::type;

} // namespace detail
} // inline namespace v1
} // inlnie namespace mpl 
} // namespace srook

#endif
