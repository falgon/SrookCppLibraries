#ifndef INCLUDED_SROOK_MATH_DETAIL_POW_HPP
#define INCLUDED_SROOK_MATH_DETAIL_POW_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/require.hpp>
#include <type_traits>

namespace srook {
namespace math {
inline namespace v1 {
namespace detail {

template <class T>
SROOK_FORCE_INLINE constexpr T pow2(const T &x) SROOK_NOEXCEPT(x *x)
{
    return x * x;
}

template <class T>
SROOK_FORCE_INLINE constexpr T pow3(const T &x) SROOK_NOEXCEPT(x *x *x)
{
    return x * x * x;
}

template <class T>
SROOK_FORCE_INLINE constexpr T pow4(const T &x) SROOK_NOEXCEPT(x *x *x *x)
{
    return x * x * x * x;
}

template <class T>
SROOK_FORCE_INLINE constexpr T pow5(const T &x) SROOK_NOEXCEPT(x *x *x *x *x)
{
    return x * x * x * x * x;
}

template <class T, typename IntType>
constexpr T pow_n_impl(const T &x, IntType n) SROOK_NOEXCEPT(n == 1 ? x : n % 2 ? x * pow2(pow_n_impl(x, n / 2)) : pow2(pow_n_impl(x, n / 2)))
{
    return n == 1 ? x : n % 2 ? x * pow2(pow_n_impl(x, n / 2)) : pow2(pow_n_impl(x, n / 2));
}

template <class T, class UIntType, REQUIRES(std::is_unsigned<UIntType>::value and std::is_integral<UIntType>::value)>
SROOK_FORCE_INLINE constexpr T pow_n(const T &x, UIntType n) SROOK_NOEXCEPT(n == 0 ? T(1) : pow_n_impl(x, n))
{
    return n == 0 ? T(1) : pow_n_impl(x, n);
}

template <class T, class SIntType, REQUIRES(std::is_signed<SIntType>::value and std::is_integral<SIntType>::value)>
SROOK_FORCE_INLINE constexpr T pow_n(const T &x, SIntType n) SROOK_NOEXCEPT()
{
    return n == 0 ? T(1) : n > 0 ? pow_n_impl(x, n) : T(1) / pow_n_impl(x, -n);
}

} // namespace detail
} // namespace v1
} // namespace math
} // namespace srook

#endif
