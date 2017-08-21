// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_IS_ODD_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_IS_ODD_HPP
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <srook/math/constants/algorithm/isfinite.hpp>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {

template <typename T>
SROOK_FORCE_INLINE constexpr bool is_odd_unchecked(T x)
    SROOK_NOEXCEPT(math::fmod(x, T(2)) == T(1))
{
    return math::fmod(x, T(2)) == T(1);
}

} // namespace detail

template <typename FloatType, REQUIRES(std::is_floating_point<FloatType>::value)>
SROOK_FORCE_INLINE constexpr bool is_odd(FloatType x)
{
    return math::isfinite(x) and detail::is_odd_unchecked(x < 0 ? -x : x);
}

} // namespace v1
} // namespace math

using math::is_odd;

} // namespace srook
#endif
