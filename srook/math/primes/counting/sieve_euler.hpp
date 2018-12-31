// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
/**
 * @addtogroup srook_math_primes_counting
 * @file sieve_euler.hpp
 * @brief The prime number generator by sieve of eratosthenese algorithm in O(N) time complexity
 * @author roki
 * @par Copyright
 * Copyright (C) 2011-2019 Roki. Distributed under the MIT License.
 */

//! @ingroup srook_math_primes_counting
//! @{

#ifndef INCLUDED_SROOK_MATH_PRIMES_COUNTING_SIEVE_EULER_HPP
#define INCLUDED_SROOK_MATH_PRIMES_COUNTING_SIEVE_EULER_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/math/constants/algorithm/log.hpp>
#include <srook/math/primes/counting/legendre.hpp>
#include <cmath>
#include <vector>

SROOK_NESTED_NAMESPACE(srook, math, primes, counting) {
SROOK_INLINE_NAMESPACE(v1)

/**
 * @class sieve_euler
 * @brief sieve eratosthenese algorithm
 */

class sieve_euler {
public:
    /**
     * @brief Given a integral number @a n, count all primes smaller than @a n
     * @param n integer value 
     * @return The number of prime numbers smaller than @a n.
     * @exception none
     * @detail 
     *  Time complexity: O(n)
     *  Space complexity: O(n) 
     */
    template <class T>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<is_integral<T>::value, std::size_t>::type
    operator()(T n)
    {
        if (n < 2) return 0;
        return sieve(n);
    }
private:
    template <class T>
    SROOK_FORCE_INLINE std::size_t sieve(T n)
    {
        std::vector<T> rs;
        rs.reserve(static_cast<std::size_t>(srook::math::primes::counting::legendre_compute(n)));
        std::vector<bool> is_prime(n, true);
        is_prime[0].flip(); is_prime[1].flip();
        std::vector<T> smallest_fp(n); // store smallest prime factor of number 
        std::size_t res = 0;

        for (std::size_t i = 2; i < static_cast<std::size_t>(n); ++i) {
            if (is_prime[i]) {
                ++res;
                rs.push_back(static_cast<T>(i));
                smallest_fp[i] = static_cast<T>(i);
            }
            for (std::size_t j = 0; j < rs.size() && static_cast<std::size_t>(i * rs[j]) < static_cast<std::size_t>(n) && rs[j] <= smallest_fp[i]; ++j) {
                is_prime[i * rs[j]] = false;
                smallest_fp[i * rs[j]] = rs[j];
            }
        }
        return res;
    }
}; 

template <class Integral>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME std::enable_if<is_integral<Integral>::value, std::size_t>::type
compute_sieve_euler(Integral x)
{
    return sieve_euler()(srook::move(x));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(counting, primes, math, srook)

#endif
#endif
//! @}
