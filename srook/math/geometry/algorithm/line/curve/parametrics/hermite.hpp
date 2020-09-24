// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_GEOMETORY_ALGORITHM_LINE_CURVE_PARAMETRICS_HERMITE_HPP
#define INCLUDED_SROOK_MATH_GEOMETORY_ALGORITHM_LINE_CURVE_PARAMETRICS_HERMITE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <tuple>
#include <srook/math/geometry/fundamental/point.hpp>
#include <srook/math/geometry/fundamental/vector.hpp>
#include <srook/math/geometry/algorithm/line/straight/simple_equation.hpp>
#include <srook/math/constants/algorithm/pow.hpp>

SROOK_NESTED_NAMESPACE(srook, math, geometry, algorithm, line, curve) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T = double>
class hermite_axis : protected srook::math::geometry::algorithm::line::straight::detail::line_axis<T> {
    typedef srook::math::geometry::algorithm::line::straight::detail::line_axis<T> base_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::point_type point_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::container_type container_type;
    typedef srook::math::geometry::fundamental::vector<value_type> vector_type;
public:
    SROOK_CONSTEXPR SROOK_FORCE_INLINE
    hermite_axis(const point_type& xy0, const vector_type& vw0, const point_type& xy1, const vector_type& vw1, std::size_t granularity = 1024) SROOK_NOEXCEPT_TRUE
        : base_type(xy0, xy1), begin_vector(vw0), end_vector(vw1), granularity_(granularity) {}

    SROOK_FORCE_INLINE container_type operator()() const
    {
        typedef numeric_limits<value_type> limits_t;
        return 
            this->check_invalid(SROOK_DEDUCED_TYPENAME type_traits::detail::Lor<is_floating_point<T>, is_fixed_point<T>>::type()) ?
            hermite_compute() : container_type(1, point_type(limits_t::quiet_NaN(), limits_t::quiet_NaN()));
    }
private:
    SROOK_FORCE_INLINE container_type hermite_compute() const
    {
        container_type res(granularity_);
        SROOK_DEDUCED_TYPENAME container_type::iterator iter = res.begin();
        for (double i = 0; i < 1; i += 1 / static_cast<double>(granularity_)) { // TODO
            *iter++ = point_type(x_compute(i), y_compute(i));
        }
        return res;
    }

    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR value_type x_compute(value_type t) const
    {
        value_type x0 = this->begin_.x(), x1 = this->end_.x();
        value_type v0 = begin_vector.v(), v1 = end_vector.v();
        return (2 * x0 - 2 * x1 + v0 + v1) * srook::math::pow(t, 3) + (-3 * x0 + 3 * x1 - 2 * v0 - v1) * srook::math::pow(t, 2) + v0 * t + x0;
    }

    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR value_type y_compute(value_type t) const
    {
        value_type y0 = this->begin_.y(), y1 = this->end_.y();
        value_type w0 = begin_vector.w(), w1 = end_vector.w();
        return (2 * y0 - 2 * y1 + w0 + w1) * srook::math::pow(t, 3) + (-3 * y0 + 3 * y1 - 2 * w0 - w1) * srook::math::pow(t, 2) + w0 * t + y0;
    }

    vector_type begin_vector, end_vector;
    std::size_t granularity_;
};

} // namespace detail

class hermite_points : protected detail::hermite_axis<> {
    typedef detail::hermite_axis<> base_type;
public:
    typedef srook::math::geometry::fundamental::point<> point_type;
    typedef srook::math::geometry::fundamental::vector<> vector_type;
    typedef double index_type;
    typedef std::tuple<point_type, vector_type, point_type, vector_type> argument_type;
    using base_type::base_type;
    using base_type::operator();
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(curve, line, algorithm, geometry, math, srook)

#endif
