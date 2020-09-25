// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_GEOMETORY_FUNDAMENTAL_POINT_HPP
#define INCLUDED_SROOK_MATH_GEOMETORY_FUNDAMENTAL_POINT_HPP

#ifndef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <utility>
#include <ostream>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/static_assert.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/type_traits/is_fixed_point.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/numeric/fixed_point/detail/fixed_point_declare.hpp>
#include <srook/utility/move.hpp>

SROOK_NESTED_NAMESPACE(srook, math, geometry, fundamental) {
SROOK_INLINE_NAMESPACE(v1)

template <class T = double>
class point : public std::pair<T, T> {
    SROOK_STATIC_ASSERT((type_traits::detail::Lor<is_arithmetic<T>, is_fixed_point<T>>::value), "The type must be arithmetic type");
    typedef std::pair<T, T> base_type;
public:
    typedef SROOK_DEDUCED_TYPENAME base_type::first_type value_type;

    SROOK_FORCE_INLINE SROOK_CONSTEXPR point() SROOK_DEFAULT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR point(const point& other) SROOK_NOEXCEPT_TRUE
        : base_type(other.x(), other.y()) {}
    SROOK_FORCE_INLINE SROOK_CONSTEXPR point(point&& other) SROOK_NOEXCEPT_TRUE
        : base_type(srook::move(other.x()), srook::move(other.y())) {}
    
    SROOK_FORCE_INLINE SROOK_CONSTEXPR point& operator=(const point& other) SROOK_NOEXCEPT_TRUE
    {
        return this->first = other.x(), this->second = other.y(), *this;
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR point& operator=(point&& other) SROOK_NOEXCEPT_TRUE
    {
        return this->first = srook::move(other.x()), this->second = srook::move(other.y()), *this;
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR point(value_type x, value_type y) SROOK_NOEXCEPT_TRUE
        : base_type(x, y) {}
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const value_type& x() const SROOK_NOEXCEPT_TRUE { return this->first; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const value_type& y() const SROOK_NOEXCEPT_TRUE { return this->second; }
#endif
    SROOK_FORCE_INLINE SROOK_CONSTEXPR value_type& x() SROOK_NOEXCEPT_TRUE { return this->first; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR value_type& y() SROOK_NOEXCEPT_TRUE { return this->second; }
private:
    SROOK_FORCE_INLINE friend std::ostream& operator<<(std::ostream& os, const point& this_) 
    { 
        return os << '(' << this_.x() << ", " << this_.y() << ')'; 
    }
};

#if SROOK_CPP_DEDUCTION_GUIDES
template <class T>
point(T, T) -> point<T>;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(fundamental ,geometry, math, srook)

#endif
