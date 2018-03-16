// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_RANDOM_NUMBER_ENGINE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_RANDOM_NUMBER_ENGINE_HPP

#include <srook/type_traits/random/is_uniform_random_bit_generator.hpp>
#include <srook/type_traits/add_const.hpp>
#include <random> // for std::seed_seq
#include <ostream>
#include <istream>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class E>
struct is_random_number_engine_impl {
private:
    template <class T>
    static SROOK_DEDUCED_TYPENAME type_traits::detail::Land<
        is_uniform_random_bit_generator<T>,
        is_default_constructible<T>,
        is_constructible<T, SROOK_DEDUCED_TYPENAME add_const<T>::type>,
        is_constructible<T, SROOK_DEDUCED_TYPENAME T::result_type>,
        is_constructible<T, std::seed_seq>,
        is_same<SROOK_DECLTYPE(declval<T&>().seed()), void>,
        is_same<SROOK_DECLTYPE(declval<T&>().seed(declval<SROOK_DEDUCED_TYPENAME T::result_type>())), void>,
        is_same<SROOK_DECLTYPE(declval<T&>().discard(declval<unsigned long long>())), void>,
        is_same<SROOK_DECLTYPE(declval<T&>() == declval<T&>()), bool>,
        is_same<SROOK_DECLTYPE(declval<T&>() != declval<T&>()), bool>,
        is_same<SROOK_DECLTYPE(declval<std::ostream&>() << declval<T&>()), SROOK_DECLTYPE(declval<std::ostream&>())&>,
        is_same<SROOK_DECLTYPE(declval<std::istream&>() >> declval<T&>()), SROOK_DECLTYPE(declval<std::istream&>())&>
    >::type test(int);

    template <class>
    static SROOK_FALSE_TYPE test(...);
public:
    typedef SROOK_DECLTYPE(test<E>(0)) type;
};

} // namespace detail

template <class E>
struct is_random_number_engine : detail::is_random_number_engine_impl<E>::type {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class E>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_random_number_engine_v = is_random_number_engine<E>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_random_number_engine;

} // namespace srook

#endif
