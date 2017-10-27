// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_base_of.hpp>
#include <srook/type_traits/is_default_constructible.hpp>
#include <srook/type_traits/is_destructible.hpp>
#include <srook/type_traits/is_function.hpp>
#include <srook/type_traits/is_lvalue_reference.hpp>
#include <srook/type_traits/is_rvalue_reference.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/is_static_castable.hpp>
#include <srook/type_traits/is_void.hpp>
#include <srook/type_traits/remove_reference.hpp>
#include <srook/utility/declval.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class, class...>
struct is_constructible;

namespace detail {

struct is_direct_constructible_impl_ {
    template <class T, class Arg, class = decltype(::new T(declval<Arg>()))>
    static SROOK_TRUE_TYPE test(int);

    template <class, class>
    static SROOK_FALSE_TYPE test(...);
};

template <class T, class Arg>
struct is_direct_constructible_impl : public is_direct_constructible_impl_ {
    typedef decltype(test<T, Arg>(0)) type;
};

template <class T, class Arg>
struct is_safe_direct_constructible_new : public conditional<is_destructible<T>::value && is_direct_constructible_impl<T, Arg>::type::value,
                                                             SROOK_TRUE_TYPE, SROOK_FALSE_TYPE>::type {
};

template <class From, class To, bool = !(is_void<From>::value || is_function<From>::value)>
struct is_base_to_derived_reference;

template <class From, class To>
struct is_base_to_derived_reference<From, To, true> {
    typedef typename remove_cv<typename remove_reference<From>::type>::type src_type;
    typedef typename remove_cv<typename remove_reference<To>::type>::type dst_type;
    typedef integral_constant<bool,
                              (!is_same<src_type, dst_type>::value) && is_base_of<src_type, dst_type>::value && (!is_constructible<dst_type, From>::value)>
        type;
    static SROOK_CONSTEXPR bool value = type::value;
};

template <class From, class To>
struct is_base_to_derived_reference<From, To, false> : public SROOK_FALSE_TYPE {
};

template <class From, class To,
          bool = is_lvalue_reference<From>::value&& is_rvalue_reference<To>::value>
struct is_lvalue_to_rvalue_reference;

template <class From, class To>
struct is_lvalue_to_rvalue_reference<From, To, true> {
    typedef typename remove_cv<typename remove_reference<From>::type>::type src_type;
    typedef typename remove_cv<typename remove_reference<To>::type>::type dst_type;
    typedef integral_constant<bool, ((!is_function<To>::value) && (is_same<src_type, dst_type>::value || is_base_of<dst_type, src_type>::value))> type;
    static constexpr bool value = type::value;
};

template <class From, class To>
struct is_lvalue_to_rvalue_reference<From, To, false> : public SROOK_FALSE_TYPE {
};

template <class T, class Arg>
struct is_direct_constructible_reference_cast : public integral_constant<bool,
                                                                         is_static_castable<Arg, T>::value && !(is_base_to_derived_reference<Arg, T>::value || is_lvalue_to_rvalue_reference<Arg, T>::value)> {
};

template <class T, class Arg>
struct is_direct_constructible_new : public conditional<is_reference<T>::value, is_direct_constructible_reference_cast<T, Arg>,
                                                        is_safe_direct_constructible_new<T, Arg> >::type {
};

template <class T, class Arg>
struct is_direct_constructible : public is_direct_constructible_new<T, Arg>::type {
};

struct is_nary_constructible_impl_ {
    template <class T, class... Args, class = decltype(T(declval<Args>()...))>
    static SROOK_TRUE_TYPE test(int);
    template <class, class...>
    static SROOK_FALSE_TYPE test(...);
};

template <class T, class... Args>
struct is_nary_constructible_impl : public is_nary_constructible_impl_ {
    typedef decltype(is_nary_constructible_impl_::test<T, Args...>(0)) type;
};

template <class T, class... Args>
struct is_nary_constructible : public is_nary_constructible_impl<T, Args...>::type {
    static_assert(sizeof...(Args) > 1, "is_nary_constructible");
};

template <class T, class... Args>
struct is_constructible_impl : public is_nary_constructible<T, Args...> {
};

template <class T, class Arg>
struct is_constructible_impl<T, Arg> : public is_direct_constructible<T, Arg> {
};

template <class T>
struct is_constructible_impl<T> : public is_default_constructible<T> {
};

} // namespace detail

template <class T, class... Args>
struct is_constructible : public detail::is_constructible_impl<T, Args...>::type {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_constructible;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class... Args>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_constructible_v = is_constructible<T, Args...>::value;
#endif

} // namespace srook

#endif
