// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CHRONO_CEIL_HPP
#define INCLUDED_SROOK_CHRONO_CEIL_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT && SROOK_HAS_INCLUDE(<chrono>)
#    define SROOK_HAS_LIB_STD_CHRONO_CEIL 1
#endif
#if SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
#    define SROOK_HAS_LIB_BOOST_CHRONO_CEIL 1
#elif SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>)
#    define SROOK_HAS_LIB_BOOST_CHRONO_CEIL 1
#endif

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature.hpp>
#include <srook/config/require.hpp>
#include <srook/type_traits/is_duration.hpp>

namespace srook {
namespace chrono {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_LIB_STD_CHRONO
template <class To, class Rep, class Period, SROOK_REQUIRES(is_duration<To>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
To ceil(const std::chrono::duration<Rep, Period>& d)
{
#    if SROOK_HAS_LIB_STD_CHRONO_CEIL
    return std::chrono::ceil<To>(d);
#    else
    const To t = std::chrono::duration_cast<To>(d);
    return t < d ? t + To(1) : t;
#    endif
}

template <class To, class Clock, class FromDuration, SROOK_REQUIRES(is_duration<To>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
std::chrono::time_point<Clock, To> ceil(const std::chrono::time_point<Clock, FromDuration>& tp)
{
    return
#    if SROOK_HAS_LIB_STD_CHRONO_CEIL
        std::chrono::ceil<To>(tp)
#    else
        std::chrono::time_point<Clock, To>{ceil<To>(tp.time_since_epoch())}
#    endif
    ;
}
#endif

#if SROOK_HAS_LIB_BOOST_CHRONO
template <class To, class Rep, class Period, SROOK_REQUIRES(is_duration<To>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
To ceil(const boost::chrono::duration<Rep, Period>& d)
{
#    if SROOK_HAS_LIB_BOOST_CHRONO_CEIL
    return boost::chrono::ceil<To>(d) +
#    else
    To t = boost::chrono::duration_cast<To>(d);
    return t < d ? t + To(1) : t;
#    endif
}

template <class To, class Clock, class FromDuration, SROOK_REQUIRES(is_duration<To>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
boost::chrono::time_point<Clock, To> ceil(const boost::chrono::time_point<Clock, FromDuration>& tp)
{
    return
#    if SROOK_HAS_LIB_BOOST_CHRONO_CEIL
        boost::chrono::ceil<To>(tp)
#    else
        boost::chrono::time_point<Clock, To>{ceil<To>(tp.time_since_epoch())}
#    endif
    ;
}
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace chrono
} // namespace srook

#endif
