#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_HPP
#include<srook/mpl/variadic_player.hpp>
#include<tuple>
#if __has_include(<optional>)
#include<optional>
#define NULLOPT std::nullopt
#define NULLOPT_T std::nullopt_t
#elif __has_include(<boost/optional.hpp>)
#include<boost/optional.hpp>
#define NULLOPT boost::none
#define NULLOPT_T boost::none_t
#endif

namespace srook{
inline namespace mpl{
inline namespace v1{

template<auto...>
struct any_pack;

namespace detail{

template<auto...>
struct first;
template<auto head,auto... tail>
struct first<head,tail...>{
	static constexpr decltype(head) value=head;
};
template<>
struct first<>{
	static constexpr NULLOPT_T value=NULLOPT;
};
template<auto... v>
constexpr std::conditional_t<!sizeof...(v),NULLOPT_T,First_t<decltype(v)...>> first_v=first<v...>::value;

template<auto...>
struct last;
template<auto head,auto... tail>
struct last<head,tail...>{
	static constexpr Last_t<decltype(tail)...> value=last<tail...>::value;
};
template<auto tail>
struct last<tail>{
	static constexpr decltype(tail) value=tail;
};
template<>
struct last<>{
	static constexpr NULLOPT_T value=NULLOPT;
};
template<auto... v>
constexpr std::conditional_t<!sizeof...(v),NULLOPT_T,Last_t<decltype(v)...>> last_v=last<v...>::value;

template<std::size_t,auto...>
struct at;
template<std::size_t index,auto head,auto... tail>
struct at<index,head,tail...>{
	static constexpr auto value=at<index-1,tail...>::value;
};
template<auto head,auto... tail>
struct at<0,head,tail...>{
	static constexpr decltype(head) value=head;
};
template<std::size_t target>
struct at<target>{
	static constexpr NULLOPT_T value=NULLOPT;
};
template<std::size_t n,auto... v>
constexpr std::conditional_t<!sizeof...(v),NULLOPT_T,At_t<n,decltype(v)...>> at_v=at<n,v...>::value;

template<class,class>
struct concat;
template<auto... l,auto... r>
struct concat<any_pack<l...>,any_pack<r...>>{
	using type=any_pack<l...,r...>;
};
template<class L,class R>
using concat_t=typename concat<L,R>::type;

template<auto...>
struct pop_front;
template<auto head,auto... tail>
struct pop_front<head,tail...>{
	using type=any_pack<tail...>;
};
template<>
struct pop_front<>{
	using type=NULLOPT_T;
};
template<auto... v>
using pop_front_t=typename pop_front<v...>::type;

template<auto...>
struct pop_back;
template<auto head,auto... tail>
struct pop_back<head,tail...>{
	using type=concat_t<any_pack<head>,typename pop_back<tail...>::type>;
};
template<auto tail>
struct pop_back<tail>{
	using type=any_pack<>;
};
template<>
struct pop_back<>{
	using type=NULLOPT_T;
};
template<auto... v>
using pop_back_t=typename pop_back<v...>::type;

template<std::size_t,auto...>
struct erase_at;
template<std::size_t n,auto head,auto... tail>
struct erase_at<n,head,tail...>{
	using type=concat_t<any_pack<head>,typename erase_at<n-1,tail...>::type>;
};
template<auto target,auto... tail>
struct erase_at<0,target,tail...>{
	using type=any_pack<tail...>;
};
template<std::size_t target,auto... v>
using erase_at_t=typename erase_at<target,v...>::type;

template<auto,auto...>
struct erase_elements;
template<auto target,auto head,auto... tail>
struct erase_elements<target,head,tail...>{
	using type=concat_t<any_pack<head>,typename erase_elements<target,tail...>::type>;
};
template<auto target,auto... tail>
struct erase_elements<target,target,tail...>{
	using type=any_pack<tail...>;
};
template<auto target>
struct erase_elements<target>{
	using type=any_pack<>;
};
template<auto target,auto... v>
using erase_elements_t=typename erase_elements<target,v...>::type;

template<auto,auto...>
struct erase_all_elements;
template<auto target,auto head,auto... tail>
struct erase_all_elements<target,head,tail...>{
	using type=concat_t<any_pack<head>,typename erase_all_elements<target,tail...>::type>;
};
template<auto target,auto... tail>
struct erase_all_elements<target,target,tail...>{
	using type=typename erase_all_elements<target,tail...>::type;
};
template<auto target>
struct erase_all_elements<target>{
	using type=any_pack<>;
};
template<auto target,auto... v>
using erase_all_elements_t=typename erase_all_elements<target,v...>::type;

template<bool,template<auto>class,auto...>
struct erase_if_elements_impl;
template<template<auto>class Predicate,auto head,auto... tail>
struct erase_if_elements_impl<true,Predicate,head,tail...>{
	using type=any_pack<tail...>;
};
template<template<auto>class Predicate,auto head,auto second,auto... tail>
struct erase_if_elements_impl<false,Predicate,head,second,tail...>{
	using type=concat_t<any_pack<head>,typename erase_if_elements_impl<Predicate<second>::value,Predicate,second,tail...>::type>;
};
template<bool b,template<auto>class Predicate,auto tail>
struct erase_if_elements_impl<b,Predicate,tail>{
	using tyep=std::conditional_t<b,any_pack<>,any_pack<tail>>;
};
template<template<auto>class,auto...>
struct erase_if_elements;
template<template<auto>class Predicate,auto head,auto... tail>
struct erase_if_elements<Predicate,head,tail...>{
	using type=typename erase_if_elements_impl<Predicate<head>::value,Predicate,head,tail...>::type;
};
template<template<auto>class Predicate,auto... v>
using erase_if_elements_t=typename erase_if_elements<Predicate,v...>::type;

template<template<auto>class,auto...>
struct erase_if_all_elements;
template<template<auto>class Predicate,auto head,auto... tail>
struct erase_if_all_elements<Predicate,head,tail...>{
	using type=concat_t<std::conditional_t<Predicate<head>::value,any_pack<>,any_pack<head>>,typename erase_if_all_elements<Predicate,tail...>::type>;
};
template<template<auto>class Predicate>
struct erase_if_all_elements<Predicate>{
	using type=any_pack<>;
};
template<template<auto>class Predicate,auto... v>
using erase_if_all_elements_t=typename erase_if_all_elements<Predicate,v...>::type;

template<template<auto>class,class>
struct filter;
template<template<auto>class Cond,auto head,auto... tail>
struct filter<Cond,any_pack<head,tail...>>{
private:
	template<bool,class,class>
	struct if_append;
	template<auto... seq1,auto... seq2>
	struct if_append<true,any_pack<seq1...>,any_pack<seq2...>>{
		using type=any_pack<seq1...,seq2...>;
	};
	template<auto... seq1,auto... seq2>
	struct if_append<false,any_pack<seq1...>,any_pack<seq2...>>{
		using type=any_pack<seq2...>;
	};
	template<bool condition,class Seq1,class Seq2>
	using if_append_t=typename if_append<condition,Seq1,Seq2>::type;
public:
	using type=if_append_t<Cond<head>::value,any_pack<head>,typename filter<Cond,any_pack<tail...>>::type>;
};
template<template<auto>class Cond>
struct filter<Cond,any_pack<>>{
	using type=any_pack<>;
};
template<template<auto>class Cond,class Seq>
using filter_t=typename filter<Cond,Seq>::type;

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
	using lcomp=Comp<lhs,pivot>;
	template<auto rhs>
	using rcomp=not_<lcomp,rhs>;
public:
	using type=
		concat_t<
			typename sort<Comp,filter_t<lcomp,any_pack<tail...>>>::type,
			concat_t<any_pack<pivot>,filter_t<rcomp,any_pack<tail...>>>
		>;
};
template<template<auto,std::size_t>class Comp>
struct sort<Comp,any_pack<>>{
	    using type=any_pack<>;
};
template<class Sequence,template<auto,auto>class Comp>
using sort_t=typename sort<Comp,Sequence>::type;

template<template<class...>class Range,auto... v>
struct transfer{
	static Range<std::decay_t<decltype(first_v<v...>)>> value;
};
template<template<class...>class Range,auto... v>
Range<std::decay_t<decltype(first_v<v...>)>> transfer<Range,v...>::value{v...};

template<auto... v>
struct transfer<std::tuple,v...>{
	static std::tuple<std::decay_t<decltype(v)>...> value;
};
template<auto... v>
std::tuple<std::decay_t<decltype(v)>...> transfer<std::tuple,v...>::value{v...};

template<class>
struct unique;
template<auto head,auto... tail>
struct unique<any_pack<head,tail...>>{
	using type=concat_t<any_pack<head>,typename unique<erase_all_elements_t<head,tail...>>::type>;
};
template<>
struct unique<any_pack<>>{
	using type=any_pack<>;
};
template<auto... v>
using unique_t=typename unique<any_pack<v...>>::type;

template<class,class>
struct equal;
template<auto l_head,auto... l_tail,auto r_head,auto... r_tail>
struct equal<any_pack<l_head,l_tail...>,any_pack<r_head,r_tail...>>{
	static constexpr bool value=std::conditional_t<l_head==r_head,equal<any_pack<l_tail...>,any_pack<r_tail...>>,std::false_type>::value;
};
template<>
struct equal<any_pack<>,any_pack<>>:std::true_type{};
template<class L,class R>
constexpr bool equal_v=std::conditional_t<L::size()==R::size(),equal<L,R>,std::false_type>::value;

template<auto,auto,auto...>
struct replace_elements;
template<auto replace_element,auto target,auto head,auto... tail>
struct replace_elements<replace_element,target,head,tail...>{
	using type=concat_t<any_pack<head>,typename replace_elements<replace_element,target,tail...>::type>;
};
template<auto replace_element,auto target,auto... tail>
struct replace_elements<replace_element,target,target,tail...>{
	using type=concat_t<any_pack<replace_element>,typename replace_elements<replace_element,target,tail...>::type>;
};
template<auto replace_element,auto target>
struct replace_elements<replace_element,target>{
	using type=any_pack<>;
};
template<auto replace_element,auto target,auto... v>
using replace_elements_t=typename replace_elements<replace_element,target,v...>::type;

template<std::size_t,class>
struct partial_head;
template<std::size_t target,auto head,auto... tail>
struct partial_head<target,any_pack<head,tail...>>{
	    using type=concat_t<any_pack<head>,typename partial_head<target-1,any_pack<tail...>>::type>;
};
template<auto tail,auto... args>
struct partial_head<1,any_pack<tail,args...>>{
	    using type=any_pack<tail>;
};
template<std::size_t target,auto... v>
using partial_head_t=typename partial_head<target,any_pack<v...>>::type;

template<std::size_t,class>
struct partial_tail;
template<std::size_t target,auto head,auto... tail>
struct partial_tail<target,any_pack<head,tail...>>{
	using type=typename partial_tail<target-1,any_pack<tail...>>::type;
};
template<auto head,auto... t>
struct partial_tail<0,any_pack<head,t...>>{
	using type=any_pack<head,t...>;
};
template<std::size_t index,auto... v>
using partial_tail_t=typename partial_tail<index,any_pack<v...>>::type;

template<class>
struct reverse;
template<auto... v>
struct reverse<any_pack<v...>>{
	using type=concat_t<any_pack<last_v<v...>>,typename reverse<pop_back_t<v...>>::type>;
};
template<>
struct reverse<any_pack<>>{
	using type=any_pack<>;
};
template<auto... v>
using reverse_t=typename reverse<any_pack<v...>>::type;

template<int,template<auto>class,auto...>
struct find_if;
template<int counter,template<auto>class Predicate,auto head,auto... tail>
struct find_if<counter,Predicate,head,tail...>{
	static constexpr int value=std::conditional_t<Predicate<head>::value,std::integral_constant<int,counter>,find_if<counter+1,Predicate,tail...>>::value;
};
template<int counter,template<auto>class Predicate>
struct find_if<counter,Predicate>{
	static constexpr int value=-counter-1;
};
template<template<auto>class Predicate,auto... v>
constexpr int find_if_v=find_if<0,Predicate,v...>::value;

template<std::size_t,auto,auto...>
struct find_index;
template<std::size_t counter,auto target,auto head,auto... tail>
struct find_index<counter,target,head,tail...>{
	static constexpr int value=find_index<counter+1,target,tail...>::value;
};
template<std::size_t counter,auto target,auto... tail>
struct find_index<counter,target,target,tail...>{
	static constexpr int value=counter;
};
template<std::size_t counter,auto target>
struct find_index<counter,target>{
	static constexpr int value=-1;
};
template<std::size_t target,auto... v>
constexpr int find_index_v=find_index<0,target,v...>::value;

template<auto,class> struct binary_search;
template<auto target,auto... v>
struct binary_search<target,any_pack<v...>>{
private:
	static constexpr At_t<sizeof...(v)/2,decltype(v)...> half_value=any_pack<v...>::template at<sizeof...(v)/2>();
	using head_inner=binary_search<target,typename any_pack<v...>::template partial_head_type<(sizeof...(v)/2)>>;
	using tail_inner=binary_search<target,typename any_pack<v...>::template partial_tail_type<(sizeof...(v)/2)>>;
public:
	static constexpr bool value=std::conditional_t<(target == half_value),std::true_type,std::conditional_t<(half_value > target),head_inner,tail_inner>>::value;
};
template<auto target,auto l1,auto l2>
struct binary_search<target,any_pack<l1,l2>>{
	static constexpr bool value=target==l1 or target==l2;
};
template<auto target,auto l>
struct binary_search<target,any_pack<l>>{
	static constexpr bool value=target==l;
};
template<auto target>
struct binary_search<target,any_pack<>>:std::false_type{};
template<auto target,auto... v>
constexpr bool binary_search_v=binary_search<target,any_pack<v...>>::value;

template<auto,auto...> struct count;
template<auto target,auto head,auto... tail>
struct count<target,head,tail...>{
	static constexpr std::size_t value=std::conditional_t<(target==head),std::true_type,std::false_type>::value+count<target,tail...>::value;
};
template<auto target>
struct count<target>{
	static constexpr std::size_t value=0;
};
template<auto target,auto... v>
constexpr std::size_t count_v=count<target,v...>::value;

template<template<auto>class,auto...> struct count_if;
template<template<auto>class Predicate,auto head,auto... tail>
struct count_if<Predicate,head,tail...>{
	static constexpr std::size_t value=std::conditional_t<Predicate<head>::value,std::true_type,std::false_type>::value+count_if<Predicate,tail...>::value;
};
template<template<auto>class Predicate>
struct count_if<Predicate>{
	static constexpr std::size_t value=0;
};
template<template<auto>class Predicate,auto... v>
constexpr std::size_t count_if_v=count_if<Predicate,v...>::value;


} // namespace detail

template<auto l,auto r> using less=std::integral_constant<bool,(l<r)>;
template<auto l,auto r> using greater=std::integral_constant<bool,!less<l,r>::value>;
template<auto l,auto r> using less_or_equal=std::integral_constant<bool,(l<=r)>;
template<auto l,auto r> using greater_or_equal=std::integral_constant<bool,(l>=r)>;

template<auto... v>
struct any_pack{
	static constexpr std::size_t size(){return sizeof...(v);}
	
	static constexpr std::conditional_t<!size(),NULLOPT_T,First_t<decltype(v)...>> first=detail::first_v<v...>;
	static constexpr std::conditional_t<!size(),NULLOPT_T,Last_t<decltype(v)...>> last=detail::last_v<v...>;
	
	template<std::size_t target>
	static constexpr std::conditional_t<!size(),NULLOPT_T,At_t<target,decltype(v)...>> at(){return detail::at_v<target,v...>;}

	template<class T>
	using concat_type=detail::concat_t<any_pack<v...>,T>;
	template<auto... ov>
	using concat_value=detail::concat_t<any_pack<v...>,any_pack<ov...>>;
	using pop_front_type=detail::pop_front_t<v...>;
	using pop_back_type=detail::pop_back_t<v...>;
	template<std::size_t index>
	using erase_at_type=detail::erase_at_t<index,v...>;
	template<auto target>
	using erase_elements_type=detail::erase_elements_t<target,v...>;
	template<auto target>
	using erase_all_elements_type=detail::erase_all_elements_t<target,v...>;
	template<template<auto>class Predicate>
	using erase_if_elements_type=detail::erase_if_elements_t<Predicate,v...>;
	template<template<auto>class Predicate>
	using erase_if_all_elements_type=detail::erase_if_all_elements_t<Predicate,v...>;
	template<template<auto>class Cond>
	using filter_elements=detail::filter_t<Cond,any_pack<v...>>;
	template<template<auto,auto>class Comp=less>
	using sort_type=detail::sort_t<any_pack<v...>,Comp>;
	using unique_type=detail::unique_t<v...>;
	template<auto replace_element,auto target>
	using replace_elements_type=detail::replace_elements_t<replace_element,target,v...>;
	template<std::size_t index>
	using partial_head_type=detail::partial_head_t<index,v...>;
	template<std::size_t index>
	using partial_tail_type=detail::partial_tail_t<index,v...>;
	using reverse_type=detail::reverse_t<v...>;
	template<auto target>
	static constexpr std::size_t count=detail::count_v<target,v...>;
	template<template<auto>class Predicate>
	static constexpr std::size_t count_if=detail::count_if_v<Predicate,v...>;

	template<template<auto>class Predicate>
	static constexpr int find_if=detail::find_if_v<Predicate,v...>;
	template<auto target>
	static constexpr int find_index=detail::find_index_v<target,v...>;

	template<auto target>
	static constexpr bool binary_search=detail::binary_search_v<target,v...>;

	template<template<class...>class Range>
	static decltype(detail::transfer<Range,v...>::value) range;

	template<class AnyPack>
	static constexpr bool equal_pack=detail::equal_v<any_pack<v...>,AnyPack>;
	template<auto... other>
	static constexpr bool equal_value=detail::equal_v<any_pack<v...>,any_pack<other...>>;
};
template<auto... v>
template<template<class...>class Range>
decltype(detail::transfer<Range,v...>::value) any_pack<v...>::range{detail::transfer<Range,v...>::value};


} // inline namespace v1
} // inlnie namespace mpl 
} // namespace srook

#ifdef NULLOPT
#undef NULLOPT
#endif
#ifdef NULLOPT_T
#undef NULLOPT_T
#endif
#endif
