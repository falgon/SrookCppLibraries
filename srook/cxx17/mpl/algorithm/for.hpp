// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FOR_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FOR_HPP
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<srook/cxx17/mpl/any_pack/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{
namespace detail{

struct Increment{
	explicit constexpr Increment() noexcept = default;
	template<class T>
	constexpr T operator()(T&& v)const noexcept{return v + 1;}
};

struct Decrement{
	explicit constexpr Decrement() noexcept = default;
	template<class T>
	constexpr T operator()(T&& v)const noexcept{return v - 1;}
};

struct Less{
	explicit constexpr Less() noexcept = default;
	template<class T>
	constexpr bool operator()(T&& l,T&& r)const noexcept{return l < r;}
};
struct Greater{
	explicit constexpr Greater() noexcept = default;
	template<class T>
	constexpr bool operator()(T&& l,T&& r)const noexcept{return l > r;}
};
struct Less_or_equal{
	explicit constexpr Less_or_equal() noexcept = default;
	template<class T>
	constexpr bool operator()(T&& l,T&& r)const noexcept{return l <= r;}
};
struct Greater_or_equal{
	explicit constexpr Greater_or_equal() noexcept = default;
	template<class T>
	constexpr bool operator()(T&& l,T&& r)const noexcept{return l >= r;}
};

template<std::size_t,std::size_t,template<std::size_t,class,class,class>class,class,class,class,class,class,class = std::nullptr_t> struct for_;

template<std::size_t begin,std::size_t end,template<std::size_t,class,class,class>class Invokable,class Crease,class Pred,auto... param,auto... v,class... Ts>
struct for_<begin,end,Invokable,Crease,Pred,any_pack<param...>,any_pack<v...>,pack<Ts...>,std::enable_if_t<Pred()(begin,end),std::nullptr_t>>{
private:
	using inner_type = any_pack<Invokable<begin,any_pack<v...>,any_pack<param...>,pack<Ts...>>::value>;
public:
	using type = concat_t<inner_type,typename for_<Crease()(begin),end,Invokable,Crease,Pred,any_pack<param...>,any_pack<v...>,pack<Ts...>>::type>;
};
template<std::size_t begin,std::size_t end,template<std::size_t,class,class,class>class Invokable,class Crease,class Pred,auto... param,auto... v,class... Ts>
struct for_<begin,end,Invokable,Crease,Pred,any_pack<param...>,any_pack<v...>,pack<Ts...>,std::enable_if_t<!Pred()(begin,end),std::nullptr_t>>{
	using type = any_pack<>;
};

template<
	std::size_t begin,
	std::size_t end,
	template<std::size_t,class,class,class>class Invokable,
	class Crease = std::conditional_t<(begin < end),Increment,Decrement>,
	class Parameter = any_pack<>,
	class Seq = any_pack<>,
	class TPack = pack<>,
	std::enable_if_t<std::is_invocable_v<Crease,std::size_t>,std::nullptr_t> = nullptr
>
using for_to_t = 
	std::conditional_t<
		(for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq,TPack>::type::size() == Seq::size()),
		typename for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq,TPack>::type,
		std::conditional_t<
			(begin < end),
			typename for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq,TPack>::type::template concat_type<
				typename Seq::template partial_tail_type<for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq,TPack>::type::size()>
			>,
			typename for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq,TPack>::type::template concat_type<
				typename Seq::template partial_head_type<for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq,TPack>::type::size()>
			>
		>
	>;


template<
	std::size_t begin,
	std::size_t end,
	template<std::size_t,class,class,class>class Invokable,
	class Crease = std::conditional_t<(begin < end),Increment,Decrement>,
	class Parameter = any_pack<>,
	class Seq = any_pack<>,
	class TPack = pack<>,
	std::enable_if_t<std::is_invocable_v<Crease,std::size_t>,std::nullptr_t> = nullptr
>
using for_until_t = 
	std::conditional_t<
		(for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq,TPack>::type::size() == Seq::size()),
		typename for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq,TPack>::type,
		std::conditional_t<
			(begin < end),
			typename for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq,TPack>::type::template concat_type<
				typename Seq::template partial_tail_type<for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq,TPack>::type::size()>
			>,
			typename for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq,TPack>::type::template concat_type<
				typename Seq::template partial_head_type<for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq,TPack>::type::size()>
			>
		>
	>;

template<
	std::size_t begin,
	std::size_t end,
	template<std::size_t,class,class,class>class Invokable,
	class Crease = std::conditional_t<(begin < end),Increment,Decrement>,
	class Parameter = any_pack<>,
	class Seq = any_pack<>,
	class TPack = pack<>,
	std::enable_if_t<std::is_invocable_v<Crease,std::size_t>,std::nullptr_t> = nullptr
>
using for_cut_to_t = typename for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq,TPack>::type;

template<
	std::size_t begin,
	std::size_t end,
	template<std::size_t,class,class,class>class Invokable,
	class Crease = std::conditional_t<(begin < end),Increment,Decrement>,
	class Parameter = any_pack<>,
	class Seq = any_pack<>,
	class TPack = pack<>,
	std::enable_if_t<std::is_invocable_v<Crease,std::size_t>,std::nullptr_t> = nullptr
>
using for_cut_until_t = typename for_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq,TPack>::type;


} // namespace detail
} // inline namespace v1
} // inlnie namespace mpl 
} // namespace srook

#endif
