// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_FACTORIAL_HPP
#define INCLUDED_SROOK_MATH_CONSTANTS_ALGORITHM_FACTORIAL_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/libraries/nullptr.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <type_traits>
namespace srook {
namespace math {
inline namespace v1 {
namespace detail {

template <typename, class = SROOK_NULLPTR_T>
struct factorials;

#define DEFINE_FACTRIALS(SIZE, LIMIT)                                                                                        \
    template <typename T>                                                                                                    \
    struct factorials<T, typename std::enable_if<std::is_integral<T>::value and sizeof(T) == SIZE, SROOK_NULLPTR_T>::type> { \
	typedef T type;                                                                                                      \
	SROOK_INLINE_VARIABLE static constexpr std::size_t limit = LIMIT;                                                    \
    }
DEFINE_FACTRIALS(1, 5);
DEFINE_FACTRIALS(2, 7);
DEFINE_FACTRIALS(4, 11);
DEFINE_FACTRIALS(8, 20);

#undef DEFINE_FACTRIALS
#define DEFINE_FACTRIALS(TYPE, LIMIT)                                                                    \
    template <typename T>                                                                                \
    struct factorials<T, typename std::enable_if<std::is_same<T, TYPE>::value, SROOK_NULLPTR_T>::type> { \
	typedef T type;                                                                                  \
	SROOK_INLINE_VARIABLE static constexpr std::size_t limit = LIMIT;                                \
    }
DEFINE_FACTRIALS(float, 34);
DEFINE_FACTRIALS(double, 170);
#undef DEFINE_FACTRIALS

} // namespace detail

template <typename T, REQUIRES(std::is_integral<T>::value or std::is_floating_point<T>::value)>
inline constexpr T factorial(T x) SROOK_NOEXCEPT_TRUE
{
    return x <= 1 ? 1 : x * factorial(x - 1);
}

template <typename T, REQUIRES(std::is_arithmetic<T>::value)>
SROOK_FORCE_INLINE constexpr T factorial_limit() SROOK_NOEXCEPT_TRUE
{
    return detail::factorials<typename std::decay<T>::type>::limit;
}

} // namespace v1
} // namespace math

using math::factorial;

} // namespace srook

#endif
