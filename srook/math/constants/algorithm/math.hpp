// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_HPP

#include<srook/math/constants/pi.hpp>

namespace srook{
namespace math{

	static constexpr std::size_t end_term = 10;
	static constexpr double fmod(double l,double r)noexcept{return l - static_cast<int>(l / r) * r;}
	static constexpr double fabs(double x)noexcept{return x < 0 ? -x : x;}
	static constexpr double factorial(double x)noexcept{return x == 0 ? 1 : factorial(x - 1) * x;}
	static constexpr double power(double l,double r)noexcept{return r == 0 ? 1 : power(l,r - 1) * l;}
	static constexpr double sin_term(double l,double r)noexcept{return r == end_term * 2 - 1 ? power(l,r) / factorial(r) : power(l,r) / factorial(r) - sin_term(l,r + 2);}
	static constexpr double sin_convert(double x)noexcept{return fabs(x) > pi<double> / 2 ? sin_term(fmod(pi<double> - x,pi<double>) * static_cast<int>(x * 2 / pi<double>),1) : sin_term(x,1);}
	static constexpr double sin(double x)noexcept{return static_cast<int>(x / pi<double>) % 2 == 0 ? sin_convert(fmod(x,pi<double>)) : - sin_convert(fmod(x,pi<double>));}
	static constexpr double cos(double x)noexcept{return fmod(x,pi<double> * 2) == pi<double> / 2 ? 0 : sin(x + pi<double> / 2);}
	static constexpr double tan(double x)noexcept{return sin(x) / cos(x);}

} // namespace math
} // namespace srook

#endif
