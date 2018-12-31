// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_GEOMETORY_FUNDAMENTAL_VECTOR_HPP
#define INCLUDED_SROOK_MATH_GEOMETORY_FUNDAMENTAL_VECTOR_HPP

#ifndef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/math/geometry/fundamental/point.hpp>

SROOK_NESTED_NAMESPACE(srook, math, geometry, fundamental) {
SROOK_INLINE_NAMESPACE(v1)

template <class T = double>
class vector : protected point<T> {
    typedef point<T> base_type;
public:
    typedef SROOK_DEDUCED_TYPENAME base_type::value_type value_type;
    
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector() SROOK_DEFAULT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector(const vector& other) SROOK_NOEXCEPT_TRUE
        : base_type(other) {}
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector(vector&& other) SROOK_NOEXCEPT_TRUE
        : base_type(srook::move(other)) {}
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector(value_type v, value_type w) SROOK_NOEXCEPT_TRUE
        : base_type(v, w) {}

    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector& operator=(const vector& other) SROOK_NOEXCEPT_TRUE
    {
        base_type::operator=(other);
        return *this;
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector& operator=(vector&& other) SROOK_NOEXCEPT_TRUE
    {
        base_type::operator=(srook::move(other));
        return *this;
    }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_CONSTEXPR const value_type& v() const SROOK_NOEXCEPT_TRUE { return this->x(); }
    SROOK_CONSTEXPR const value_type& w() const SROOK_NOEXCEPT_TRUE { return this->y(); }
#endif
    SROOK_CONSTEXPR value_type& v() SROOK_NOEXCEPT_TRUE { return this->x(); }
    SROOK_CONSTEXPR value_type& w() SROOK_NOEXCEPT_TRUE { return this->y(); }
private:
    SROOK_FORCE_INLINE friend std::ostream& operator<<(std::ostream& os, const vector& this_)
    {
        return os << static_cast<point<T>>(this_);
    }
};

#if SROOK_CPP_DEDUCTION_GUIDES
template <class T>
vector(T, T) -> vector<T>;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(fundamental ,geometry, math, srook)

#endif
