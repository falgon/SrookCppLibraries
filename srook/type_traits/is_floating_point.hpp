// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_FLOATING_POINT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_FLOATING_POINT_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

#define DEFINE_TRUE_FLOATING_POINT(TYPE)                           \
    template <>                                                    \
    struct is_floating_point_impl<TYPE> : public SROOK_TRUE_TYPE { \
    }

template <typename>
struct is_floating_point_impl : public SROOK_FALSE_TYPE {
};

DEFINE_TRUE_FLOATING_POINT(float);
DEFINE_TRUE_FLOATING_POINT(double);
DEFINE_TRUE_FLOATING_POINT(long double);
#if !defined(__STRICT_ANSI__) && defined(_GLIBCXX_USE_INT128)
DEFINE_TRUE_FLOATING_POINT(__float128);
#endif
#undef DEFINE_TRUE_FLOATING_POINT

} // namespace detail

template <class T>
struct is_floating_point : public detail::is_floating_point_impl<typename remove_cv<T>::type>::type {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_floating_point;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_floating_point_v = is_floating_point<T>::value;
#endif

} // namespace srook

#endif
