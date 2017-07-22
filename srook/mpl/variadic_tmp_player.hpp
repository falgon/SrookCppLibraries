// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TMP_PLAYER_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TMP_PLAYER_HPP
#include<cstddef>
#include<srook/config/libraries/optional.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{
// pack
template<class... T>
struct pack{
	static constexpr std::size_t size=sizeof...(T);
};

// Length
template<class Head,class... Tail>
constexpr std::size_t Length_v=1+Length_v<Tail...>;
template<class Tail>
constexpr std::size_t Length_v<Tail> =1;

// Concat
template<class...>
struct Concat;
template<class L,class... R>
struct Concat<L,R...>{
	static constexpr std::size_t size=sizeof...(R)+1;
	using type=pack<L,R...>;
};
template<class... L,class... R>
struct Concat<pack<L...>,pack<R...>>:Concat<L...,R...>{};
template<class L,class... R>
struct Concat<L,pack<R...>>:Concat<L,R...>{};
template<class... L,class... R>
struct Concat<pack<L...>,R...>:Concat<L...,R...>{};
template<>
struct Concat<pack<>,pack<>>{
	using type=pack<>;
};
template<class L,class... R>
using Concat_t=typename Concat<L,R...>::type;

// Transfer
template<template<class...>class Tuple,class... Arg>
struct Transfer{
	using type=Tuple<Arg...>;
};
template<template<class...>class Tuple,class... Arg>
struct Transfer<Tuple,pack<Arg...>>:Transfer<Tuple,Arg...>{};
template<template<class...>class Tuple,class... Arg>
using Transfer_t=typename Transfer<Tuple,Arg...>::type;

// Erase
template<class T,class... Pack>
struct Erase;
template<class T,class L,class... R>
struct Erase<T,L,R...>{
	using type=Concat_t<L,typename Erase<T,R...>::type>;
};
template<class L,class... R>
struct Erase<L,L,R...>{
	using type=pack<R...>;
};
template<class Tail>
struct Erase<Tail>{
	using type=pack<>;
};
template<class T,class L,class...R>
struct Erase<T,pack<L,R...>>:Erase<T,L,R...>{};
template<class T,class... Pack>
using Erase_t=typename Erase<T,Pack...>::type;

// Erase All
template<class T,class... Pack>
struct EraseAll;
template<class T,class L,class... R>
struct EraseAll<T,L,R...>{
	using type=Concat_t<L,typename EraseAll<T,R...>::type>;
};
template<class L,class... R>
struct EraseAll<L,L,R...>{
	using type=typename EraseAll<L,R...>::type;
};
template<class Tail>
struct EraseAll<Tail>{
	using type=pack<>;
};
template<class T,class L,class... R>
struct EraseAll<T,pack<L,R...>>:EraseAll<T,L,R...>{};
template<class T,class... Pack>
using EraseAll_t=typename EraseAll<T,Pack...>::type;

// No duplicate
template<class...>
struct NoDuplicate;
template<class Head,class... Tail>
struct NoDuplicate<Head,Tail...>{
private:
	using inner_type=Erase_t<Head,typename NoDuplicate<Tail...>::type>;
public:
	using type=Concat_t<Head,inner_type>;
};
template<class Head,class... Tail>
struct NoDuplicate<pack<Head,Tail...>>:NoDuplicate<Head,Tail...>{};
template<>
struct NoDuplicate<>{
	using type=pack<>;
};
template<class... Pack>
using NoDuplicate_t=typename NoDuplicate<Pack...>::type;

// Replace
template<class,class,class...>
struct Replace;
template<class T,class R,class Head,class... Tail>
struct Replace<T,R,Head,Tail...>{
	using type=Concat_t<Head,typename Replace<T,R,Tail...>::type>;
};
template<class T,class R,class... Tail>
struct Replace<T,R,T,Tail...>{
	using type=Concat_t<R,Tail...>;
};
template<class T,class R>
struct Replace<T,R>{
	using type=pack<>;
};
template<class T,class R,class Head,class... Tail>
struct Replace<T,R,pack<Head,Tail...>>:Replace<T,R,Head,Tail...>{};
template<class T,class R,class... Pack>
using Replace_t=typename Replace<T,R,Pack...>::type;

// Replace All
template<class,class,class...>
struct ReplaceAll;
template<class T,class R,class Head,class... Tail>
struct ReplaceAll<T,R,Head,Tail...>{
	using type=Concat_t<Head,typename ReplaceAll<T,R,Tail...>::type>;
};
template<class T,class R,class... Tail>
struct ReplaceAll<T,R,T,Tail...>{
	using type=Concat_t<R,typename ReplaceAll<T,R,Tail...>::type>;
};
template<class T,class R>
struct ReplaceAll<T,R>{
	using type=pack<>;
};
template<class T,class R,class Head,class... Tail>
struct ReplaceAll<T,R,pack<Head,Tail...>>:ReplaceAll<T,R,Head,Tail...>{};
template<class T,class R,class... Pack>
using ReplaceAll_t=typename ReplaceAll<T,R,Pack...>::type;

