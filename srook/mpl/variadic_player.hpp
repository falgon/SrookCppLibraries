#ifndef INCLUDED_SROOK_VARIADIC_PARAM_PLAYER
#define INCLUDED_SROOK_VARIADIC_PARAM_PLAYER
namespace srook{

// core pack
template<class...>
struct pack{};

// generating pack from template arguments
template<class... Args>
using Generate=pack<Args...>;

// Length
template<class Head,class... Tail>
constexpr std::size_t Length_v=1+Length_v<Tail...>;
template<class Tail>
constexpr std::size_t Length_v<Tail> =1;

// Concat
template<class L,class... R>
struct Concat{
	using type=Generate<L,R...>;
};
template<class... L,class... R>
struct Concat<pack<L...>,pack<R...>>{
	using type=Generate<L...,R...>;
};
template<class L,class... R>
struct Concat<L,pack<R...>>{
	using type=Generate<L,R...>;
};
template<class L,class... R>
using Concat_t=typename Concat<L,R...>::type;

// Erase
template<class,class...>
struct Erase;
template<class T,class Head,class... Tail>
struct Erase<T,pack<Head,Tail...>>{
	using type=Concat_t<Head,typename Erase<T,Generate<Tail...>>::type>;
};
template<class Head,class... Tail>
struct Erase<Head,pack<Head,Tail...>>{
	using type=Generate<Tail...>;
};
template<class Tail>
struct Erase<Tail,pack<>>{
	using type=pack<>;
};
template<class T,class... Pack>
using Erase_t=typename Erase<T,Pack...>::type;

// Erase All
template<class,class...>
struct EraseAll;
template<class T,class Head,class... Tail>
struct EraseAll<T,pack<Head,Tail...>>{
	using type=Concat_t<Head,typename EraseAll<T,Generate<Tail...>>::type>;
};
template<class Head,class... Tail>
struct EraseAll<Head,pack<Head,Tail...>>{
	using type=typename EraseAll<Head,Generate<Tail...>>::type;
};
template<class Tail>
struct EraseAll<Tail,pack<>>{
	using type=pack<>;
};
template<class T,class... Pack>
using EraseAll_t=typename EraseAll<T,Pack...>::type;

// No Duplicate
template<class Pack>
struct NoDuplicate;
template<class Head,class... Tail>
struct NoDuplicate<pack<Head,Tail...>>{
private:
	using inner_result=Erase_t<Head,typename NoDuplicate<Generate<Tail...>>::type>;
public:
	using type=Concat_t<Head,inner_result>;
};
template<>
struct NoDuplicate<pack<>>{
	using type=pack<>;
};
template<class... Pack>
using NoDuplicate_t=typename NoDuplicate<Pack...>::type;

// Replace
template<class,class,class...>
struct Replace;
template<class T,class R,class Head,class... Tail>
struct Replace<T,R,pack<Head,Tail...>>{
	using type=Concat_t<Head,typename Replace<T,R,pack<Tail...>>::type>;
};
template<class T,class R,class... Tail>
struct Replace<T,R,pack<T,Tail...>>{
	using type=Concat_t<R,Tail...>;
};
template<class T,class R>
struct Replace<T,R,pack<>>{
	using type=pack<>;
};
template<class T,class R,class... Pack>
using Replace_t=typename Replace<T,R,Pack...>::type;

// Replace All
template<class,class,class...>
struct ReplaceAll;
template<class T,class R,class Head,class... Tail>
struct ReplaceAll<T,R,pack<Head,Tail...>>{
	using type=Concat_t<Head,typename ReplaceAll<T,R,pack<Tail...>>::type>;
};
template<class T,class R,class... Tail>
struct ReplaceAll<T,R,pack<T,Tail...>>{
	using type=Concat_t<R,typename ReplaceAll<T,R,pack<Tail...>>::type>;
};
template<class T,class R>
struct ReplaceAll<T,R,pack<>>{
	using type=pack<>;
};
template<class T,class R,class... Pack>
using ReplaceAll_t=typename ReplaceAll<T,R,Pack...>::type;

// Index of
template<class,class...>
struct IndexOf;
template<class T,class Head,class... Tail>
struct IndexOf<T,Head,Tail...>{
private:
	static constexpr int tmp=IndexOf<T,Tail...>::value;
public:
	static constexpr int value=tmp==-1?tmp:1+tmp;
};
template<class T,class Head,class... Tail>
struct IndexOf<T,pack<Head,Tail...>>{
private:
	static constexpr int tmp=IndexOf<T,Tail...>::value;
public:
	static constexpr int value=tmp==-1?tmp:1+tmp;
};
template<class Head,class... Tail>
struct IndexOf<Head,Head,Tail...>{
	static constexpr int value=0;
};
template<class Tail>
struct IndexOf<Tail>{
	static constexpr int value=-1;
};
template<class T,class... Args>
constexpr int IndexOf_v=IndexOf<T,Args...>::value;

// First
template<class...>
struct First;
template<class Head,class... Tail>
struct First<Head,Tail...>{
	using type=Head;
};
template<class Head,class... Tail>
struct First<pack<Head,Tail...>>{
	using type=Head;
};
template<class... Pack>
using First_t=typename First<Pack...>::type;

// Last
template<class...>
struct Last;
template<class Head,class... Tail>
struct Last<Head,Tail...>{
	using type=typename Last<Tail...>::type;
};
template<class Head,class... Tail>
struct Last<pack<Head,Tail...>>{
	using type=typename Last<Tail...>::type;
};
template<class Tail>
struct Last<Tail>{
	using type=Tail;
};
template<class... Pack>
using Last_t=typename Last<Pack...>::type;

// Pop front
template<class...>
struct PopFront;
template<class Head,class... Tail>
struct PopFront<Head,Tail...>{
	using type=Generate<Tail...>;
};
template<class Head,class... Tail>
struct PopFront<pack<Head,Tail...>>{
	using type=Generate<Tail...>;
};
template<class... Pack>
using PopFront_t=typename PopFront<Pack...>::type;

// Pop back
template<class...>
struct PopBack;
template<class Head,class... Tail>
struct PopBack<Head,Tail...>{
	using type=Concat_t<Head,typename PopBack<Tail...>::type>;
};
template<class Head,class... Tail>
struct PopBack<pack<Head,Tail...>>{
	using type=Concat_t<Head,typename PopBack<Tail...>::type>;
};
template<class Tail>
struct PopBack<Tail>{
	using type=pack<>;
};
template<class... Pack>
using PopBack_t=typename PopBack<Pack...>::type;

// Reverse
template<class... Args>
struct Reverse{
	using type=Concat_t<Last_t<Args...>,typename Reverse<PopBack_t<Args...>>::type>;
};
template<class... Args>
struct Reverse<pack<Args...>>{
	using type=Concat_t<Last_t<Args...>,typename Reverse<PopBack_t<Args...>>::type>;
};
template<>
struct Reverse<pack<>>{
	using type=pack<>;
};
template<class... Args>
using Reverse_t=typename Reverse<Args...>::type;

// PartialHead: generating half front parameter pack
template<std::size_t,class...>
struct PartialHead;
template<std::size_t N,class Head,class... Args>
struct PartialHead<N,Head,Args...>{
	using type=Concat_t<Head,typename PartialHead<N-1,Args...>::type>;
};
template<std::size_t N,class Head,class... Args>
struct PartialHead<N,pack<Head,Args...>>{
	using type=Concat_t<Head,typename PartialHead<N-1,Args...>::type>;
};
template<class Tail,class... Args>
struct PartialHead<1,Tail,Args...>{
	using type=Tail;
};
template<std::size_t N,class... Pack>
using PartialHead_t=typename PartialHead<N,Pack...>::type;

// PartialTail: generating half tail parameter pack
template<class... Args>
struct Apply_;
template<class Head,class... Tail>
struct Apply_<Head,Tail...>{
	using type=Concat_t<Head,typename Apply_<Tail...>::type>;
};
template<class Tail>
struct Apply_<Tail>{
	using type=Tail;
};
template<>
struct Apply_<>{
	using type=pack<>;
};
template<std::size_t N,class Head,class... Tail>
struct PartialTail{
	using type=typename PartialTail<N-1,Tail...>::type;
};
template<std::size_t N,class Head,class... Tail>
struct PartialTail<N,pack<Head,Tail...>>{
	using type=typename PartialHead<N-1,Tail...>::type;
};
template<class Head,class... Tail>
struct PartialTail<0,Head,Tail...>{
	using type=Concat_t<Head,typename Apply_<Tail...>::type>;
};
template<std::size_t N,class... Args>
using PartialTail_t=typename PartialTail<N,Args...>::type;

// At
template<std::size_t,class...>
struct At;
template<std::size_t index,class Head,class... Tail>
struct At<index,Head,Tail...>{
	using type=typename At<index-1,Tail...>::type;
};
template<std::size_t index,class Head,class... Tail>
struct At<index,pack<Head,Tail...>>{
	using type=typename At<index-1,Tail...>::type;
};
template<class Target,class... Tail>
struct At<0,Target,Tail...>{
	using type=Target;
};
template<std::size_t index,class... Pack>
using At_t=typename At<index,Pack...>::type;


// Transfer: apply to tuple,container etc...
template<template<class...>class,class...>
struct Transfer;
template<template<class...>class Tuple,class... Pack>
struct Transfer<Tuple,pack<Pack...>>{
	using type=Tuple<Pack...>;
};
template<template<class...>class Tuple,class... Pack>
using Transfer_t=typename Transfer<Tuple,Pack...>::type;

} // namespace srook
#endif
