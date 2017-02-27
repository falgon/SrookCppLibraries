#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_PLAYER_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_PLAYER_HPP
#include<type_traits>
#include<utility>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

// length
template<class>
struct Length;
template<std::size_t... v>
struct Length<std::index_sequence<v...>>{
	static constexpr std::size_t value=std::index_sequence<v...>::size();
};
template<class Seq>
constexpr std::size_t Length_v=Length<Seq>::value;


// concat
template<class,class>
struct Concat;
template<std::size_t... l,std::size_t... r>
struct Concat<std::index_sequence<l...>,std::index_sequence<r...>>{
	using type=std::index_sequence<l...,r...>;
};

template<class L,class R>
using Concat_t=typename Concat<L,R>::type;

// erase
template<std::size_t,class>
struct Erase;
template<std::size_t target,std::size_t head,std::size_t... tail>
struct Erase<target,std::index_sequence<head,tail...>>{
	using type=Concat_t<std::index_sequence<head>,typename Erase<target,std::index_sequence<tail...>>::type>;
};
template<std::size_t target,std::size_t... pack>
struct Erase<target,std::index_sequence<target,pack...>>{
	using type=std::index_sequence<pack...>;
};
template<std::size_t target>
struct Erase<target,std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<std::size_t target,class Sequence=std::index_sequence<>>
using Erase_t=typename Erase<target,Sequence>::type;

// erase all
template<std::size_t,class>
struct EraseAll;
template<std::size_t target,std::size_t head,std::size_t... tail>
struct EraseAll<target,std::index_sequence<head,tail...>>{
	using type=Concat_t<std::index_sequence<head>,typename EraseAll<target,std::index_sequence<tail...>>::type>;
};
template<std::size_t target,std::size_t... pack>
struct EraseAll<target,std::index_sequence<target,pack...>>{
	using type=typename EraseAll<target,std::index_sequence<pack...>>::type;
};
template<std::size_t target>
struct EraseAll<target,std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<std::size_t target,class Sequence=std::index_sequence<>>
using EraseAll_t=typename EraseAll<target,Sequence>::type;

// First
template<class>
struct First;

template<std::size_t head,std::size_t... tail>
struct First<std::index_sequence<head,tail...>>{
	static constexpr std::size_t value=head;
};

template<class Seq>
static constexpr std::size_t First_v=First<Seq>::value;

// last
template<class>
struct Last;

template<std::size_t head,std::size_t... tail>
struct Last<std::index_sequence<head,tail...>>{
	static constexpr std::size_t value=Last<std::index_sequence<tail...>>::value;
};

template<std::size_t tail>
struct Last<std::index_sequence<tail>>{
	static constexpr std::size_t value=tail;
};

template<class Seq>
static constexpr std::size_t Last_v=Last<Seq>::value;


// transfer
template<template<class...>class,class>
struct Transfer;

template<template<class...>class Range,std::size_t... seq>
struct Transfer<Range,std::index_sequence<seq...>>{
	static Range<decltype(First_v<std::index_sequence<seq...>>)> value;
};

template<template<class...>class Range,std::size_t... seq>
Range<decltype(First_v<std::index_sequence<seq...>>)> Transfer<Range,std::index_sequence<seq...>>::value={{seq...}};

// no duplicate
template<class>
struct NoDuplicate;

template<std::size_t head,std::size_t... tail>
struct NoDuplicate<std::index_sequence<head,tail...>>{
	using type=Concat_t<std::index_sequence<head>,Erase_t<head,typename NoDuplicate<std::index_sequence<tail...>>::type>>;
};

template<>
struct NoDuplicate<std::index_sequence<>>{
	using type=std::index_sequence<>;
};

template<class Seq>
using NoDuplicate_t=typename NoDuplicate<Seq>::type;

// replace
template<std::size_t,std::size_t,class>
struct Replace;
template<std::size_t target,std::size_t replace_value,std::size_t head,std::size_t... tail>
struct Replace<target,replace_value,std::index_sequence<head,tail...>>{
	using type=Concat_t<std::index_sequence<head>,typename Replace<target,replace_value,std::index_sequence<tail...>>::type>;
};
template<std::size_t target,std::size_t replace_value,std::size_t... tail>
struct Replace<target,replace_value,std::index_sequence<target,tail...>>{
	using type=Concat_t<std::index_sequence<replace_value>,std::index_sequence<tail...>>;
};
template<std::size_t target,std::size_t replace_value>
struct Replace<target,replace_value,std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<std::size_t target,std::size_t replace_value,class Seq>
using Replace_t=typename Replace<target,replace_value,Seq>::type;