// Index of
template<class,class...>
struct IndexOf;
template<class T,class Head,class... Tail>
struct IndexOf<T,Head,Tail...>{
	static constexpr int value=IndexOf<T,Tail...>::value==-1?IndexOf<T,Tail...>::value:1+IndexOf<T,Tail...>::value;
};
template<class Head,class... Tail>
struct IndexOf<Head,Head,Tail...>{
	static constexpr int value=0;
};
template<class Tail>
struct IndexOf<Tail>{
	static constexpr int value=-1;
};
template<class T,class Head,class... Tail>
struct IndexOf<T,pack<Head,Tail...>>:IndexOf<T,Head,Tail...>{};
template<class T,class... Args>
constexpr int IndexOf_v=IndexOf<T,Args...>::value;

// First
template<class...>
struct First;
template<class Head,class... Tail>
struct First<Head,Tail...>{
	using type=Head;
};
template<>
struct First<>{
	using type=NULLOPT_T;
};
template<class Head,class... Tail>
struct First<pack<Head,Tail...>>:First<Head>{};
template<class... Pack>
using First_t=typename First<Pack...>::type;

// Last
template<class...>
struct Last;
template<class Head,class... Tail>
struct Last<Head,Tail...>{
	using type=typename Last<Tail...>::type;
};
template<>
struct Last<>{
	using type=NULLOPT_T;
};
template<class Tail>
struct Last<Tail>{
	using type=Tail;
};
template<class Head,class... Tail>
struct Last<pack<Head,Tail...>>:Last<Head,Tail...>{};
template<class... Pack>
using Last_t=typename Last<Pack...>::type;

// Pop front
template<class...>
struct PopFront;
template<class Head,class... Tail>
struct PopFront<Head,Tail...>{
	using type=pack<Tail...>;
};
template<class Head,class... Tail>
struct PopFront<pack<Head,Tail...>>:PopFront<Head,Tail...>{};
template<class... Pack>
using PopFront_t=typename PopFront<Pack...>::type;

// Pop back
template<class...>
struct PopBack;
template<class Head,class... Tail>
struct PopBack<Head,Tail...>{
	using type=Concat_t<Head,typename PopBack<Tail...>::type>;
};
template<class Tail>
struct PopBack<Tail>{
	using type=pack<>;
};
template<class Head,class... Tail>
struct PopBack<pack<Head,Tail...>>:PopBack<Head,Tail...>{};
template<class... Pack>
using PopBack_t=typename PopBack<Pack...>::type;

// Reverse
template<class... Args>
struct Reverse{
	using type=Concat_t<Last_t<Args...>,typename Reverse<PopBack_t<Args...>>::type>;
};
template<>
struct Reverse<pack<>>{
	using type=pack<>;
};
template<class... Args>
struct Reverse<pack<Args...>>:Reverse<Args...>{};
template<class... Args>
using Reverse_t=typename Reverse<Args...>::type;

// Partial Head
template<std::size_t,class...>
struct PartialHead;
template<std::size_t N,class Head,class... Args>
struct PartialHead<N,Head,Args...>{
	using type=Concat_t<Head,typename PartialHead<N-1,Args...>::type>;
};
template<class Tail,class... Args>
struct PartialHead<1,Tail,Args...>{
	using type=Tail;
};
template<std::size_t N,class Head,class... Args>
struct PartialHead<N,pack<Head,Args...>>:PartialHead<N,Head,Args...>{};
template<std::size_t N,class... Pack>
using PartialHead_t=typename PartialHead<N,Pack...>::type;

// Partial Tail
template<class... Args>
struct Apply_Partial_Tail;
template<class Head,class... Tail>
struct Apply_Partial_Tail<Head,Tail...>{
	using type=Concat_t<Head,typename Apply_Partial_Tail<Tail...>::type>;
};
template<class Tail>
struct Apply_Partial_Tail<Tail>{
	using type=Tail;
};
template<>
struct Apply_Partial_Tail<>{
	using type=pack<>;
};
template<std::size_t N,class Head,class... Tail>
struct PartialTail{
	using type=typename PartialTail<N-1,Tail...>::type;
};
template<class Head,class... Tail>
struct PartialTail<0,Head,Tail...>{
	using type=Concat_t<Head,typename Apply_Partial_Tail<Tail...>::type>;
};
template<std::size_t N,class Head,class... Tail>
struct PartialTail<N,pack<Head,Tail...>>:PartialTail<N,Head,Tail...>{};
template<std::size_t N,class... Args>
using PartialTail_t=typename PartialTail<N,Args...>::type;

