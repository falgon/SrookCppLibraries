// Copyright (C) Roki 2017
#ifndef INCLUDED_ANY_PACK_TEST_HPP
#define INCLUDED_ANY_PACK_TEST_HPP

#include<srook/mpl/variadic_player.hpp>
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<srook/cxx17/mpl/any_pack/algorithm/at.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/binary_search.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/count.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/count_if.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/equal.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/erase_all_elements.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/erase_at.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/erase_elements.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/erase_if_elements.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/erase_if_all_elements.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/filter.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/find_if.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/find_index.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/first.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/for.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/for_type.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/last.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/make_any_pack.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/make_index_sequence.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/partial_head.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/partial_tail.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/pop_back.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/pop_front.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/replace_elements.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/reverse.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/sort.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/transfer.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/unique.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{
	
	template<auto l,auto r> using less = std::integral_constant<bool,(l<r)>;
  	template<auto l,auto r> using greater = std::integral_constant<bool,!less<l,r>::value>;
  	template<auto l,auto r> using less_or_equal = std::integral_constant<bool,(l<=r)>;
  	template<auto l,auto r> using greater_or_equal = std::integral_constant<bool,(l>=r)>;

  	template<auto... v>
  	struct any_pack{
  		static constexpr std::size_t size(){return sizeof...(v);}
  		static constexpr std::conditional_t<!size(),std::nullopt_t,First_t<decltype(v)...>> first = detail::first_v<v...>;
  		static constexpr std::conditional_t<!size(),std::nullopt_t,Last_t<decltype(v)...>> last = detail::last_v<v...>;

  		template<std::size_t target>
  		static constexpr std::conditional_t<!size(),std::nullopt_t,At_t<target,decltype(v)...>> at(){return detail::at_v<target,v...>;}

	  	template<class T> using concat_type = detail::concat_t<any_pack<v...>,T>;
  		template<auto... ov> using concat_value = detail::concat_t<any_pack<v...>,any_pack<ov...>>;
  		using pop_front_type = detail::pop_front_t<v...>;
  		using pop_back_type = detail::pop_back_t<v...>;
  		template<std::size_t index> using erase_at_type = detail::erase_at_t<index,v...>;
  		template<auto target> using erase_elements_type = detail::erase_elements_t<target,v...>;
  		template<auto target> using erase_all_elements_type = detail::erase_all_elements_t<target,v...>;
  		template<template<auto>class Predicate> using erase_if_elements_type = detail::erase_if_elements_t<Predicate,v...>;
  		template<template<auto>class Predicate> using erase_if_all_elements_type = detail::erase_if_all_elements_t<Predicate,v...>;
  		template<template<auto>class Cond> using filter_elements = detail::filter_t<Cond,any_pack<v...>>;
  		template<template<auto,auto>class Comp=less> using sort_type = detail::sort_t<any_pack<v...>,Comp>;
  		using unique_type = detail::unique_t<v...>;
  		template<auto replace_element,auto target> using replace_elements_type = detail::replace_elements_t<replace_element,target+1,v...>;
  		template<std::size_t index> using partial_head_type = detail::partial_head_t<index,v...>;
  		template<std::size_t index> using partial_tail_type = detail::partial_tail_t<index,v...>;
  		using reverse_type = detail::reverse_t<v...>;
  		template<auto target> static constexpr std::size_t count = detail::count_v<target,v...>;
  		template<template<auto>class Predicate> static constexpr std::size_t count_if = detail::count_if_v<Predicate,v...>;
  		template<template<auto>class Predicate> static constexpr int find_if = detail::find_if_v<Predicate,v...>;
  		template<auto target> static constexpr int find_index = detail::find_index_v<target,v...>;
  		template<auto target> static constexpr bool binary_search = detail::binary_search_v<target,v...>;

  		struct Nothing{
  			explicit constexpr Nothing()=default;
  			template<class T>
  			constexpr T& operator()(T&& t)const noexcept{return t;}
  		};

  		template<template<class...>class Range> static decltype(detail::transfer<Range,v...>::value) range;
  		template<template<class...>class ConstantRange,class Transformer = Nothing>
  		static constexpr std::enable_if_t<std::is_invocable_v<Transformer,First_t<decltype(v)...>>,ConstantRange<std::decay_t<decltype(Transformer()(v))>...>> constant_range{Transformer()(v)...};
  		template<class AnyPack> static constexpr bool equal_pack = detail::equal_v<any_pack<v...>,AnyPack>;
  		template<auto... other> static constexpr bool equal_value = detail::equal_v<any_pack<v...>,any_pack<other...>>;
  		using pack_type = srook::pack<decltype(v)...>;
  		template<std::size_t size,auto init_value> using make_any_pack = detail::make_any_pack_t<size,init_value,any_pack<v...>>;
  		template<std::size_t n> using make_index_sequence = detail::make_index_sequence<n,any_pack<v...>>;
  		template<std::size_t begin,std::size_t end,template<std::size_t,class,class>class Applyer,class Parameter = any_pack<>,class Crease = std::conditional_t<(begin < end),detail::Increment,detail::Decrement>> using for_to = detail::for_to_t<begin,end,Applyer,Crease,Parameter,any_pack<v...>>;
  		template<std::size_t begin,std::size_t end,template<std::size_t,class,class>class Applyer,class Parameter = any_pack<>,class Crease = std::conditional_t<(begin < end),detail::Increment,detail::Decrement>> using for_until = detail::for_until_t<begin,end,Applyer,Crease,Parameter,any_pack<v...>>;
  		template<std::size_t begin,std::size_t end,template<std::size_t,class,class>class Applyer,class Parameter = any_pack<>,class Crease = std::conditional_t<(begin < end),detail::Increment,detail::Decrement>> using for_cut_to = detail::for_cut_to_t<begin,end,Applyer,Crease,Parameter,any_pack<v...>>;
  		template<std::size_t begin,std::size_t end,template<std::size_t,class,class>class Applyer,class Parameter = any_pack<>,class Crease = std::conditional_t<(begin < end),detail::Increment,detail::Decrement>> using for_cut_until = detail::for_cut_until_t<begin,end,Applyer,Crease,Parameter,any_pack<v...>>;
		
  		template<std::size_t begin,std::size_t end,template<std::size_t,class,class>class Applyer,class Parameter = any_pack<>,class Crease = std::conditional_t<(begin < end),detail::Increment,detail::Decrement>> using for_type_to = detail::for_type_to_t<begin,end,Applyer,Crease,Parameter,any_pack<v...>>;
  		template<std::size_t begin,std::size_t end,template<std::size_t,class,class>class Applyer,class Parameter = any_pack<>,class Crease = std::conditional_t<(begin < end),detail::Increment,detail::Decrement>> using for_type_until = detail::for_type_until_t<begin,end,Applyer,Crease,Parameter,any_pack<v...>>;
  		template<std::size_t begin,std::size_t end,template<std::size_t,class,class>class Applyer,class Parameter = any_pack<>,class Crease = std::conditional_t<(begin < end),detail::Increment,detail::Decrement>> using for_type_cut_to = detail::for_type_cut_to_t<begin,end,Applyer,Crease,Parameter,any_pack<v...>>;
  		template<std::size_t begin,std::size_t end,template<std::size_t,class,class>class Applyer,class Parameter = any_pack<>,class Crease = std::conditional_t<(begin < end),detail::Increment,detail::Decrement>> using for_type_cut_until = detail::for_type_cut_until_t<begin,end,Applyer,Crease,Parameter,any_pack<v...>>;
  	};

  	template<auto... v>
  	template<template<class...>class Range>
  	decltype(detail::transfer<Range,v...>::value) any_pack<v...>::range{detail::transfer<Range,v...>::value};

} // inline namespace v1
} // inline namespace mpl
} // namespace srook

#endif