// replace all
template<std::size_t,std::size_t,class>
struct ReplaceAll;
template<std::size_t target,std::size_t replace_value,std::size_t head,std::size_t... tail>
struct ReplaceAll<target,replace_value,std::index_sequence<head,tail...>>{
	using type=Concat_t<std::index_sequence<head>,typename ReplaceAll<target,replace_value,std::index_sequence<tail...>>::type>;
};
template<std::size_t target,std::size_t replace_value,std::size_t... tail>
struct ReplaceAll<target,replace_value,std::index_sequence<target,tail...>>{
	using type=Concat_t<std::index_sequence<replace_value>,typename ReplaceAll<target,replace_value,std::index_sequence<tail...>>::type>;
};
template<std::size_t target,std::size_t replace_value>
struct ReplaceAll<target,replace_value,std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<std::size_t target,std::size_t replace_value,class Sequence>
using ReplaceAll_t=typename ReplaceAll<target,replace_value,Sequence>::type;

// Find
template<std::size_t,class>
struct Find;
template<std::size_t target,std::size_t head,std::size_t... tail>
struct Find<target,std::index_sequence<head,tail...>>{
	static constexpr int value=
		Find<target,std::index_sequence<tail...>>::value==-1?
			Find<target,std::index_sequence<tail...>>::value:
			1+Find<target,std::index_sequence<tail...>>::value;
};
template<std::size_t head,std::size_t... tail>
struct Find<head,std::index_sequence<head,tail...>>{
	static constexpr int value=0;
};
template<std::size_t target>
struct Find<target,std::index_sequence<>>{
	static constexpr int value=-1;
};
template<std::size_t index,class Sequence>
constexpr int Find_v=Find<index,Sequence>::value;

// pop front
template<class>
struct PopFront;
template<std::size_t head,std::size_t... tail>
struct PopFront<std::index_sequence<head,tail...>>{
	using type=std::index_sequence<tail...>;
};
template<class Sequence>
using PopFront_t=typename PopFront<Sequence>::type;

// pop back
template<class>
struct PopBack;
template<std::size_t head,std::size_t... tail>
struct PopBack<std::index_sequence<head,tail...>>{
	using type=Concat_t<std::index_sequence<head>,typename PopBack<std::index_sequence<tail...>>::type>;
};
template<std::size_t tail>
struct PopBack<std::index_sequence<tail>>{
	using type=std::index_sequence<>;
};
template<class Sequence>
using PopBack_t=typename PopBack<Sequence>::type;

// insert
template<class,std::size_t,class,bool>
struct Insert;
template<std::size_t... seq,std::size_t index,std::size_t head,std::size_t... tail>
struct Insert<std::index_sequence<seq...>,index,std::index_sequence<head,tail...>,true>{
	using type=Concat_t<std::index_sequence<head>,typename Insert<std::index_sequence<seq...>,index-1,std::index_sequence<tail...>,static_cast<bool>(index-1)>::type>;
};
template<std::size_t... seq1,std::size_t... seq2>
struct Insert<std::index_sequence<seq1...>,0,std::index_sequence<seq2...>,false>{
	using type=std::index_sequence<seq1...,seq2...>;
};
template<class Sequence1,std::size_t index,class Sequence2>
using Insert_t=typename Insert<Sequence1,index,Sequence2,static_cast<bool>(index)>::type;


// reverse
template<class>
struct Reverse;
template<std::size_t... seq>
struct Reverse<std::index_sequence<seq...>>{
	using type=
		Concat_t<
			std::index_sequence<Last_v<std::index_sequence<seq...>>>,
			typename Reverse<PopBack_t<std::index_sequence<seq...>>>::type
		>;
};
template<>
struct Reverse<std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<class Sequence>
using Reverse_t=typename Reverse<Sequence>::type;

// partial head
template<std::size_t,class>
struct PartialHead;
template<std::size_t target,std::size_t head,std::size_t... tail>
struct PartialHead<target,std::index_sequence<head,tail...>>{
	using type=Concat_t<std::index_sequence<head>,typename PartialHead<target-1,std::index_sequence<tail...>>::type>;
};
template<std::size_t tail,std::size_t... args>
struct PartialHead<1,std::index_sequence<tail,args...>>{
	using type=std::index_sequence<tail>;
};
template<std::size_t target,class Sequence>
using PartialHead_t=typename PartialHead<target,Sequence>::type;

