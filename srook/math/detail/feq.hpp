// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_DETAIL_FEQ_HPP
#define INCLUDED_SROOK_MATH_DETAIL_FEQ_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/math/config/builtin.hpp>
#include <srook/math/constants/algorithm/abs.hpp>
#include <srook/limits/numeric_limits.hpp>

SROOK_NESTED_NAMESPACE(srook, math) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <typename T>
SROOK_CONSTEXPR bool feq(T x, T y)
{
    return srook::math::abs(x - y) <= numeric_limits<T>::epsilon();
}

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(math, srook)

#endif
