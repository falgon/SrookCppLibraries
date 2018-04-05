// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_PRIMES_HPP
#define INCLUDED_SROOK_TMPL_VT_PRIMES_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>

#if SROOK_CPP_VARIADIC_TEMPLATES

#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/filterD.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <srook/utility/index_sequence.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/mpl/constant_sequence/algorithm/partial_tail.hpp>
#include <srook/mpl/constant_sequence/algorithm/concat.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, class>
struct sieve_from_value;

template <std::size_t p, std::size_t lhs>
struct sieve_from_value<std::index_sequence<p>, std::index_sequence<lhs>>
    : bool_constant<lhs % p != 0> {};

template <class> struct unwrap_index_seq;
template <std::size_t n>
struct unwrap_index_seq<std::index_sequence<n>>
    : integral_constant<std::size_t, n> {};

template <class> struct to_index_seq;
template <class... Xs>
struct to_index_seq<packer<Xs...>>
    : type_constant<std::index_sequence<unwrap_index_seq<Xs>::value...>> {};

template <class> struct sieve_impl;
template <std::size_t p, std::size_t... vals>
struct sieve_impl<std::index_sequence<p, vals...>>
    : srook::constant_sequence::concat<
        std::index_sequence<p>,
        SROOK_DEDUCED_TYPENAME sieve_impl<
            SROOK_DEDUCED_TYPENAME to_index_seq<SROOK_DEDUCED_TYPENAME filterD<bind<sieve_from_value, std::index_sequence<p>>, std::index_sequence<vals>...>::type>::type
        >::type
    > {};

template <>
struct sieve_impl<std::index_sequence<>> 
    : type_constant<std::index_sequence<>> {};


template <class> struct sieve;
template <std::size_t... vals>
struct sieve<std::index_sequence<vals...>> 
    : type_constant<packer<SROOK_DEDUCED_TYPENAME sieve_impl<std::index_sequence<vals...>>::type>> {};

} // namespace detail

template <unsigned n>
struct primes 
    : detail::sieve<SROOK_DEDUCED_TYPENAME srook::constant_sequence::partial_tail<2, std::make_index_sequence<n>>::type> {};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
#endif
