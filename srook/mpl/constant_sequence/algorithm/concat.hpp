// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_CONCAT_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_CONCAT_HPP
#include<type_traits>
#include<utility>
#include<srook/utility/integer_sequence.hpp>
#include<srook/config/compiler.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class,class>
struct concat;

template<class L,L...l,class R,R... r>
struct concat<srook::integer_sequence<L,l...>,srook::integer_sequence<R,r...>>{
	static_assert(std::is_convertible<L,R>::value,"Two types are not convertible");
	using type = srook::integer_sequence<typename std::common_type<L,R>::type,l...,r...>;
};

#ifndef SROOK_IS_CXX11_EARLIER
template<class L,L... l,class R,R... r>
struct concat<std::integer_sequence<L,l...>,std::integer_sequence<R,r...>>{
	static_assert(std::is_convertible<L,R>::value,"Two types are not convertible");
	using type = std::integer_sequence<typename std::common_type<L,R>::type,l...,r...>;
};
template<class L,class R>
using concat_t = typename concat<L,R>::type;
#endif

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
