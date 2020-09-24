// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_NUMERIC_FIXED_POINT_TYPEDEFS_HPP
#define INCLUDED_SROOK_NUMERIC_FIXED_POINT_TYPEDEFS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/numeric/fixed_point/fixed_point.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_ALIAS_TEMPLATES
SROOK_NESTED_NAMESPACE(srook, numeric) {
SROOK_INLINE_NAMESPACE(v1)

template <std::size_t I, std::size_t F, SROOK_REQUIRES(I + F == 8)>
using fixed8_t = srook::numeric::fixed_point<I, F>;

template <std::size_t I, std::size_t F, SROOK_REQUIRES(I + F == 16)>
using fixed16_t = srook::numeric::fixed_point<I, F>;

template <std::size_t I, std::size_t F, SROOK_REQUIRES(I + F == 32)>
using fixed32_t = srook::numeric::fixed_point<I, F>;

template <std::size_t I, std::size_t F, SROOK_REQUIRES(I + F == 64)>
using fixed64_t = srook::numeric::fixed_point<I, F>;

#if defined(SROOK_HAS_INT128) && !defined(__STRICT_ANSI__)
template <std::size_t I, std::size_t F, SROOK_REQUIRES(I + F == 128)>
using fixed128_t = srook::numeric::fixed_point<I, F>;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(numeric, srook)

namespace srook {

using srook::numeric::fixed8_t;
using srook::numeric::fixed16_t;
using srook::numeric::fixed32_t;
using srook::numeric::fixed64_t;
#if defined(SROOK_HAS_INT128) && !defined(__STRICT_ANSI__)
using srook::numeric::fixed128_t;
#endif

} // namespace srook
#endif
#endif
