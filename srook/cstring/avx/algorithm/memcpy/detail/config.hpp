// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CSTRING_AVX_MEMCPY_CONFIG_DETAIL_HPP
#define INCLUDED_SROOK_CSTRING_AVX_MEMCPY_CONFIG_DETAIL_HPP

#include <srook/config.hpp>
#ifdef _MSC_VER
#   include <intrin.h>
#elif defined(__GNUC__)
#   include <x86intrin.h>
#elif deifned(__clang__)
#   include <x86intrin.h>
#elif !defined(SROOK_CONFIG_ENABLE_AVX512_MEMCPY) && SROOK_HAS_INCLUDE(<immintrin.h>)
#   include <immintrin.h>
#elif defined(SROOK_CONFIG_ENABLE_AVX512_MEMCPY) && SROOK_HAS_INCLUDE(<immintrin.h>) && SROOK_HAS_INCLUDE(<zmmintrin.h>)
#   include <immintrin.h>
#   include <zmmintrin.h>
#elif !define(SROOK_CONFIG_ENABLE_AVX512_MEMCPY)
#   error "This feature needs <immintrin.h>"
#else
#   error "This feature needs <immintrin.h> and <zmmintrin.h>"
#endif

#include <srook/type_traits.hpp>
#include <srook/cstdint.hpp>
#include <cstddef>

namespace srook {
namespace cstring {
namespace avx {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, class U>
struct memcpy_impl_return_type 
    : public enable_if<type_traits::detail::Land<is_convertible<T, void*>, is_convertible<U, const void*>>::value> {};

template <class T, class U>
struct memcpy_return_type 
    : public add_pointer<SROOK_DEDUCED_TYPENAME memcpy_impl_return_type<T, U>::type> {};

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} // namespace avx
} // namespace cstring
} // namespace srook

#endif
