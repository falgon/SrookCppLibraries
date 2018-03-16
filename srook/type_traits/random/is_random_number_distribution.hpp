// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_RANDOM_NUMBER_DISTRIBUTION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_RANDOM_NUMBER_DISTRIBUTION_HPP

#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/type_traits/is_copy_constructible.hpp>
#include <srook/type_traits/is_copy_assignable.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/cstdint.hpp>
#include <istream>
#include <ostream>
#include <random> // for the type satisfying UniformRandomBitGenerator

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

typedef std::minstd_rand0 uniform_randombit_generator_type;

template <class D>
struct is_random_number_distribution_impl {
private:
    template <class T>
    static SROOK_DEDUCED_TYPENAME type_traits::detail::Land<
        is_copy_constructible<T>,
        is_copy_assignable<T>,
        is_arithmetic<SROOK_DEDUCED_TYPENAME T::result_type>,
        is_copy_constructible<SROOK_DEDUCED_TYPENAME T::param_type>,
        is_copy_assignable<SROOK_DEDUCED_TYPENAME T::param_type>,
        is_equality_comparable<SROOK_DEDUCED_TYPENAME T::param_type>,
        is_same<SROOK_DEDUCED_TYPENAME T::param_type::distribution_type, T>,
        is_default_constructible<T>,
        is_constructible<T, SROOK_DEDUCED_TYPENAME T::param_type>,
        is_same<SROOK_DECLTYPE(T().reset()), void>,
        is_same<SROOK_DECLTYPE(T().param()), SROOK_DEDUCED_TYPENAME T::param_type>,
        is_same<SROOK_DECLTYPE(declval<const T>().param()), SROOK_DEDUCED_TYPENAME T::param_type>,
        is_same<SROOK_DECLTYPE(T().param(declval<SROOK_DEDUCED_TYPENAME T::param_type>())), void>,
        is_same<SROOK_DECLTYPE(T{}(declval<uniform_randombit_generator_type>())), SROOK_DEDUCED_TYPENAME D::result_type>,
        is_same<SROOK_DECLTYPE(T{}(declval<uniform_randombit_generator_type>(), declval<SROOK_DEDUCED_TYPENAME D::param_type>())), SROOK_DEDUCED_TYPENAME T::result_type>,
        is_same<SROOK_DECLTYPE(declval<T&>().min()), SROOK_DEDUCED_TYPENAME T::result_type>,
        is_same<SROOK_DECLTYPE(declval<const T&>().min()), SROOK_DEDUCED_TYPENAME T::result_type>,
        is_same<SROOK_DECLTYPE(declval<T&>().max()), SROOK_DEDUCED_TYPENAME T::result_type>,
        is_same<SROOK_DECLTYPE(declval<const T&>().max()), SROOK_DEDUCED_TYPENAME T::result_type>,
        is_same<SROOK_DECLTYPE(declval<T&>() == declval<T&>()), bool>,
        is_same<SROOK_DECLTYPE(declval<const T&>() == declval<T&>()), bool>,
        is_same<SROOK_DECLTYPE(declval<T&>() == declval<const T&>()), bool>,
        is_same<SROOK_DECLTYPE(declval<const T&>() == declval<const T&>()), bool>,
        is_same<SROOK_DECLTYPE(declval<T&>() != declval<T&>()), bool>,
        is_same<SROOK_DECLTYPE(declval<const T&>() != declval<T&>()), bool>,
        is_same<SROOK_DECLTYPE(declval<T&>() != declval<const T&>()), bool>,
        is_same<SROOK_DECLTYPE(declval<const T&>() != declval<const T&>()), bool>,
        is_same<SROOK_DECLTYPE(declval<std::ostream&>() << T()), std::ostream&>,
        is_same<SROOK_DECLTYPE(declval<std::ostream&>() << declval<const T>()), std::ostream&>,
        is_same<SROOK_DECLTYPE(declval<std::istream&>() >> T()), std::istream&>
    >::type test(int);

    template <class>
    static SROOK_FALSE_TYPE test(...);
public:
    typedef SROOK_DECLTYPE(test<D>(0)) type;
};

} // namespace detail

template <class D>
struct is_random_number_distribution : detail::is_random_number_distribution_impl<D>::type {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class D>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_random_number_distribution_v = is_random_number_distribution<D>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_random_number_distribution;

} // namespace srook

#endif
