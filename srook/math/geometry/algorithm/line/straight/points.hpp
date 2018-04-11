// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_GEOMETORY_ALGORITHM_LINE_STRAIGHT_POINTS_HPP
#define INCLUDED_SROOK_MATH_GEOMETORY_ALGORITHM_LINE_STRAIGHT_POINTS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/math/geometry/algorithm/line/straight/slope.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <srook/range/adaptor/copied.hpp>
#include <srook/range/adaptor/transformed.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <cmath>
#include <vector>
#include <iostream>


SROOK_NESTED_NAMESPACE(srook, math, geometry, algorithm, line, straight) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T = double>
class line_axis {
    typedef T value_type;
    typedef srook::math::geometry::fundamental::point<T> point_type;
    typedef std::vector<point_type> container_type;
    typedef std::pair<point_type, double> aa_point_type;
    typedef std::vector<aa_point_type> aa_container_type;
public:
    
    SROOK_FORCE_INLINE SROOK_CONSTEXPR line_axis(const srook::math::geometry::fundamental::point<value_type>& lhs, const srook::math::geometry::fundamental::point<value_type>& rhs)
    SROOK_NOEXCEPT_TRUE
        : begin_(lhs), end_(rhs) {}

    SROOK_FORCE_INLINE container_type operator()() const 
    {
        typedef srook::numeric_limits<T> limits_t;
        return 
            !check_invalid(SROOK_DEDUCED_TYPENAME type_traits::detail::Lor<is_floating_point<T>, is_fixed_point<T>>::type()) ? 
            begin_.x() == end_.x() ? perpendicular() : make_straight() : container_type(1, point_type(limits_t::quiet_NaN(), limits_t::quiet_NaN()));
    }
private:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool check_invalid(SROOK_TRUE_TYPE) const SROOK_NOEXCEPT_TRUE
    {
        typedef srook::numeric_limits<T> limits_t;
        return 
            isnan(begin_.x())                   ||
            isnan(begin_.y())                   || 
            isnan(end_.x())                     || 
            isnan(end_.y())                     || 
            begin_.x() >= limits_t::infinity()  || 
            begin_.x() <= -limits_t::infinity() ||
            begin_.y() >= limits_t::infinity()  ||
            begin_.y() <= -limits_t::infinity() ||
            end_.x() >= limits_t::infinity()    ||
            end_.x() <= -limits_t::infinity()   ||
            end_.y() >= limits_t::infinity()    ||
            end_.y() <= -limits_t::infinity();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool check_invalid(SROOK_FALSE_TYPE) { return true; }

    container_type perpendicular() const
    {
        container_type r(compute_capacity(begin_.y(), end_.y()), point_type(begin_.x(), begin_.y()));
#if SROOK_CPP_LAMBDAS
        unsigned u = 0;
        const auto l = [&u](const point_type& p) SROOK_NOEXCEPT_TRUE -> point_type { return { p.x(), p.y() + u++ }; };
#else
        struct nolambda {
            SROOK_CONSTEXPR nolambda() SROOK_DEFAULT
            SROOK_CONSTEXPR point_type operator()(const point_type& p) const SROOK_NOEXCEPT_TRUE { return point_type(p.x(), p.y() + u_++); }
        private:
            mutable unsigned u_;
        } l;
#endif
        return r | srook::range::adaptors::transformed(srook::move(l)) | srook::range::adaptors::copied;
    }

    container_type make_straight() const
    {
        const value_type m = slope::m(begin_, end_);

        if (m >= 1) {
#if SROOK_CPP_LAMBDAS
            auto l = [this, &m](auto& current, value_type i) -> void { current = point_type(round_frac1(from_y(m, static_cast<value_type>(i))), static_cast<value_type>(i)); };
#else
            struct nolambda {
                SROOK_CONSTEXPR nolambda() SROOK_DEFAULT
                SROOK_CXX14_CONSTEXPR void operator()(point_type& current, value_type i)
                {
                    current = point_type(round_frac1(from_y(m, static_cast<value_type>(i))), static_cast<value_type>(i));
                }
            } l;
#endif
            container_type yl(compute_capacity(begin_.y(), end_.y()));
            long i = begin_.y() - static_cast<long>(begin_.y()) >= 0.1 ? static_cast<long>(begin_.y() + 1) : begin_.y();  
            for (SROOK_DEDUCED_TYPENAME container_type::iterator iter = srook::begin(yl); iter != srook::end(yl); ++iter) {
                l(*iter, i++);
            }
            return yl;
        }
#if SROOK_CPP_LAMBDAS
        auto l = [this, &m](auto& current, std::size_t i) -> void { current = point_type(static_cast<value_type>(i), round_frac1(from_x(m, static_cast<value_type>(i)))); };
#else
        struct nolambda {
            SROOK_CONSTEXPR nolambda() SROOK_DEFAULT
            SROOK_CXX14_CONSTEXPR void operator()(point_type& current, std::size_t i)
            {
                current = point_type(static_cast<value_type>(i), round_frac1(from_x(m, static_cast<value_type>(i))));
            }
        } l;
#endif
        container_type xl(compute_capacity(begin_.x(), end_.x()));
        long i = begin_.x() - static_cast<long>(begin_.x()) >= 0.1 ? static_cast<long>(begin_.x() + 1) : begin_.x();
        for (SROOK_DEDUCED_TYPENAME container_type::iterator iter = srook::begin(xl); iter != srook::end(xl); ++iter) {
            l(*iter, i++);
        }
        return xl;
    }

    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR std::size_t compute_capacity(value_type b, value_type e) const SROOK_NOEXCEPT_TRUE
    {
        long capacity = static_cast<long>(e - b + 1);
        if (e > static_cast<long>(e)) ++capacity;
        if (b > static_cast<long>(b)) --capacity;
        return static_cast<std::size_t>(negate_signed(capacity));
    }

    template <class U>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR U negate_signed(U val) const SROOK_NOEXCEPT_TRUE
    {
        return val < 0 ? -val : val;
    }

    template <class U>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR U round_frac1(U val) const SROOK_NOEXCEPT_TRUE
    {
        return round_frac1_impl(srook::move(val), SROOK_DEDUCED_TYPENAME type_traits::detail::Lor<is_floating_point<U>, is_fixed_point<U>>::type());
    }

    template <class U>
    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR U round_frac1_impl(U val, SROOK_TRUE_TYPE) const SROOK_NOEXCEPT_TRUE
    {
        SROOK_CONSTEXPR_OR_CONST U fr = static_cast<U>(10);
        if (0 < val) {
            val *= fr;
            val += 0.5;
            return static_cast<U>(static_cast<long>(val) / fr);
        } else {
            val *= fr;
            val -= 0.5;
            return static_cast<U>(static_cast<long>(val) / fr);
        }
    }

    template <class U>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR U& round_frac1_impl(U& val, SROOK_FALSE_TYPE) const SROOK_NOEXCEPT_TRUE { return val; }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME point_type::value_type 
    from_x(value_type m, SROOK_DEDUCED_TYPENAME point_type::value_type x) const SROOK_NOEXCEPT_TRUE
    {
        return m * x - m * begin_.x() + begin_.y();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME point_type::value_type 
    from_y(value_type m, SROOK_DEDUCED_TYPENAME point_type::value_type y) const SROOK_NOEXCEPT_TRUE
    {
        return y * (1 / m) - begin_.y() * (1 / m) + begin_.x();
    }
private:
    const srook::math::geometry::fundamental::point<value_type>& begin_, end_;
};

} // namespace detail

class points : protected detail::line_axis<> {
    typedef detail::line_axis<> base_type;
public:
    using base_type::base_type;
    using base_type::operator();
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(straight, line, algorithm, geometry, math, srook)

#endif
