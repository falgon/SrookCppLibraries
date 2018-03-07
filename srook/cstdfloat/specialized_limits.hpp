// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CSTDFLOAT_SPECIALIZED_LIMITS_HPP
#define INCLUDED_SROOK_CSTDFLOAT_SPECIALIZED_LIMITS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/cstdfloat/type.hpp>
#if defined(SROOK_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T) && defined(SROOK_HAS_FLOAT128)
#   include <srook/limits/numeric_limits.hpp>
#   ifdef __INTEL_COMPILER
#       define SROOK_CSTDFLOAT_FLOAT128_SQRT __sqrtq
#   elif defined(__GNUC__)
#       define SROOK_CSTDFLOAT_FLOAT128_SQRT sqrtq
#   endif

extern "C" srook::intrinsic_types::float128_t SROOK_CSTDFLOAT_FLOAT128_SQRT(srook::intrinsic_types::float128_t) SROOK_NOEXCEPT_TRUE;

namespace srook {

template <>
class numeric_limits<srook::intrinsic_types::float128_t> {
public:
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool is_specialized = true;
    static srook::intrinsic_types::float128_t (min)() SROOK_NOEXCEPT_TRUE { return SROOK_CSTDFLOAT_FLOAT128_MIN; }
    static srook::intrinsic_types::float128_t (max)() SROOK_NOEXCEPT_TRUE { return SROOK_CSTDFLOAT_FLOAT128_MAX; }
    static srook::intrinsic_types::float128_t lowest() SROOK_NOEXCEPT_TRUE { return -(max)(); }
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR int digits = 113;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR int digits10 = 33;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR int max_digits10 = 36;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool is_signed = true;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool is_integer = false;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool is_exact = false;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR int radix = 2;
    static srook::intrinsic_types::float128_t epsilon() { return SROOK_CSTDFLOAT_FLOAT128_EPS; }
    static srook::intrinsic_types::float128_t round_error() { return SROOK_FLOAT_128_C(0.5); }
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR int min_exponent = -16381;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR int min_exponent10 = static_cast<int>((min_exponent * 301L) / 1000L);
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR int max_exponent = +16384;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR int max_exponent10 = static_cast<int>((max_exponent * 301L) / 1000L);
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool has_infinity = true;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool has_quiet_NaN = true;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool has_signaling_NaN = true;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::float_denorm_style has_denorm = std::denorm_absent;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool has_denorm_loss = false;
    static srook::intrinsic_types::float128_t infinity() { return SROOK_FLOAT_128_C(1.0) / SROOK_FLOAT_128_C(0.0); }
    static srook::intrinsic_types::float128_t quiet_NaN() { return ::SROOK_CSTDFLOAT_FLOAT128_SQRT(SROOK_FLOAT_128_C(-1.0)); }
    static srook::intrinsic_types::float128_t signaling_NaN() { return SROOK_FLOAT_128_C(0.0); }
    static srook::intrinsic_types::float128_t denorm_min() { return SROOK_FLOAT_128_C(0.0); }
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool is_iec559 = true;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool is_bounded = false;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool is_modulo = false;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool traps = false;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool tinyless_before = false;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::float_round_style round_style = std::round_to_nearest;
};

} // namespace srook
#endif
#endif
