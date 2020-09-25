// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_GEOMETRY_FUNDAMENTAL_THETA_HPP
#define INCLUDED_SROOK_MATH_GEOMETRY_FUNDAMENTAL_THETA_HPP

#ifndef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config/feature.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/cstdfloat.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_fixed_point.hpp>
#include <srook/type_traits/disable_if.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/numeric/fixed_point/detail/fixed_point_declare.hpp>

SROOK_NESTED_NAMESPACE(srook, math, geometry, fundamental) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
class theta {
    SROOK_STATIC_ASSERT((type_traits::detail::Lor<is_arithmetic<T>, is_fixed_point<T>>::value), "The type must be arithmetic type");
public:
    typedef T value_type;
    typedef numeric_limits<T> traits_type;
        
    SROOK_FORCE_INLINE SROOK_CONSTEXPR theta() SROOK_DEFAULT

    SROOK_FORCE_INLINE SROOK_CONSTEXPR theta(const T& val) SROOK_NOEXCEPT_TRUE
        : data_(val) {}
    SROOK_FORCE_INLINE SROOK_CONSTEXPR theta& operator=(const T& val) SROOK_NOEXCEPT_TRUE { return data_ = val, *this; }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR operator T() const SROOK_NOEXCEPT_TRUE { return data_; }
#endif
    SROOK_FORCE_INLINE SROOK_CONSTEXPR operator T() SROOK_NOEXCEPT_TRUE { return data_; }
private:
    T data_;
};

template <std::size_t F, std::size_t I>
SROOK_FORCE_INLINE SROOK_CONSTEXPR bool operator==(const theta<srook::numeric::fixed_point<F, I>>& lhs, const theta<srook::numeric::fixed_point<F, I>>& rhs) SROOK_NOEXCEPT_TRUE
{
    return static_cast<srook::numeric::fixed_point<F, I>>(lhs) == static_cast<srook::numeric::fixed_point<F, I>>(rhs);
}

template <std::size_t F, std::size_t I>
SROOK_FORCE_INLINE SROOK_CONSTEXPR bool operator!=(const theta<srook::numeric::fixed_point<F, I>>& lhs, const theta<srook::numeric::fixed_point<F, I>>& rhs) SROOK_NOEXCEPT_TRUE
{
    return !(lhs == rhs);
}

template <std::size_t F, std::size_t I>
SROOK_FORCE_INLINE SROOK_CONSTEXPR bool operator<(const theta<srook::numeric::fixed_point<F, I>>& lhs, const theta<srook::numeric::fixed_point<F, I>>& rhs) SROOK_NOEXCEPT_TRUE
{
    return static_cast<srook::numeric::fixed_point<F, I>>(lhs) < static_cast<srook::numeric::fixed_point<F, I>>(rhs);
}

template <std::size_t F, std::size_t I>
SROOK_FORCE_INLINE SROOK_CONSTEXPR bool operator<=(const theta<srook::numeric::fixed_point<F, I>>& lhs, const theta<srook::numeric::fixed_point<F, I>>& rhs) SROOK_NOEXCEPT_TRUE
{
    return lhs == rhs || lhs < rhs;
}

template <std::size_t F, std::size_t I>
SROOK_FORCE_INLINE SROOK_CONSTEXPR bool operator>(const theta<srook::numeric::fixed_point<F, I>>& lhs, const theta<srook::numeric::fixed_point<F, I>>& rhs) SROOK_NOEXCEPT_TRUE
{
    return !(lhs <= rhs);
}

template <std::size_t F, std::size_t I>
SROOK_FORCE_INLINE SROOK_CONSTEXPR bool operator>=(const theta<srook::numeric::fixed_point<F, I>>& lhs, const theta<srook::numeric::fixed_point<F, I>>& rhs) SROOK_NOEXCEPT_TRUE
{
    return lhs == rhs || lhs > rhs;
}

template <class T>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME disable_if<is_fixed_point<T>::value, bool>::type
operator==(const theta<T>& lhs, const theta<T>& rhs) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE

template <class T>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME disable_if<is_fixed_point<T>::value, bool>::type
operator!=(const theta<T>&, const theta<T>&) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE

#if SROOK_CPP_DEDUCTION_GUIDES
template <class T>
theta(T) -> theta<T>;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(fundamental, geometry, math, srook)

#endif
