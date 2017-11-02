// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_CONVERTIBLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_CONVERTIBLE_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/decltype.hpp>
#include <srook/type_traits/is_array.hpp>
#include <srook/type_traits/is_function.hpp>
#include <srook/type_traits/is_void.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/declval.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class From, class To, bool = is_void<From>::value || is_function<To>::value || is_array<To>::value>
struct is_convertible_impl : is_void<To>::type {
};

template <class From, class To>
struct is_convertible_impl<From, To, false> {
private:
    template <class To1>
    static void test(To1);
    template <class From1, class To1, typename = SROOK_DECLTYPE((test<To1>(declval<From>())))>
    static SROOK_TRUE_TYPE test(int);
    template <class, class>
    static SROOK_FALSE_TYPE test(...);

public:
    typedef SROOK_DECLTYPE((test<From, To>(0))) type;
};

} // namespace detail

template <class From, class To>
struct is_convertible : public detail::is_convertible_impl<From, To>::type {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_convertible;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class R>
constexpr bool is_convertible_v = is_convertible<L, R>::value;
#endif

} // namespace srook
#endif
