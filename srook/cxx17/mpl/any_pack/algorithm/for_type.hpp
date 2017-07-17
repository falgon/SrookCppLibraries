// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FOR_TYPE_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FOR_TYPE_HPP
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/for.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{
namespace detail{

template<std::size_t,std::size_t,template<std::size_t,class,class>class,class,class,class,class,class = std::nullptr_t> struct for_type_;

template<std::size_t begin,std::size_t end,template<std::size_t,class,class>class Invokable,class Crease,class Pred,auto... param,auto... v>
struct for_type_<begin,end,Invokable,Crease,Pred,any_pack<param...>,any_pack<v...>,std::enable_if_t<Pred()(begin,end),std::nullptr_t>>{
private:
	using inner_type = typename Invokable<begin,any_pack<v...>,any_pack<param...>>::type;
public:
	using type = concat_t<inner_type,typename for_type_<Crease()(begin),end,Invokable,Crease,Pred,any_pack<param...>,any_pack<v...>>::type>;
};
template<std::size_t begin,std::size_t end,template<std::size_t,class,class>class Invokable,class Crease,class Pred,auto... param,auto... v>
struct for_type_<begin,end,Invokable,Crease,Pred,any_pack<param...>,any_pack<v...>,std::enable_if_t<!Pred()(begin,end),std::nullptr_t>>{
	using type = any_pack<>;
};

template<
	std::size_t begin,
	std::size_t end,
	template<std::size_t,class,class>class Invokable,
	class Crease = std::conditional_t<(begin < end),Increment,Decrement>,
	class Parameter = any_pack<>,
	class Seq = any_pack<>,
	std::enable_if_t<std::is_invocable_v<Crease,std::size_t>,std::nullptr_t> = nullptr
>
using for_type_to_t = 
	std::conditional_t<
		(for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq>::type::size() == Seq::size()),
		typename for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq>::type,
		std::conditional_t<
			(begin < end),
			typename for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq>::type::template concat_type<
				typename Seq::template partial_tail_type<for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq>::type::size()>
			>,
			typename for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq>::type::template concat_type<
				typename Seq::template partial_head_type<for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq>::type::size()>
			>
		>
	>;


template<
	std::size_t begin,
	std::size_t end,
	template<std::size_t,class,class>class Invokable,
	class Crease = std::conditional_t<(begin < end),Increment,Decrement>,
	class Parameter = any_pack<>,
	class Seq = any_pack<>,
	std::enable_if_t<std::is_invocable_v<Crease,std::size_t>,std::nullptr_t> = nullptr
>
using for_type_until_t = 
	std::conditional_t<
		(for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq>::type::size() == Seq::size()),
		typename for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq>::type,
		std::conditional_t<
			(begin < end),
			typename for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq>::type::template concat_type<
				typename Seq::template partial_tail_type<for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq>::type::size()>
			>,
			typename for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq>::type::template concat_type<
				typename Seq::template partial_head_type<for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq>::type::size()>
			>
		>
	>;

template<
	std::size_t begin,
	std::size_t end,
	template<std::size_t,class,class>class Invokable,
	class Crease = std::conditional_t<(begin < end),Increment,Decrement>,
	class Parameter = any_pack<>,
	class Seq = any_pack<>,
	std::enable_if_t<std::is_invocable_v<Crease,std::size_t>,std::nullptr_t> = nullptr
>
using for_type_cut_to_t = typename for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less_or_equal,Greater_or_equal>,Parameter,Seq>::type;

template<
	std::size_t begin,
	std::size_t end,
	template<std::size_t,class,class>class Invokable,
	class Crease = std::conditional_t<(begin < end),Increment,Decrement>,
	class Parameter = any_pack<>,
	class Seq = any_pack<>,
	std::enable_if_t<std::is_invocable_v<Crease,std::size_t>,std::nullptr_t> = nullptr
>
using for_type_cut_until_t = typename for_type_<begin,end,Invokable,Crease,std::conditional_t<(begin < end),Less,Greater>,Parameter,Seq>::type;


} // namespace detail
} // inline namespace v1
} // inlnie namespace mpl 
} // namespace srook

#endif
