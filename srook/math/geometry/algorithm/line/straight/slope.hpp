// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_GEOMETORY_ALGORITHM_LINE_STRAIGHT_SLOPE_HPP
#define INCLUDED_SROOK_MATH_GEOMETORY_ALGORITHM_LINE_STRAIGHT_SLOPE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/math/geometry/fundamental/theta.hpp>
#include <srook/math/geometry/fundamental/point.hpp>
#include <srook/math/constants/algorithm/tan.hpp>

SROOK_NESTED_NAMESPACE(srook, math, geometry, algorithm, line, straight) {
SROOK_INLINE_NAMESPACE(v1)

struct slope {
    template <class T>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR static T 
    m(const srook::math::geometry::fundamental::theta<T>& th) SROOK_NOEXCEPT_TRUE
    {
        return srook::math::tan(th);
    }

    template <class T>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR static T
    m(const srook::math::geometry::fundamental::point<T>& p1, const srook::math::geometry::fundamental::point<T>& p2) SROOK_NOEXCEPT_TRUE
    {
        return (p2.y() - p1.y()) / (p2.x() - p1.x());
    }
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(straight, line, algorithm, geometry, srook)

#endif
