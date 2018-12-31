// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_IS_INTEGER_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_IS_INTEGER_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/math/constants/algorithm/isfinite.hpp>
#include <srook/math/constants/algorithm/trunc.hpp>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {

template <class T>
SROOK_FORCE_INLINE constexpr bool is_integer_unchecked(T x) SROOK_NOEXCEPT(math::trunc(x))
{
    return x == math::trunc(x);
}

} // namespace detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
SROOK_FORCE_INLINE constexpr bool is_integer(FloatType x) SROOK_NOEXCEPT(math::isfinite(x) and detail::is_integer_unchecked(x))
{
    return math::isfinite(x) and detail::is_integer_unchecked(x);
}

} // namespace v1
} // namespace math

using math::is_integer;

} // namespace srook

#endif
