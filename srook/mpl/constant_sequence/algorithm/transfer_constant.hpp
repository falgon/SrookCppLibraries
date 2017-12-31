// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_ALGORITHM_TRANSFER_CONSTANT_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_ALGORITHM_TRANSFER_CONSTANT_HPP

#include<type_traits>
#include<utility>
#include<srook/type_traits/is_callable.hpp>
#include<srook/config/require.hpp>
#include<srook/mpl/variadic_player.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

namespace detail{

struct DoNothing{
	explicit constexpr DoNothing() = default;
	template<class T>
	constexpr T operator()(T&& v)const noexcept
	{
		return v;
	}
};

template<template<class...>class,class,class,class,class = std::nullptr_t>
struct transfer_constant_impl;

template<template<class...>class ConstantRange,class ValueTp,ValueTp... seq,class Applyer>
struct transfer_constant_impl<ConstantRange,ValueTp,std::integer_sequence<ValueTp,seq...>,Applyer,std::enable_if_t<srook::is_callable_v<std::decay_t<Applyer>>,std::nullptr_t>>{
	static constexpr ConstantRange<decltype(Applyer()(seq))...> value{Applyer()(seq)...};
};

} // namespace detail

template<template<class...>class ConstantRange,class ValueTp,class Seq,class Applyer = detail::DoNothing>
static constexpr decltype(auto) transfer_constant = detail::transfer_constant_impl<ConstantRange,ValueTp,Seq,Applyer>::value;


} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook

#endif
