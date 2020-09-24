// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_RANDOM_NUMBER_ENGINE_ADAPTOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_RANDOM_NUMBER_ENGINE_ADAPTOR_HPP

#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/cstdint.hpp>
#include <random> // for the type satisfying UniformRandomBitGenerator

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

typedef std::minstd_rand0 random_number_engine_t;

template <class A>
struct is_random_number_engine_adaptor_impl {
private:
    template <class T>
    static SROOK_DEDUCED_TYPENAME type_traits::detail::Land<
        is_default_constructible<T>,
        is_constructible<T, SROOK_DEDUCED_TYPENAME T::result_type>,
        is_constructible<T, std::seed_seq>,
        is_equality_comparable<T>,
        is_invocable<SROOK_DECLTYPE(&T::seed), T>,
        is_invocable<SROOK_DECLTYPE(&T::seed), T, SROOK_DEDUCED_TYPENAME T::result_type>,
        is_invocable<SROOK_DECLTYPE(&T::seed), T, std::seed_seq>
    >::type test(int);

    template <class>
    static SROOK_FALSE_TYPE test(...);
public:
    typedef SROOK_DECLTYPE(test<A>(0)) type;
};

} // namespace detail

template <class T>
struct is_random_number_engine_adaptor : detail::is_random_number_engine_adaptor_impl<T>::type {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_random_number_engine_adaptor_v = is_random_number_engine_adaptor<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_random_number_engine_adaptor;

} // namespace srook

#endif
