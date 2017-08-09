// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_SQRT_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_SQRT_HPP
#include<limits>

namespace srook{
namespace math{
inline namespace v1{

namespace detail{

constexpr double sqrt_aux(double x,double c,double prev)
{
	        return c == prev ? c : sqrt_aux(x,(c + x / c) * 0.5,c);
}

} // namespace detail
} // inline namespace v1

constexpr double sqrt(double x){return x >= 0 and x < std::numeric_limits<double>::infinity() ? detail::sqrt_aux(x,x,0) : std::numeric_limits<double>::quiet_NaN();}

} // namespace math
} // namespace srook
#endif
