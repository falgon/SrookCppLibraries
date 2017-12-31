// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MATH_MAKE_COSINE_TABLE_HPP
#define INCLUDED_SROOK_CXX17_MATH_MAKE_COSINE_TABLE_HPP

#include<srook/math/constants/algorithm/math.hpp>
#include<srook/cxx17/mpl/any_pack/any_pack.hpp>
#include<srook/mpl/make_same_type_sequence.hpp>
#include<srook/mpl/variadic_player.hpp>

namespace srook{
namespace math{
inline namespace v1{
namespace detail{

constexpr std::int64_t to_integer = 10000000000000000;

template<std::size_t i,std::size_t j>
constexpr double cos_value = srook::math::cos((2 * j + 1) * i * (srook::math::pi<double> / 16));

template<std::size_t,std::size_t,class> struct make_costable_y_impl;
template<std::size_t i,std::size_t j,std::int64_t... v>
struct make_costable_y_impl<i,j,srook::any_pack<v...>>{
	using type = typename make_costable_y_impl<i,j-1,srook::any_pack<std::int64_t(cos_value<i,j> * to_integer),v...>>::type;
};
template<std::size_t i,std::int64_t... v>
struct make_costable_y_impl<i,0,srook::any_pack<v...>>{
	using type = srook::any_pack<std::int64_t(cos_value<i,0> * to_integer),v...>;
};
template<std::size_t x,std::size_t y,class Pack=srook::any_pack<>>
using make_costable_y = typename make_costable_y_impl<x,y,Pack>::type;


template<std::size_t,std::size_t,class> struct make_costable_x_impl;
template<std::size_t i,std::size_t j,std::int64_t... v>
struct make_costable_x_impl<i,j,srook::any_pack<v...>>{
	using type = typename make_costable_x_impl<i-1,j,typename make_costable_y<i,j>::template concat_type<srook::any_pack<v...>>>::type;
};
template<std::size_t j,std::int64_t... v>
struct make_costable_x_impl<0,j,srook::any_pack<v...>>{
	using type = typename make_costable_y<0,j>::template concat_type<srook::any_pack<v...>>;
};
template<std::size_t x,std::size_t y,class Pack=srook::any_pack<>>
using make_costable_x = typename make_costable_x_impl<x-1,y-1,Pack>::type;

struct Realvalue{
	explicit constexpr Realvalue()=default;
	
	template<class T>
	constexpr double operator()(T&& v)
	{
		return static_cast<double>(v) / to_integer;
	}
};

} // namespace detail

template<std::size_t x,std::size_t y,template<class...>class Tuple = std::tuple>
constexpr decltype(auto) cos_table = detail::make_costable_x<x,y>::template constant_range<Tuple,detail::Realvalue>;

} // inline namespace v1
} // namespace math
} // namespace srook

#endif