// partial tail
template<class>
struct PartialTail_impl;
template<std::size_t head,std::size_t... tail>
struct PartialTail_impl<std::index_sequence<head,tail...>>{
	using type=Concat_t<std::index_sequence<head>,typename PartialTail_impl<std::index_sequence<tail...>>::type>;
};
template<std::size_t tail>
struct PartialTail_impl<std::index_sequence<tail>>{
	using type=std::index_sequence<tail>;
};
template<>
struct PartialTail_impl<std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<std::size_t,class>
struct PartialTail;
template<std::size_t target,std::size_t head,std::size_t... tail>
struct PartialTail<target,std::index_sequence<head,tail...>>{
	using type=typename PartialTail<target-1,std::index_sequence<tail...>>::type;
};
template<std::size_t head,std::size_t... tail>
struct PartialTail<0,std::index_sequence<head,tail...>>{
	using type=Concat_t<std::index_sequence<head>,typename PartialTail_impl<std::index_sequence<tail...>>::type>;
};
template<std::size_t target,class Sequence>
using PartialTail_t=typename PartialTail<target,Sequence>::type;

// at
template<std::size_t,class>
struct At;
template<std::size_t index,std::size_t head,std::size_t... tail>
struct At<index,std::index_sequence<head,tail...>>{
	static constexpr std::size_t value=At<index-1,std::index_sequence<tail...>>::value;
};
template<std::size_t head,std::size_t... tail>
struct At<0,std::index_sequence<head,tail...>>{
	static constexpr std::size_t value=head;
};
template<std::size_t index,class Sequence>
static constexpr std::size_t At_v=At<index,Sequence>::value;

// swap at
template<std::size_t,class,class>
struct SwapAt;
template<std::size_t target,std::size_t head1,std::size_t... tail1,std::size_t head2,std::size_t... tail2>
struct SwapAt<target,std::index_sequence<head1,tail1...>,std::index_sequence<head2,tail2...>>{
	using L_type=
		Concat_t<std::index_sequence<head1>,typename SwapAt<target-1,std::index_sequence<tail1...>,std::index_sequence<tail2...>>::L_type>;
	using R_type=
		Concat_t<std::index_sequence<head2>,typename SwapAt<target-1,std::index_sequence<tail1...>,std::index_sequence<tail2...>>::R_type>;
};
template<std::size_t head1,std::size_t... tail1,std::size_t head2,std::size_t... tail2>
struct SwapAt<0,std::index_sequence<head1,tail1...>,std::index_sequence<head2,tail2...>>{
	using L_type=Concat_t<std::index_sequence<head2>,std::index_sequence<tail1...>>;
	using R_type=Concat_t<std::index_sequence<head1>,std::index_sequence<tail2...>>;
};
template<std::size_t target,class Seq1,class Seq2>
using SwapAt_L=typename SwapAt<target,Seq1,Seq2>::L_type;
template<std::size_t target,class Seq1,class Seq2>
using SwapAt_R=typename SwapAt<target,Seq1,Seq2>::R_type;


// swap at specified
template<std::size_t,class,std::size_t,class>
struct SwapAt_Specified;
template<
	std::size_t left_target_index,std::size_t lhead,std::size_t... ltail,
	std::size_t right_target_index,std::size_t rhead,std::size_t... rtail
>
struct SwapAt_Specified<left_target_index,std::index_sequence<lhead,ltail...>,right_target_index,std::index_sequence<rhead,rtail...>>{
	using L_type=
		Concat_t<
			std::index_sequence<lhead>,
			typename SwapAt_Specified<
				left_target_index-1,
				std::index_sequence<ltail...>,
				right_target_index,
				std::index_sequence<rhead,rtail...>
			>::L_type
		>;
	using R_type=
		Concat_t<
			std::index_sequence<rhead>,
			typename SwapAt_Specified<
				left_target_index,
				std::index_sequence<lhead,ltail...>,
				right_target_index-1,
				std::index_sequence<rtail...>
			>::R_type
		>;
};

template<
	std::size_t lhead,std::size_t... ltail,
	std::size_t right_target_index,std::size_t rhead,std::size_t... rtail
>
struct SwapAt_Specified<0,std::index_sequence<lhead,ltail...>,right_target_index,std::index_sequence<rhead,rtail...>>{
	using L_type=
		std::index_sequence<At_v<right_target_index,std::index_sequence<rhead,rtail...>>,ltail...>;
	using R_type=
		std::index_sequence<>;
};

template<
	std::size_t left_target_index,std::size_t lhead,std::size_t... ltail,
	std::size_t rhead,std::size_t... rtail
