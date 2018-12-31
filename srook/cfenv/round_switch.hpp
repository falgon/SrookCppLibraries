// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CFENV_ROUND_SWITCH_HPP
#define INCLUDED_SROOK_CFENV_ROUND_SWITCH_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/cfenv/config.hpp>
#include <srook/cstdfloat.hpp>
#include <srook/cstdint.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/is_floating_point.hpp>
#include <srook/type_traits/add_volatile.hpp>
#include <srook/scope/unique_resource.hpp>
#include <limits>
#if SROOK_OS_IS_WIN32 || defined(_WIN64)
#   include <emmintrin.h>
#endif

SROOK_NESTED_NAMESPACE(srook, cfenv) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {
    
class round_switch_impl {
public:
    enum mxcsr : srook::uint32_t {
        daz     = 0x00000040, imask     = 0x00000080, dmask     = 0x00000100,
        zmask   = 0x00000200, omask     = 0x00000400, umask     = 0x00000800,
        pmask   = 0x00001000, rnearest  = 0x00000000, rdown     = 0x00002000,
        rup     = 0x00004000, r2ward0   = 0x00006000, flash20   = 0x00008000
    };
#ifdef _MSC_VER
#   if defined(_WIN64) || _M_IX86_FP == 2
private:
    SROOK_FORCE_INLINE static void to_nearest_msimpl()             SROOK_NOEXCEPT_TRUE { _mm_setcsr(_mm_getcsr() & (~r2ward0)); }
    SROOK_FORCE_INLINE static void toward_zero_msimpl()            SROOK_NOEXCEPT_TRUE { _mm_setcsr(_mm_getcsr() | r2ward0); }
    SROOK_FORCE_INLINE static void toward_infinity_msimpl()        SROOK_NOEXCEPT_TRUE { _mm_setcsr((_mm_getcsr() & (~r2ward0)) | rup); }
    SROOK_FORCE_INLINE static void toward_neg_infinity_msimpl()    SROOK_NOEXCEPT_TRUE { _mm_setcsr((_mm_getcsr() & (~r2ward0)) | rdown); }
public:
#   endif
#   ifdef _WIN32
private:
    template <class BitCompute, SROOK_REQUIRES(is_same<SROOK_DEDUCED_TYPENAME invoke_result<BitCompute, srook::uint16_t>::type, srook::uint16_t>::value)>
    SROOK_FORCE_INLINE static void apply_setting(BitCompute compute)
    {
        srook::uint16_t mode;
        _asm { fnstcw mode }
        mode = compute(mode);
        _asm { fldcw mode }
    }
public:
#   endif
#   ifdef _WIN64
    SROOK_FORCE_INLINE static void to_nearest()             SROOK_NOEXCEPT_TRUE { to_nearest_msimpl(); }
    SROOK_FORCE_INLINE static void toward_zero()            SROOK_NOEXCEPT_TRUE { torward_zero_msimpl(); }
    SROOK_FORCE_INLINE static void toward_infinity()        SROOK_NOEXCEPT_TRUE { to_ward_infinity_msimpl(); }
    SROOK_FORCE_INLINE static void toward_neg_infinity()    SROOK_NOEXCEPT_TRUE { toward_neg_infinity_msimpl(); }
#   elif defined(_WIN32)
    SROOK_FORCE_INLINE static void to_nearest() SROOK_NOEXCEPT_TRUE
    {
        struct set2near {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint16_t 
            operator()(srook::uint16_t mode) const SROOK_NOEXCEPT_TRUE { return mode & ~0x0c00; }
        };
        apply_setting(set2near());
#       if _M_IX86_FP == 2
        to_nearest_msimpl();
#       endif
    }
    SROOK_FORCE_INLINE static void toward_zero() SROOK_NOEXCEPT_TRUE
    {
        struct set2ward_zero {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint16_t
            operator()(srook::uint16_t mode) const SROOK_NOEXCEPT_TRUE { return mode | 0x0c00; }
        };
        apply_setting(set2ward_zero());
#       if _M_IX86_FP == 2
        toward_zero_msimpl();
#       endif
    }
    SROOK_FORCE_INLINE static void toward_infinity() SROOK_NOEXCEPT_TRUE
    {
        struct set2ward_inf {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint16_t
            operator()(srook::uint16_t mode) const SROOK_NOEXCEPT_TRUE { return (mode & ~0x0c00) | 0x0800; }
        };
        apply_setting(set2ward_inf());
#       if _M_IX86_FP == 2
        toward_infinity_msimpl();
#       endif
    }
    SROOK_FORCE_INLINE static void toward_neg_infinity() SROOK_NOEXCEPT_TRUE
    {
        struct set2ward_neg_inf {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint16_t
            operator()(srook::uint16_t mode) const SROOK_NOEXCEPT_TRUE { return (mode & ~0x0c00) | 0x0400; }
        };
        apply_setting(set2ward_inf());
#       if _M_IX86_FP == 2
        toward_neg_infinity_msimpl();
#       endif
    }
#   else
    SROOK_FORCE_INLINE void to_nearest()            SROOK_NOEXCEPT_TRUE { _controlfp(_RC_NEAR, _MCW_RC); }
    SROOK_FORCE_INLINE void toward_zero()           SROOK_NOEXCEPT_TRUE { _controlfp(_RC_CHOP, _MCW_RC); }
    SROOK_FORCE_INLINE void toward_infinity()       SROOK_NOEXCEPT_TRUE { _controlfp(_RC_UP, _MCW_RC); }
    SROOK_FORCE_INLINE void toward_neg_infinity()   SROOK_NOEXCEPT_TRUE { _controlfp(_RC_DOWN, _MCW_RC); }
#   endif
#elif defined(__GNUC__)
#   if defined(__x86_64__) || defined(__SSE2_MATH__)
private:
    template <class BitCompute, SROOK_REQUIRES(is_same<SROOK_DEDUCED_TYPENAME invoke_result<BitCompute, srook::uint32_t>::type, srook::uint32_t>::value)>
    SROOK_FORCE_INLINE static void apply_setting(BitCompute compute) SROOK_NOEXCEPT_TRUE
    {
        srook::uint32_t mode;
        __asm__ __volatile__ ("stmxcsr %0":"=m"(mode));
        mode = compute(mode);
        __asm__ __volatile__ ("ldmxcsr %0"::"m"(mode));
    }
    SROOK_FORCE_INLINE static void to_nearest_uniximpl() SROOK_NOEXCEPT_TRUE
    {
        struct set2near {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint32_t 
            operator()(srook::uint32_t mode) const SROOK_NOEXCEPT_TRUE { return mode & ~r2ward0; }
        };
        apply_setting(set2near());
    }
    SROOK_FORCE_INLINE static void toward_zero_uniximpl() SROOK_NOEXCEPT_TRUE
    {
        struct set2ward_zero {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint32_t
            operator()(srook::uint32_t mode) const SROOK_NOEXCEPT_TRUE { return mode | r2ward0; }
        };
        apply_setting(set2ward_zero());
    }
    SROOK_FORCE_INLINE static void toward_infinity_uniximpl() SROOK_NOEXCEPT_TRUE
    {
        struct set2ward_inf {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint32_t
            operator()(srook::uint32_t mode) const SROOK_NOEXCEPT_TRUE { return (mode & ~r2ward0) | rup; }
        };
        apply_setting(set2ward_inf());
    }
    SROOK_FORCE_INLINE static void toward_neg_infinity_uniximpl() SROOK_NOEXCEPT_TRUE
    {
        struct set2ward_neg_inf {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint32_t
            operator()(srook::uint32_t mode) const SROOK_NOEXCEPT_TRUE { return (mode & ~r2ward0) | rdown; }
        };
        apply_setting(set2ward_neg_inf());
    }
public:
#   endif
#   ifdef __x86_64__
    SROOK_FORCE_INLINE static void to_nearest()             SROOK_NOEXCEPT_TRUE { to_nearest_uniximpl(); }
    SROOK_FORCE_INLINE static void toward_zero()            SROOK_NOEXCEPT_TRUE { toward_zero_uniximpl(); }
    SROOK_FORCE_INLINE static void toward_infinity()        SROOK_NOEXCEPT_TRUE { toward_infinity_uniximpl(); }
    SROOK_FORCE_INLINE static void toward_neg_infinity()    SROOK_NOEXCEPT_TRUE { toward_neg_infinity_uniximpl(); }
#   elif defined(__i386__)
private:
    template <class BitCompute, SROOK_REQUIRES(is_same<SROOK_DEDUCED_TYPENAME invoke_result<BitCompute, srook::uint16_t>::type, srook::uint16_t>::value)>
    SROOK_FORCE_INLINE static void apply_setting32(BitCompute compute) SROOK_NOEXCEPT_TRUE
    {
        srook::uint16_t mode;
        __asm__ __volatile__ ("fnstcw %0":"=m"(mode));
        mode = compute(mode);
        __asm__ __volatile__ ("fldcw %0"::"m"(mode));
    }
public:
    SROOK_FORCE_INLINE static void to_nearest() SROOK_NOEXCEPT_TRUE
    {
        struct set2near {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint16_t
            operator()(srook::uint16_t mode) const SROOK_NOEXCEPT_TRUE { return mode & ~0x0c00; }
        };
        apply_setting32(set2near());
#       if defined(__SSE2_MATH__)
        to_nearest_uniximpl();
#       endif
    }
    SROOK_FORCE_INLINE static void toward_zero() SROOK_NOEXCEPT_TRUE
    {
        struct set2ward_zero {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint16_t
            operator()(srook::uint16_t mode) const SROOK_NOEXCEPT_TRUE { return mode | 0x0c00; }
        };
        apply_setting32(set2ward_zero());
#       if defined(__SSE2_MATH__)
        toward_zero_uniximpl();
#       endif
    }
    SROOK_FORCE_INLINE static void toward_infinity() SROOK_NOEXCEPT_TRUE
    {
        struct set2ward_inf {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint16_t
            operator()(srook::uint16_t mode) const SROOK_NOEXCEPT_TRUE { return (mode & ~0x0c00) | 0x0800; }
        };
        apply_setting32(set2ward_inf());
#       if defined(__SSE2_MATH__)
        toward_infinity_uniximpl();
#       endif
    }
    SROOK_FORCE_INLINE static void toward_neg_infinity() SROOK_NOEXCEPT_TRUE
    {
        struct set2ward_neg_inf {
            SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::uint16_t
            operator()(srook::uint16_t mode) const SROOK_NOEXCEPT_TRUE { return (mode & ~0x0c00) | 0x0400; }
        };
        apply_setting32(set2ward_neg_inf());
#       if defined(__SSE2_MATH__)
        toward_neg_infinity_uniximpl();
#       endif
    }
#else
    SROOK_FORCE_INLINE static void to_nearest()            SROOK_NOEXCEPT_TRUE { std::fesetround(FE_TONEAREST); }
    SROOK_FORCE_INLINE static void toward_zero()           SROOK_NOEXCEPT_TRUE { std::fesetround(FE_DOWNWARD); }
    SROOK_FORCE_INLINE static void toward_infinity()       SROOK_NOEXCEPT_TRUE { std::fesetround(FE_UPWARD); }
    SROOK_FORCE_INLINE static void toward_neg_infinity()   SROOK_NOEXCEPT_TRUE { std::fesetround(FE_TOWARDZERO); }
#   endif
#else
#   error This environment is not supported.
#endif
};

template <class FloatingPoint, bool = is_floating_point<FloatingPoint>::value>
struct block_optimize : add_volatile<FloatingPoint> {};

template <class FloatingPoint>
struct block_optimize<FloatingPoint, false> {
    // if this block is instantiated, the below static_assert will always fire.
    SROOK_STATIC_ASSERT((is_same<FloatingPoint, float>::value), "srook::cfenv::round_switch::enable_round: The type must be floating point type");
};

} // namespace detail

