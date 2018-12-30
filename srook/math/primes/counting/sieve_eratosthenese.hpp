// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
/**
 * @addtogroup srook_math_primes_counting
 * @file sieve_eratosthenese.hpp
 * @brief The prime number counter by sieve of eratosthenese algorithm.
 * @author roki
 * @par Copyright
 * Copyright (C) 2011-2019 Roki. Distributed under the MIT License.
 */

//! @ingroup srook_math_primes_counting
//! @{

#ifndef INCLUDED_SROOK_MATH_PRIMES_PROGRESSION_COUNTING_ERATOSTHENESE_HPP
#define INCLUDED_SROOK_MATH_PRIMES_PROGRESSION_COUNTING_ERATOSTHENESE_HPP

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
#include <srook/math/constants/algorithm/sqrt.hpp>
#include <srook/math/constants/algorithm/log.hpp>
#include <srook/math/primes/counting/legendre.hpp>
#include <cmath>
#include <vector>

SROOK_NESTED_NAMESPACE(srook, math, primes, counting) {
SROOK_INLINE_NAMESPACE(v1)

/**
 * @class sieve_eratosthenese
 * @brief sieve eratosthenese algorithm
 */
class sieve_eratosthenese {
public:
    /**
     * @brief Given a integral number @a n, count all primes smaller than @a n
     * @param n integer value 
     * @return The number of prime numbers smaller than @a n.
     * @exception none
     * @detail 
     *  Divide the range [0..n-1] in different segments and compute primes in all segments one by one.
     *  Time complexity: O(n \log\log n)
     *  Space complexity: O(n) 
     */
    template <class T>
    SROOK_FORCE_INLINE std::size_t operator()(T n)
    {
        if (n < 2) return {};
        return sieve(n);
    }
private:
    SROOK_FORCE_INLINE std::size_t sieve(std::size_t n)
    {
        std::vector<bool> prime(n, true);
        prime[0].flip();
        for (std::size_t i = 0, end = static_cast<std::size_t>(srook::math::sqrt(n)); i < end; ++i) {
            if (prime[i]) {
                for (std::size_t j = ((i + 1) << 1) - 1; j < n; j += i + 1) prime[j] = false;
            }
        }
        std::size_t x = 0;
        for (std::size_t i = 1; i < n; ++i) {
            if (prime[i]) ++x;
        }
        return x;
    }
}; 

template <class Integral>
SROOK_FORCE_INLINE std::size_t compute_sieve_eratosthenese(Integral x)
{
    return sieve_eratosthenese()(srook::move(x));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(progression, primes, math, srook)

#endif
#endif
//! @}
