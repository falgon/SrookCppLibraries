// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_NUMERIC_DETAIL_FIXED_POINT_FIXED_POINT_DECLARE_HPP
#define INCLUDED_SROOK_NUMERIC_DETAIL_FIXED_POINT_FIXED_POINT_DECLARE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>

SROOK_NESTED_NAMESPACE(srook, numeric) {
SROOK_INLINE_NAMESPACE(v1)

template <std::size_t, std::size_t>
class fixed_point;

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(numeric, srook)

#endif