// At
template<std::size_t,class...>
struct At;
template<std::size_t index,class Head,class... Tail>
struct At<index,Head,Tail...>{
	using type=typename At<index-1,Tail...>::type;
};
template<class Target,class... Tail>
struct At<0,pack<Target,Tail...>>{
	using type=Target;
};
template<class Target,class... Tail>
struct At<0,Target,Tail...>{
	using type=Target;
};
template<std::size_t index,class Head,class... Tail>
struct At<index,pack<Head,Tail...>>:At<index,Head,Tail...>{};
template<std::size_t index,class... Pack>
using At_t=typename At<index,Pack...>::type;

// SwapAt
template<class,class,std::size_t,class,class>
struct SwapAt;
template<class LH,class... LT,class RH,class... RT,std::size_t n,class LHeads,class RHeads>
struct SwapAt<pack<LH,LT...>,pack<RH,RT...>,n,LHeads,RHeads>{
	using L_type=typename SwapAt<pack<LT...>,pack<RT...>,n-1,Concat_t<LH,LHeads>,Concat_t<RH,RHeads>>::L_type;
	using R_type=typename SwapAt<pack<LT...>,pack<RT...>,n-1,Concat_t<LH,LHeads>,Concat_t<RH,RHeads>>::R_type;
};
template<class LT,class... L,class RT,class... R,class LHeads,class RHeads>
struct SwapAt<pack<LT,L...>,pack<RT,R...>,0,LHeads,RHeads>{
	using L_type=Concat_t<LHeads,pack<RT,L...>>;
	using R_type=Concat_t<RHeads,pack<LT,R...>>;
};
template<class LPack,class RPack,std::size_t IndexTarget>
using SwapAt_L=typename SwapAt<LPack,RPack,IndexTarget,pack<>,pack<>>::L_type;
template<class LPack,class RPack,std::size_t IndexTarget>
using SwapAt_R=typename SwapAt<LPack,RPack,IndexTarget,pack<>,pack<>>::R_type;


// SwapAt_Specified
template<class,std::size_t,class,std::size_t,class,class,std::size_t,std::size_t>
struct SwapAt_Specified_L_t;

template<class,std::size_t,class,std::size_t,class,class,std::size_t,std::size_t>
struct SwapAt_Specified_R_t;

template<
	class LH,class... LT,std::size_t IL,
	class... R,std::size_t IR,
	class LHeads,class RHeads,
	std::size_t CORE_IL,std::size_t CORE_IR
>
struct SwapAt_Specified_L_t<
		pack<LH,LT...>,IL,
		pack<R...>,IR,
		LHeads,RHeads,
		CORE_IL,CORE_IR
>{
	using L_type=
		typename SwapAt_Specified_L_t<
			pack<LT...>,IL-1,
			pack<R...>,IR,
			Concat_t<LH,LHeads>,pack<R...>,
			CORE_IL,CORE_IR
		>::L_type;
};

template<
	class... L,std::size_t IL,
	class RH,class... RT,std::size_t IR,
	class LHeads,class RHeads,
	std::size_t CORE_IL,std::size_t CORE_IR
>
struct SwapAt_Specified_R_t<
		pack<L...>,IL,
		pack<RH,RT...>,IR,
		LHeads,RHeads,
		CORE_IL,CORE_IR
>{
	using R_type=
		typename SwapAt_Specified_R_t<
			pack<L...>,IL,
			pack<RT...>,IR-1,
			pack<L...>,Concat_t<RH,RHeads>,
			CORE_IL,CORE_IR
		>::R_type;
};

template<
	class LH,class... LT,
	class... R,std::size_t IR,
	class LHeads,class RHeads,
	std::size_t CORE_IL,std::size_t CORE_IR
>
struct SwapAt_Specified_L_t<
		pack<LH,LT...>,0,
		pack<R...>,IR,
		LHeads,RHeads,
		CORE_IL,CORE_IR
>{
	using L_type=
		Concat_t<
			Concat_t<
				LHeads,
				At_t<CORE_IR,pack<R...>>
			>,
		LT...>;
};
template<
	class... L,std::size_t IL,
	class RH,class... RT,
	class LHeads,class RHeads,
	std::size_t CORE_IL,std::size_t CORE_IR
>
struct SwapAt_Specified_R_t<
		pack<L...>,IL,
		pack<RH,RT...>,0,
		LHeads,RHeads,
		CORE_IL,CORE_IR
>{
		using R_type=
			Concat_t<
				Concat_t<
					RHeads,
					At_t<CORE_IL,pack<L...>>
				>,
			RT...>;
};

template<class LPack,std::size_t IL,class RPack,std::size_t IR>
using SwapAt_Specified_L=typename SwapAt_Specified_L_t<LPack,IL,RPack,IR,pack<>,pack<>,IL,IR>::L_type;
template<class LPack,std::size_t IL,class RPack,std::size_t IR>
using SwapAt_Specified_R=typename SwapAt_Specified_R_t<LPack,IL,RPack,IR,pack<>,pack<>,IL,IR>::R_type;

} // inline namespace v1
} // namespace mpl
} // namespace roki
#endif
