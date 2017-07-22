// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_PI_HPP
#define INCLUDED_SROOK_MATH_PI_HPP
#include<type_traits>
#include<cmath>

namespace srook{
namespace math{

template<class> struct PI_;

template<class T>
struct PI_{
	static constexpr T value()
	{
		static_assert(std::is_arithmetic<T>::value,"This type is not supported");
		return T(M_PI);
	}
};

template<class T>
static constexpr T pi = PI_<T>::value();


} // namespace math
} // namespace srook

#endif
