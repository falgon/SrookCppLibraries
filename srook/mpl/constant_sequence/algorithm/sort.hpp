#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_SORT_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_SORT_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/filter.hpp>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<template<std::size_t,std::size_t>class Comp,class>
struct sort;
template<template<std::size_t,std::size_t>class Comp,std::size_t pivot,std::size_t... tail>
struct sort<Comp,std::index_sequence<pivot,tail...>>{
private:
	template<template<std::size_t>class Comp_,std::size_t T>
	struct not_{
		constexpr static bool value=not Comp_<T>::value;
	};
	template<std::size_t lhs>
	using lcomp=Comp<lhs,pivot>;
	template<std::size_t rhs>
	using rcomp=not_<lcomp,rhs>;
public:
	using type=
		concat_t<
			typename sort<Comp,filter_t<lcomp,std::index_sequence<tail...>>>::type,
			concat_t<std::index_sequence<pivot>,filter_t<rcomp,std::index_sequence<tail...>>>
		>;
};

template<template<std::size_t,std::size_t>class Comp>
struct sort<Comp,std::index_sequence<>>{
	using type=std::index_sequence<>;
};

template<std::size_t l,std::size_t r>
using less=std::integral_constant<bool,(l<r)>;
template<std::size_t l,std::size_t r>
using greater=std::integral_constant<bool,!less<l,r>::value>;
template<std::size_t l,std::size_t r>
using less_or_equal=std::integral_constant<bool,(l<=r)>;
template<std::size_t l,std::size_t r>
using greater_or_equal=std::integral_constant<bool,(l>=r)>;

template<class Sequence,template<std::size_t,std::size_t>class Comp=less>
using sort_t=typename sort<Comp,Sequence>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
