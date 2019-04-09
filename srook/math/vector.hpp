// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_VECTOR_HPP
#define INCLUDED_SROOK_MATH_VECTOR_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/math/linear_algebra/vector.hpp>

SROOK_NESTED_NAMESPACE(srook, math) {
SROOK_INLINE_NAMESPACE(v1)

using srook::math::linear_algebra::vector;
using srook::math::linear_algebra::make_vector;

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(math, srook)

#endif
