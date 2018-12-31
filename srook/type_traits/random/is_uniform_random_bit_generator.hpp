// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_UNIFORM_RANDOM_BIT_GENERATOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_UNIFORM_RANDOM_BIT_GENERATOR_HPP

#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/detail/sfinae_types.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/type_traits/is_unsigned.hpp>
#include <srook/type_traits/is_constructible.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/utility/declval.hpp>
#include <srook/cstdint.hpp>
#include <vector> // for InputIterator, RandomAccessIterator, OutputIterator

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class G>
struct is_uniform_random_bit_generator_impl {
private:
    template <class T>
    static SROOK_DEDUCED_TYPENAME type_traits::detail::Land<
        is_integral<SROOK_DEDUCED_TYPENAME T::result_type>,
        is_unsigned<SROOK_DEDUCED_TYPENAME T::result_type>,
        is_same<SROOK_DECLTYPE(T::max()), SROOK_DEDUCED_TYPENAME T::result_type>,
        is_same<SROOK_DECLTYPE(T::min()), SROOK_DEDUCED_TYPENAME T::result_type>,
        is_same<SROOK_DECLTYPE(declval<T>()()), SROOK_DEDUCED_TYPENAME T::result_type>
    >::type test(int);

    template <class>
    static SROOK_FALSE_TYPE test(...);
public:
    typedef SROOK_DECLTYPE(test<G>(0)) type;
};

} // namespace detail

template <class T>
struct is_uniform_random_bit_generator : detail::is_uniform_random_bit_generator_impl<T>::type {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_uniform_random_bit_generator_v = is_uniform_random_bit_generator<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_uniform_random_bit_generator;

} // namespace srook
#endif
