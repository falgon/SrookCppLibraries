// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
/**
 * @addtogroup srook_math_primes_counting
 * @file sieve_atkin.hpp
 * @brief The prime number counter by sieve of atkin algorithm.
 * @author roki
 * @par Copyright
 * Copyright (C) 2011-2019 Roki. Distributed under the MIT License.
 */

//! @ingroup srook_math_primes_counting
//! @{

#ifndef INCLUDED_SROOK_MATH_PRIMES_COUNTING_SIEVE_ATKIN_HPP
#define INCLUDED_SROOK_MATH_PRIMES_COUNTING_SIEVE_ATKIN_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/math/primes/progression/sieve_atkin.hpp>

SROOK_NESTED_NAMESPACE(srook, math, primes, counting) {
SROOK_INLINE_NAMESPACE(v1)

/**
 * @class sieve_atkin
 * @brief sieve atkin algorithm
 */
class sieve_atkin : protected srook::math::primes::progression::sieve_atkin<> {
public:
    /**
     * @brief Given a integral number @a n, generate all primes smaller than @a n
     * @param n integer value 
     * @return The number of prime numbers smaller than @a n.
     * @exception none
     * @detail 
     *  Time complexity: O(n / \log\log n)
     *  Space complexity: O(n) 
     */
    template <class T>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<is_integral<T>::value, std::size_t>::type
    operator()(T n)
    {
        if (n < 2) return 0;
        std::size_t result = 1;
        if (n < 3) return result;
        ++result;
        if (n < 4) return result;
        
        sieve(n, [&result](T){ ++result; });
        return result;
    }
};

template <class Integral>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME std::enable_if<is_integral<Integral>::value, std::size_t>::type
compute_sieve_atkin(Integral x)
{
    return sieve_atkin()(srook::move(x));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(counting, primes, math, srook)

#endif
#endif
//! @}
