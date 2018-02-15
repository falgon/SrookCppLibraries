// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
/**
 * @addtogroup srook_math_primes_progression
 * @file sieve_sundaram.hpp
 * @brief The prime number generator by sieve of sundaram algorithm.
 * @author roki
 * @par Copyright
 * Copyright (C) 2011-2018 Roki. Distributed under the MIT License.
 */

//! @ingroup srook_math_primes_progression
//! @{

#ifndef INCLUDED_SROOK_MATH_PRIMES_PROGRESSION_SIEVE_SUNDARAM_HPP
#define INCLUDED_SROOK_MATH_PRIMES_PROGRESSION_SIEVE_SUNDARAM_HPP

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
#include <srook/math/primes/counting/legendre.hpp>
#include <cmath>
#include <vector>

SROOK_NESTED_NAMESPACE(srook, math, primes, progression) {
SROOK_INLINE_NAMESPACE(v1)

/**
 * @class sieve_sundaram
 * @brief segmented sieve sundaram algorithm
 */
template <template <class...> class Container = std::vector>
class sieve_sundaram {
    template <class... Ts>
    struct container_type : type_constant<Container<Ts...>> {};
public:
    /**
     * @brief Given a integral number @a n, generate all primes smaller than @a n
     * @param n integer value 
     * @return the prime sequence smaller than n wrapped in @a Container<T>
     * @exception none
     * @detail 
     *  Time complexity: O(n \log\log n)
     *  Space complexity: O(n) 
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
        auto inserter = std::back_inserter(rs);
        sieve(n, [&inserter](T p){ *inserter++ = p; });
        return rs;
    }
protected:
    template <class T, class F>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, T&>::value>::type
    sieve(T n, F&& f)
    {
        std::vector<bool> is_prime(n + 1, false);
        const std::size_t nsize = (n - 2) >> 1;

        for (std::size_t i = 1; i <= nsize; ++i) {
            for (std::size_t j = i; (i + j + ((i * j) << 1)) <= nsize; ++j) {
                is_prime[i + j + ((i * j) << 1)] = true;
            }
        }
        f(2);
        for (std::size_t i = 1; i <= nsize; ++i) {
            if (!is_prime[i]) f((i << 1) + 1);
        }
    }
};

template <class Integral, template <class...> class Container = std::vector>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME std::enable_if<is_integral<Integral>::value, Container<Integral>>::type
compute_sieve_sundaram(Integral x)
{
    return sieve_sundaram<Container>()(srook::move(x));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(progression, primes, math, srook)

#endif
#endif
//! @}
