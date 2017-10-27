// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_STATIC_CASTABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_STATIC_CASTABLE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/utility/declval.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

struct is_static_castable_impl_ {
    template <class From, class To, class = decltype(static_cast<To>(declval<From>()))>
    static SROOK_TRUE_TYPE test(int);

    template <class, class>
    static SROOK_FALSE_TYPE test(...);
};

template <class From, class To>
struct is_static_castable_impl : public is_static_castable_impl_ {
    typedef decltype(test<From, To>(0)) type;
};

template <class From, class To>
struct is_safe_static_castable : public is_static_castable_impl<From, To>::type {
};

} // namespace detail

template <class From, class To>
struct is_static_castable : public detail::is_safe_static_castable<From, To>::type {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_static_castable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class From, class To>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_static_castable_v = is_static_castable<From, To>::value;
#endif

} // namespace srook

#endif
