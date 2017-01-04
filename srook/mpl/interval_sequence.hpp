#ifndef INCLUDED_SROOK_INTERVAL_SEQUENCE_IMPL
#define INCLUDED_SROOK_INTERVAL_SEQUENCE_IMPL
#include<utility>
#include<memory>
namespace srook{
inline namespace v1{

namespace mpl{
namespace interval_sequence{

template<class Operator,int interval>
struct Exp{
	using operator_type=Operator;
	static constexpr int intervalue=interval;
};
struct plus{
	template<class L,class R>
	static constexpr decltype(std::declval<L>()+std::declval<R>()) apply(L a,R b)noexcept{return a+b;}
};
struct minus{
	template<class L,class R>
	static constexpr decltype(std::declval<L>()-std::declval<R>()) apply(L a,R b)noexcept{return a-b;}
};
struct multiply{
	template<class L,class R>
	static constexpr decltype(std::declval<L>()*std::declval<R>()) apply(L a,R b)noexcept{return a*b;}
};
struct division{
	template<class L,class R>
	static constexpr decltype(std::declval<L>()/std::declval<R>()) apply(L a,R b)noexcept{return b?a/b:0;}
};

} // namespace interval_sequence
} // namespace mpl

namespace mpl{

template<class,std::size_t,std::size_t,class>
struct make_interval_sequence_impl;
template<class Operator,int interval,std::size_t n,std::size_t apply_value,std::size_t... v>
struct make_interval_sequence_impl<interval_sequence::Exp<Operator,interval>,n,apply_value,std::integer_sequence<int,v...>>{
	using type=
		typename make_interval_sequence_impl<
			interval_sequence::Exp<Operator,interval>,
			n-1,
			Operator::apply(apply_value,interval),
			std::integer_sequence<int,v...,apply_value>
		>::type;
};
template<class Operator,int interval,std::size_t apply_value,std::size_t... v>
struct make_interval_sequence_impl<mpl::interval_sequence::Exp<Operator,interval>,0,apply_value,std::integer_sequence<int,v...>>{
	using type=std::integer_sequence<int,v...>;
};
template<class Expression,int interval,class Sequence=std::integer_sequence<int>>
using make_interval_sequence=typename make_interval_sequence_impl<Expression,interval,interval,Sequence>::type;

template<template<class,class>class Range,int... v>
constexpr Range<int,std::allocator<int>> make_range_from_sequence(std::integer_sequence<int,v...>)
{
	return Range<int,std::allocator<int>>{v...};
}

} // mpl

} // inline namespace
} // namespace
#endif