>
struct SwapAt_Specified<left_target_index,std::index_sequence<lhead,ltail...>,0,std::index_sequence<rhead,rtail...>>{
	using Ltype=
		std::index_sequence<>;
	using R_type=
		std::index_sequence<At_v<left_target_index,std::index_sequence<lhead,ltail...>>,rtail...>;
};

template<std::size_t left_target_index,class Seq1,std::size_t right_target_index,class Seq2>
using SwapAt_Specified_L=typename SwapAt_Specified<left_target_index,Seq1,right_target_index,Seq2>::L_type;
template<std::size_t left_target_index,class Seq1,std::size_t right_target_index,class Seq2>
using SwapAt_Specified_R=typename SwapAt_Specified<left_target_index,Seq1,right_target_index,Seq2>::R_type;


// max min
template<std::size_t L,std::size_t R>
struct Greater{
	using type=typename std::conditional<(L > R),std::index_sequence<L>,std::index_sequence<R>>::type;
};
template<std::size_t L,std::size_t R>
struct Less{
	using type=typename std::conditional<(L < R),std::index_sequence<L>,std::index_sequence<R>>::type;
};

template<template<std::size_t,std::size_t>class,class>
struct maxmin_impl;
template<template<std::size_t,std::size_t>class Comp,std::size_t head1,std::size_t head2,std::size_t... tail>
struct maxmin_impl<Comp,std::index_sequence<head1,head2,tail...>>{
	static constexpr std::size_t value=maxmin_impl<Comp,Concat_t<typename Comp<head1,head2>::type,std::index_sequence<tail...>>>::value;
};
template<template<std::size_t,std::size_t>class Comp,std::size_t target>
struct maxmin_impl<Comp,std::index_sequence<target>>{
	static constexpr std::size_t value=target;
};
template<class Sequence>
constexpr std::size_t max_v=maxmin_impl<Greater,Sequence>::value;
template<class Sequence>
constexpr std::size_t min_v=maxmin_impl<Less,Sequence>::value;

// filter
template<template<std::size_t>class,class>
struct filter;
template<template<std::size_t>class Cond,std::size_t head,std::size_t... tail>
struct filter<Cond,std::index_sequence<head,tail...>>{
private:
	template<bool,class,class>
	struct if_append;
	template<std::size_t... seq1,std::size_t... seq2>
	struct if_append<true,std::index_sequence<seq1...>,std::index_sequence<seq2...>>{
		using type=std::index_sequence<seq1...,seq2...>;
	};
	template<std::size_t... seq1,std::size_t... seq2>
	struct if_append<false,std::index_sequence<seq1...>,std::index_sequence<seq2...>>{
		using type=std::index_sequence<seq2...>;
	};
	template<bool condition,class Seq1,class Seq2>
	using if_append_t=typename if_append<condition,Seq1,Seq2>::type;

public:
	using type=if_append_t<Cond<head>::value,std::index_sequence<head>,typename filter<Cond,std::index_sequence<tail...>>::type>;
};
template<template<std::size_t>class Cond>
struct filter<Cond,std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<template<std::size_t>class Cond,class Seq>
using filter_t=typename filter<Cond,Seq>::type;

// quick sort
template<template<std::size_t,std::size_t>class Comp,class>
struct quicksort;
template<template<std::size_t,std::size_t>class Comp,std::size_t pivot,std::size_t... tail>
struct quicksort<Comp,std::index_sequence<pivot,tail...>>{
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
		Concat_t<
			typename quicksort<Comp,filter_t<lcomp,std::index_sequence<tail...>>>::type,
			Concat_t<std::index_sequence<pivot>,filter_t<rcomp,std::index_sequence<tail...>>>
		>;
};

template<template<std::size_t,std::size_t>class Comp>
struct quicksort<Comp,std::index_sequence<>>{
	using type=std::index_sequence<>;
};

template<std::size_t l,std::size_t r>
using less=std::integral_constant<bool,(l<r)>;
template<std::size_t l,std::size_t r>
using greater=std::integral_constant<bool,(l>r)>;

template<class Sequence,template<std::size_t,std::size_t>class Comp=less>
using quicksort_t=typename quicksort<Comp,Sequence>::type;


// Summation
template<class,std::size_t>
struct Summation;
template<std::size_t... seq,std::size_t n>
struct Summation<std::index_sequence<seq...>,n>{
	static constexpr std::size_t value=
		((2*First_v<std::index_sequence<seq...>>)+
		((n-1)*(First_v<PopFront_t<std::index_sequence<seq...>>>-First_v<std::index_sequence<seq...>>)*n))/2;
};
template<class Sequence,std::size_t n=Sequence::size()>
constexpr std::size_t Summation_v=Summation<Sequence,n>::value;



} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
