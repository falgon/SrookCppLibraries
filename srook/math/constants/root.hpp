// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ROOT_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ROOT_HPP
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>

namespace srook {
namespace math {
inline namespace v1 {

template <typename T>
SROOK_FORCE_INLINE constexpr T root_two() SROOK_NOEXCEPT_TRUE
{
    return static_cast<T>(1.41421356237309504880168872420969807856967187537694807317667973799073247846210703885038753432764157273501384623L);
}

template <typename T>
SROOK_FORCE_INLINE constexpr T root_three() SROOK_NOEXCEPT_TRUE
{
    return static_cast<T>(1.73205080756887729352744634150587236694280525381038062805580697945193301690880003708114618675724857567562614142L);
}

template <typename T>
SROOK_FORCE_INLINE constexpr T half_root_two() SROOK_NOEXCEPT_TRUE
{
    return static_cast<T>(0.707106781186547524400844362104849039284835937688474036588339868995366239231053519425193767163820786367506923115L);
}

} // namespace v1
} // namespace math
} // namespace srook

#endif
