// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_HASH_SHA_DETAIL_SUM_HPP
#define INCLUDED_SROOK_HASH_SHA_DETAIL_SUM_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#ifdef __GNUC__
#   pragma GCC system_header
#elif defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang ignored "-Wvariadic-macros"
#endif

#include <srook/hash/sha2/detail/config.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/utility/index_sequence.hpp>
#include <srook/tmpl/vt/first.hpp>

SROOK_NESTED_NAMESPACE(srook, hash) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class... Ts>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Land<is_integral<Ts>...>::value, 
    srook::array<SROOK_DEDUCED_TYPENAME tmpl::vt::first<Ts...>::type, sizeof...(Ts)>
>::type
sum(Ts... ts)
{
    return srook::make_array(ts...);
}

template <class IntegralType, std::size_t x, std::size_t... I>
SROOK_CONSTEXPR srook::array<IntegralType, x>
sum(const srook::array<IntegralType, x>& l, const srook::array<IntegralType, x>& r, srook::utility::index_sequence<I...>)
{
    return sum((l[I] + r[I])...);
}

template <class IntegralType, std::size_t x>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<is_integral<IntegralType>::value, srook::array<IntegralType, x>>::type
sum(const srook::array<IntegralType, x>& l, const srook::array<IntegralType, x>& r)
{
    return sum(l, r, SROOK_DEDUCED_TYPENAME srook::utility::make_index_sequence_type<x>::type());
}

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(hash, srook)

#ifdef __clang__
#   pragma clang  diagnostic pop
#endif
#endif
