// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_SEED_SEQUENCE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_SEED_SEQUENCE_HPP

#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/type_traits/is_unsigned.hpp>
#include <srook/type_traits/is_constructible.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/cstdint.hpp>
#include <vector> // for InputIterator, RandomAccessIterator, OutputIterator

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

typedef std::vector<srook::uint_least32_t>::iterator uileast32_iter_t;
typedef uileast32_iter_t mutable_raiter_t;
typedef uileast32_iter_t output_iter_t;

template <class S>
struct is_seed_sequence_impl {
private:
    template <class T>
    static SROOK_DEDUCED_TYPENAME type_traits::detail::Land<
        is_integral<SROOK_DEDUCED_TYPENAME T::result_type>,
        is_unsigned<SROOK_DEDUCED_TYPENAME T::result_type>,
        bool_constant<sizeof(SROOK_DEDUCED_TYPENAME S::result_type) >= 4>,
        is_default_constructible<S>,
        is_constructible<S, uileast32_iter_t, uileast32_iter_t>,
        is_constructible<S, std::initializer_list<SROOK_DEDUCED_TYPENAME S::result_type>>,
        is_same<SROOK_DECLTYPE(declval<S&>().generate(mutable_raiter_t(), mutable_raiter_t())), void>,
        is_same<SROOK_DECLTYPE(declval<const S&>().size()), std::size_t>,
        is_same<SROOK_DECLTYPE(declval<const S&>().param(output_iter_t())), void>
    >::type test(int);

    template <class>
    static SROOK_FALSE_TYPE test(...);
public:
    typedef SROOK_DECLTYPE(test<S>(0)) type;
};

} // namespace detail

template <class S>
struct is_seed_sequence : detail::is_seed_sequence_impl<S>::type {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_seed_sequence_v = is_seed_sequence<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_seed_sequence;

} // namespace srook
#endif
