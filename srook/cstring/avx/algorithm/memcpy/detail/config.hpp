// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CSTRING_AVX_MEMCPY_CONFIG_DETAIL_HPP
#define INCLUDED_SROOK_CSTRING_AVX_MEMCPY_CONFIG_DETAIL_HPP

#include <srook/config.hpp>
#if SROOK_HAS_INCLUDE(<immintrin.h>)
#   include <immintrin.h>
#else
#   error This feature needs <immintrin.h>
#endif
#include <srook/type_traits.hpp>
#include <cstddef>
#include <cstdint>

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
