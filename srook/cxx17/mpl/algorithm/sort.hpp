// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_SORT_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_SORT_HPP
#include<srook/mpl/variadic_player.hpp>
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/filter.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{
namespace detail{

template<template<auto,auto>class Comp,class>
struct sort;
template<template<auto,auto>class Comp,auto pivot,auto... tail>
struct sort<Comp,any_pack<pivot,tail...>>{
private:
	template<template<auto>class Comp_,auto T>
	struct not_{
		constexpr static bool value=not Comp_<T>::value;
	};
	template<auto lhs>
	using lcomp = Comp<lhs,pivot>;
	template<auto rhs>
	using rcomp = not_<lcomp,rhs>;
public:
	using type=
		concat_t<
			typename sort<Comp,filter_t<lcomp,any_pack<tail...>>>::type,
			concat_t<any_pack<pivot>,filter_t<rcomp,any_pack<tail...>>>
		>;
};
template<template<auto,std::size_t>class Comp>
struct sort<Comp,any_pack<>>{
	    using type = any_pack<>;
};
template<class Sequence,template<auto,auto>class Comp>
using sort_t = typename sort<Comp,Sequence>::type;

} // namespace detail
} // inline namespace v1
} // inlnie namespace mpl 
} // namespace srook

#endif
