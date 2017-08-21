// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MATH_DETAIL_FLOAT_COMPUTE_HPP
#define INCLUDED_SROOK_MATH_DETAIL_FLOAT_COMPUTE_HPP

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/type_traits/float_promote.hpp>

namespace srook {

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

namespace math {
inline namespace v1 {
namespace detail {

template <class... Ts>
struct float_compute : float_promote<double, Ts...> {
};

template <typename FloatType>
SROOK_FORCE_INLINE constexpr typename float_compute<FloatType>::type as_float_compute(const FloatType &x)
{
    return static_cast<typename float_compute<FloatType>::type>(x);
}

} // namespace detail
} // namespace v1
} // namespace math

#endif
} // srook

#endif
