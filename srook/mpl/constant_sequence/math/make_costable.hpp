#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_MATH_MAKE_COSTABLE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_MATH_MAKE_COSTABLE_HPP
#include<srook/math/constants/algorithm/cos.hpp>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>
#include<srook/mpl/constant_sequence/algorithm/transfer_constant.hpp>

namespace srook {
inline namespace mpl {
namespace constant_sequence {
namespace math{
inline namespace v1 {

namespace detail {
constexpr std::int64_t to_integer = 10000000000000000;

template<std::size_t i,std::size_t j>
constexpr double cos_value = srook::math::cos((2 * j + 1) * i * (srook::math::pi<double> / 16));

template<std::size_t,std::size_t,class> struct make_costable_y_impl;
template<std::size_t i,std::size_t j,std::int64_t... v>
struct make_costable_y_impl<i,j,std::integer_sequence<std::int64_t,v...>>{
	using type = typename make_costable_y_impl<i,j - 1,std::integer_sequence<std::int64_t,std::int64_t(cos_value<i,j> * to_integer),v...>>::type;
};
template<std::size_t i,std::int64_t... v>
struct make_costable_y_impl<i,0,std::integer_sequence<std::int64_t,v...>>{
	using type = std::integer_sequence<std::int64_t,std::int64_t(cos_value<i,0> * to_integer),v...>;
};
template<std::size_t x,std::size_t y,class Pack = std::integer_sequence<std::int64_t>>
using make_costable_y = typename make_costable_y_impl<x,y,Pack>::type;

template<std::size_t,std::size_t,class> struct make_costable_x_impl;
template<std::size_t i,std::size_t j,std::int64_t... v>
struct make_costable_x_impl<i,j,std::integer_sequence<std::int64_t,v...>>{
	using type = typename make_costable_x_impl<i - 1,j,constant_sequence::concat_t<make_costable_y<i,j>,std::integer_sequence<std::int64_t,v...>>>::type;
};
template<std::size_t j,std::int64_t... v>
struct make_costable_x_impl<0,j,std::integer_sequence<std::int64_t,v...>>{
	using type = constant_sequence::concat_t<make_costable_y<0,j>,std::integer_sequence<std::int64_t,v...>>;
};
template<std::size_t x,std::size_t y,class Pack = std::integer_sequence<std::int64_t>>
using make_costable_x = typename make_costable_x_impl<x - 1,y - 1,Pack>::type;

struct Realvalue{
	explicit constexpr Realvalue() = default;

	template<class T>
	constexpr double operator()(T&& v)
	{
		return double(v) / to_integer;
	}
};

} // namespace detail

template<std::size_t x,std::size_t y>
constexpr decltype(auto) cos_table = constant_sequence::transfer_constant<std::tuple,std::int64_t,detail::make_costable_x<x,y>,detail::Realvalue>;


} // inline namespace v1
} // namespace math
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook

#endif
