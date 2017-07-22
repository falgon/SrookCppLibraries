// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_RUN_LENGTH_HPP
#define INCLUDED_SROOK_CXX17_MPL_RUN_LENGTH_HPP
#include<srook/cxx17/mpl/any_pack/any_pack.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{

namespace detail{

template<std::size_t,auto,class> struct search_length;
template<std::size_t counter,auto search,auto... tail>
struct search_length<counter,search,any_pack<search,tail...>>{
	static constexpr std::size_t value=search_length<counter+1,search,any_pack<tail...>>::value;
	using type=typename search_length<counter+1,search,any_pack<tail...>>::type;
};
template<std::size_t counter,auto search,auto head,auto... tail>
struct search_length<counter,search,any_pack<head,tail...>>{
	static constexpr std::size_t value=counter;
	using type=any_pack<search,counter>;
};
template<std::size_t counter,auto search>
struct search_length<counter,search,any_pack<>>{
	static constexpr std::size_t value=counter;
	using type=any_pack<search,counter>;
};
template<auto search,class Anypack>
using search_length_t=typename search_length<0,search,Anypack>::type;
template<auto search,class Anypack>
constexpr std::size_t search_length_v=search_length<0,search,Anypack>::value;

template<class> struct run_length_impl;
template<auto head,auto... tail>
struct run_length_impl<any_pack<head,tail...>>{
private:
	using length_type=search_length_t<head,any_pack<head,tail...>>;
	static constexpr std::size_t length_value=search_length_v<head,any_pack<head,tail...>>;
public:
	using type=
		detail::concat_t<
			std::conditional_t<(length_value>1),length_type,any_pack<head>>,
			typename run_length_impl< std::conditional_t<(length_value>1),typename any_pack<head,tail...>::template partial_tail_type<length_value>,any_pack<tail...>>>::type
		>;
};
template<>
struct run_length_impl<any_pack<>>{
	using type=any_pack<>;
};

} // inline namespace v1
} // inline namespace mpl
} // namespace detail

template<class Anypack>
using run_length=typename detail::run_length_impl<Anypack>::type;

} // namespace srook

#endif
