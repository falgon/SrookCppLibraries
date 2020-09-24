// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_NUMERIC_DETAIL_FIXED_POINT_SIZED_CONFIG_HPP
#define INCLUDED_SROOK_NUMERIC_DETAIL_FIXED_POINT_SIZED_CONFIG_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/cstdint.hpp>
#include <srook/type_traits/make_signed.hpp>
#include <srook/type_traits/make_unsigned.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <exception>

SROOK_NESTED_NAMESPACE(srook, numeric) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t>
struct fixed_point_traits {
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool is_specialized = false;
    typedef void value_type;
};

template <std::size_t x, typename ValueType>
struct make_size_fixed_point_triats {
    typedef std::size_t size_type;
    typedef ValueType value_type;
    typedef SROOK_DEDUCED_TYPENAME make_unsigned<value_type>::type unsigned_type;
    typedef SROOK_DEDUCED_TYPENAME make_signed<value_type>::type signed_type;
    typedef fixed_point_traits<(x << 1)> next_fixed_point;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR size_type size = x;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool is_specialized = true;
};

#if defined(SROOK_HAS_INT128) && !defined(__STRICT_ANSI__)
template <>
struct fixed_point_traits<128> : make_size_fixed_point_triats<128, srook::int128_t> {};  
#endif
template <>
struct fixed_point_traits<64> : make_size_fixed_point_triats<64, srook::int64_t> {};

template <>
struct fixed_point_traits<32> : make_size_fixed_point_triats<32, srook::int32_t> {};

template <>
struct fixed_point_traits<16> : make_size_fixed_point_triats<16, srook::int16_t> {};

template <>
struct fixed_point_traits<8> : make_size_fixed_point_triats<8, srook::int8_t> {};

template <class B, class N>
SROOK_CONSTEXPR B nextbase_cast(const N& rhs) { return static_cast<B>(rhs); }

} // namespace detail

struct divide_by_zero : std::exception {
    const char* what() const SROOK_NOEXCEPT_TRUE SROOK_OVERRIDE { return "in srook::numeric::sized_fixed_point: divide by zero"; }
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(numeric, srook)

#endif