class round_switch : public srook::cfenv::detail::round_switch_impl {
    struct scoped_round_switcher {
        SROOK_FORCE_INLINE void operator()(std::float_round_style af) const SROOK_NOEXCEPT_TRUE { set(af); }
    };
public:
    template <class FloatingPoint>
    struct enable_round {
        typedef SROOK_DEDUCED_TYPENAME detail::block_optimize<FloatingPoint>::type type;
    };
        
    SROOK_FORCE_INLINE static void set(std::float_round_style frs) SROOK_NOEXCEPT_TRUE
    {
        switch (frs) {
            case std::round_toward_zero: 
                toward_zero(); 
                break;
            case std::round_to_nearest:
                to_nearest();
                break;
            case std::round_toward_infinity:
                toward_infinity();
                break;
            case std::round_toward_neg_infinity:
                toward_neg_infinity();
                break;
            case std::round_indeterminate: 
                SROOK_ATTRIBUTE_FALLTHROUGH;
            default:
                return;
        }
    }

    template <class Fn, class... Args>
    SROOK_FORCE_INLINE static SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<Fn>::type, Args&&...>::type
    scoped_set(std::float_round_style inscope, std::float_round_style after, Fn&& fn, Args&&... args) 
    SROOK_NOEXCEPT(is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<Fn>::type, Args&&...>::value)
    {
        set(srook::move(inscope));
        SROOK_ATTRIBUTE_UNUSED srook::scope::unique_resource<std::float_round_style, scoped_round_switcher> resource(srook::move(after), scoped_round_switcher());
        return fn(srook::forward<Args>(args)...);
    }

    SROOK_FORCE_INLINE static srook::scope::unique_resource<std::float_round_style, scoped_round_switcher> 
    make_scoped(std::float_round_style inscope, std::float_round_style after = std::round_to_nearest) 
    SROOK_NOEXCEPT(is_nothrow_constructible<srook::scope::unique_resource<std::float_round_style, scoped_round_switcher>>::value)
    {
        set(srook::move(inscope));
        return srook::scope::make_unique_resource(srook::move(after), scoped_round_switcher());
    }
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(cfenv, srook)

#endif
