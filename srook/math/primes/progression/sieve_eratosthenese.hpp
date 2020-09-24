// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
/**
 * @addtogroup srook_math_primes_progression
 * @file sieve_eratosthenese.hpp
 * @brief The prime number generator by sieve of eratosthenese algorithm.
 * @author roki
 * @par Copyright
 * Copyright (C) 2011-2019 Roki. Distributed under the MIT License.
 */

//! @ingroup srook_math_primes_progression
//! @{

#ifndef INCLUDED_SROOK_MATH_PRIMES_PROGRESSION_SIEVE_ERATOSTHENESE_HPP
#define INCLUDED_SROOK_MATH_PRIMES_PROGRESSION_SIEVE_ERATOSTHENESE_HPP

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

SROOK_NESTED_NAMESPACE(srook, math, primes, progression) {
SROOK_INLINE_NAMESPACE(v1)

/**
 * @class sieve_eratosthenese
 * @brief segmented sieve eratosthenese algorithm
 */
template <template <class...> class Container = std::vector>
class sieve_eratosthenese {
    template <class... Ts>
    struct container_type : type_constant<Container<Ts...>> {};
public:
    /**
     * @brief Given a integral number @a n, generate all primes smaller than @a n
     * @param n integer value 
     * @return the prime sequence smaller than n wrapped in @a Container<T>
     * @exception none
     * @detail 
     *  Divide the range [0..n-1] in different segments and compute primes in all segments one by one.
     *  Time complexity: O(n \log\log n)
     *  Space complexity: O(\sqrt{n}) 
     */
    template <class T>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<is_integral<T>::value, Container<T>>::type
    operator()(T n)
    {
        if (n < 2) return {};

        typedef T value_type;
        Container<value_type> rs;
        // By using the prime number theorem, the memory area is reserved in advance.
        rs.reserve(static_cast<std::size_t>(srook::math::primes::counting::legendre_compute(n)));

        // Find all primes upto square root of `n` and store these primes in vector `rs`.
        const auto limit = static_cast<value_type>(std::floor(std::sqrt(n)) + 1);
        auto oiter = sieve(limit, std::back_inserter(rs));

        // Divide the range [0..n-1] in different segments. 
        for (std::size_t low = limit, high = limit << 1; low < static_cast<std::size_t>(n); low += limit) {
            std::vector<bool> is_prime(limit + 1, true);
            for (const value_type& prime : rs) {
                // Find the minimum number in [low..high] that is a multiple of prime (divisible by prime).
                auto lolim = static_cast<std::size_t>(std::floor(low / prime)) * prime;
                if (lolim < low) lolim += prime;
                for (std::size_t i = lolim; i < high; i += prime) {
                    is_prime[i - low] = false;
                }
            }
            for (std::size_t i = low; i < high; ++i) {
                if (is_prime[i - low]) *oiter++ = static_cast<value_type>(i);
            }
            high += limit;
            if (high >= static_cast<std::size_t>(n)) high = n;
        }
        return rs;
    }
private:
    template <class T, class OutputIterator>
    SROOK_FORCE_INLINE OutputIterator sieve(T n, OutputIterator oiter)
    {
        std::vector<bool> prime(n, true);
        prime[0].flip();
        for (std::size_t i = 0, end = static_cast<std::size_t>(srook::math::sqrt(n)); i < end; ++i) {
            if (prime[i]) {
                for (std::size_t j = ((i + 1) << 1) - 1; j < static_cast<std::size_t>(n); j += i + 1) prime[j] = false;
            }
        }    
        for (std::size_t i = 1; i < static_cast<std::size_t>(n); ++i) {
            if (prime[i]) *oiter++ = static_cast<T>(i + 1);
        }
        return oiter;
    }
}; 

template <class Integral, template <class...> class Container = std::vector>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME std::enable_if<is_integral<Integral>::value, Container<Integral>>::type
compute_sieve_eratosthenese(Integral x)
{
    return sieve_eratosthenese<Container>()(srook::move(x));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(progression, primes, math, srook)

#endif
#endif
//! @}
