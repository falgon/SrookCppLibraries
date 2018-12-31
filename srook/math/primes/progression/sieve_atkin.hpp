// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
/**
 * @addtogroup srook_math_primes_progression
 * @file sieve_atkin.hpp
 * @brief The prime number generator by sieve of atkin algorithm.
 * @author roki
 * @par Copyright
 * Copyright (C) 2011-2019 Roki. Distributed under the MIT License.
 */

//! @ingroup srook_math_primes_progression
//! @{

#ifndef INCLUDED_SROOK_MATH_PRIMES_PROGRESSION_SIEVE_ATKIN_HPP
#define INCLUDED_SROOK_MATH_PRIMES_PROGRESSION_SIEVE_ATKIN_HPP

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
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/math/constants/algorithm/sqrt.hpp>
#include <srook/math/constants/algorithm/log.hpp>
#include <srook/math/constants/algorithm/pow.hpp>
#include <srook/math/primes/counting/legendre.hpp>
#include <cmath>
#include <vector>

SROOK_NESTED_NAMESPACE(srook, math, primes, progression) {
SROOK_INLINE_NAMESPACE(v1)

/**
 * @class sieve_atkin
 * @brief sieve atkin algorithm
 */
template <template <class...> class Container = std::vector>
class sieve_atkin {
    template <class... Ts>
    struct container_type : type_constant<Container<Ts...>> {};
public:
    /**
     * @brief Given a integral number @a n, generate all primes smaller than @a n
     * @param n integer value 
     * @return the prime sequence smaller than n wrapped in @a Container<T>
     * @exception none
     * @detail 
     *  Time complexity: O(n / \log\log n)
     *  Space complexity: O(n) 
     *  See also: http://www.ams.org/journals/mcom/2004-73-246/S0025-5718-03-01501-1/S0025-5718-03-01501-1.pdf
     */
    template <class T>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<is_integral<T>::value, Container<T>>::type
    operator()(T n)
    {
        if (n < 2) return {};
        typedef T value_type;
        Container<value_type> rs = { 2 };
        if (n < 3) return rs;
        rs.push_back(3);
        if (n < 4) return rs;
        
        // By using the prime number theorem, the memory area is reserved in advance.
        rs.reserve(static_cast<std::size_t>(srook::math::primes::counting::legendre_compute(n)));
        auto inserter = std::back_inserter(rs);
        sieve(n, [&inserter](value_type p){ *inserter++ = p; });
        return rs;
    }

    template <class T, class F1, class F2>
    SROOK_FORCE_INLINE void operator()(T n, F1&& PrimeF, F2&& NPrimeF)
    {
        NPrimeF(0);
        NPrimeF(1);
        if (n < 2) return ;
        PrimeF(2);
        if (n < 3) return ;
        PrimeF(3);
        if (n < 4) return ;
        NPrimeF(4);
        sieve(n, srook::forward<F1>(PrimeF), srook::forward<F2>(NPrimeF));
    }
protected:
    template <class T, class F>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, T&>::value>::type 
    sieve(const T n, F&& f)
    {
        std::vector<bool> is_prime(n, false);
        const std::size_t sqrtn = srook::math::sqrt(n);
        std::size_t in = 0;
        
        for (std::size_t i = 1; i <= 5; i += 4) {
            for (std::size_t j = i; j <= sqrtn; j += 6) {
                for (std::size_t k = 1; k <= sqrtn && (in = (k * k << 2) + j * j) <= n; ++k) {
                    is_prime[in].flip();
                }
                for (std::size_t k = j + 1; k <= sqrtn && (in = 3 * k * k - j * j) <= n; k += 2) {
                    is_prime[in].flip();
                }
            }
        }
        for (std::size_t i = 2; i <= 4; i += 2) {
            for (std::size_t j = i; j <= sqrtn; j += 6) {
                for (std::size_t k = 1; k <= sqrtn && (in = 3 * k * k + j * j) <= n; k += 2) {
                    is_prime[in].flip();
                }
                for (std::size_t k = j + 1; k <= sqrtn && (in = 3 * k * k - j * j) <= n; k += 2) {
                    is_prime[in].flip();
                }
            }
        }
        for (std::size_t i = 3; i <= sqrtn; i += 6) {
            for (std::size_t j = 1; j <= 2; ++j) {
                for (std::size_t k = j; k <= sqrtn && (in = (k * k << 2) + i * i) <= n; k += 3) {
                    is_prime[in].flip();
                }
            }
        }
        for (std::size_t i = 5; i <= sqrtn; ++i) {
            if (is_prime[i]) {
                for (std::size_t j = i * i; j <= n; j += i * i) {
                    is_prime[j] = false;
                }
            }
        }
        for (std::size_t i = 5; i < n; ++i) {
            if (is_prime[i]) f(i);
        }
    }
    
    template <class T, class F1, class F2>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
    enable_if<type_traits::detail::Land<is_invocable<SROOK_DEDUCED_TYPENAME decay<F1>::type, T&>, is_invocable<SROOK_DEDUCED_TYPENAME decay<F2>::type, T&>>::value>::type 
    sieve(const T n, F1&& f1, F2&& f2)
    {
        std::vector<bool> is_prime(n, false);
        const std::size_t sqrtn = srook::math::sqrt(n);
        std::size_t in = 0;
        
        for (std::size_t i = 1; i <= 5; i += 4) {
            for (std::size_t j = i; j <= sqrtn; j += 6) {
                for (std::size_t k = 1; k <= sqrtn && (in = (k * k << 2) + j * j) <= n; ++k) {
                    is_prime[in].flip();
                }
                for (std::size_t k = j + 1; k <= sqrtn && (in = 3 * k * k - j * j) <= n; k += 2) {
                    is_prime[in].flip();
                }
            }
        }
        for (std::size_t i = 2; i <= 4; i += 2) {
            for (std::size_t j = i; j <= sqrtn; j += 6) {
                for (std::size_t k = 1; k <= sqrtn && (in = 3 * k * k + j * j) <= n; k += 2) {
                    is_prime[in].flip();
                }
                for (std::size_t k = j + 1; k <= sqrtn && (in = 3 * k * k - j * j) <= n; k += 2) {
                    is_prime[in].flip();
                }
            }
        }
        for (std::size_t i = 3; i <= sqrtn; i += 6) {
            for (std::size_t j = 1; j <= 2; ++j) {
                for (std::size_t k = j; k <= sqrtn && (in = (k * k << 2) + i * i) <= n; k += 3) {
                    is_prime[in].flip();
                }
            }
        }
        for (std::size_t i = 5; i <= sqrtn; ++i) {
            if (is_prime[i]) {
                for (std::size_t j = i * i; j <= n; j += i * i) {
                    is_prime[j] = false;
                }
            }
        }
        for (std::size_t i = 5; i < n; ++i) {
            if (is_prime[i]) f1(i);
            else f2(i);
        }
    }
};

template <class Integral, template <class...> class Container = std::vector>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME std::enable_if<is_integral<Integral>::value, Container<Integral>>::type
compute_sieve_atkin(Integral x)
{
    return sieve_atkin<Container>()(srook::move(x));
}

template <class Integral, class F1, class F2>
SROOK_FORCE_INLINE void compute_sieve_atkin_if(Integral x, F1&& PrimeF, F2&& NPrimeF)
{
    return sieve_atkin<>()(srook::move(x), srook::forward<F1>(PrimeF), srook::forward<F2>(NPrimeF));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(progression, primes, math, srook)

#endif
#endif
//! @}
