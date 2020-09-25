// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CHRONO_CLOCK_RDTSCP_CLOCK_HPP
#define INCLUDED_SROOK_CHRONO_CLOCK_RDTSCP_CLOCK_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/chrono/intrinsic/rdtsc.hpp>
#include <srook/type_traits/clock/is_trivial_clock.hpp>
#include <chrono>

SROOK_NESTED_NAMESPACE(srook, chrono, clock) {
SROOK_INLINE_NAMESPACE(v1)

class rdtscp_clock {
public:
    typedef srook::uint64_t rep;
    typedef std::ratio<1> period;
    typedef std::chrono::duration<rep, period> duration;
    typedef std::chrono::time_point<rdtscp_clock, duration> time_point;

    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_steady = true;

    static SROOK_FORCE_INLINE time_point now() SROOK_NOEXCEPT_TRUE
    {
        return time_point(duration(srook::chrono::intrinsic::rdtscp()));
    }
private:
    SROOK_ST_ASSERT(is_trivial_clock<rdtscp_clock>::value);
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(clock, chrono, srook)

#endif
#endif
