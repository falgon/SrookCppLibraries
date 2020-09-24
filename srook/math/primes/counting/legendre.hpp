// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
/**
 * @addtogroup srook_math_primes_counting
 * @file legendre.hpp
 * @brief The prime number counting function by Legendre (1808)
 * @author roki
 * @par Copyright
 * Copyright (C) 2011-2019 Roki. Distributed under the MIT License.
 */
//! @ingroup srook_math_primes_counting
//! @{
#ifndef INCLUDED_SROOK_MATH_PRIMES_COUNTING_LEGENDRE_HPP
#define INCLUDED_SROOK_MATH_PRIMES_COUNTING_LEGENDRE_HPP

#ifndef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/math/constants/algorithm/log.hpp>

SROOK_NESTED_NAMESPACE(srook, math, primes, counting) {
SROOK_INLINE_NAMESPACE(v1)

/**
 * @struct legendre
 * @brief the Legendre(1808)'s wrapper structure
 */
template <class Integral>
struct legendre {
private:
    SROOK_ST_ASSERT(is_integral<Integral>::value);
public:
    typedef Integral value_type;

    //! Legendre's constant
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR value_type A = 1;
    //! Legendre's constant
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR float B = -1.08366;

    /**
     * @brief Use the prime number theorem by Legendre (1808) to get an approximation of the number of prime numbers smaller than @a x.
     * @param x integer value
     * @return the approximation of the number of prime numbers smaller than @a x.
     * @exception none
     */
    static SROOK_FORCE_INLINE SROOK_CONSTEXPR Integral compute(value_type x) SROOK_NOEXCEPT_TRUE
    {
        return x / (A * srook::math::log(x) + B);
    }
};

/**
 * @brief Use the prime number theorem by Legendre (1808) to get an approximation of the number of prime numbers smaller than @a x.
 * @param x integer value
 * @return the approximation of the number of prime numbers smaller than @a x.
 * @exception none
 */
template <class Integral>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<is_integral<Integral>::value, Integral>::type
legendre_compute(Integral x)
{
    return legendre<Integral>::compute(x);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(counting, primes, math, srook)

#endif
