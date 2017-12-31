// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CSTRING_AVX_MEMCPY_DETAIL_CORE_HPP
#define INCLUDED_SROOK_CSTRING_AVX_MEMCPY_DETAIL_CORE_HPP

#include <srook/cstring/avx/algorithm/memcpy/detail/config.hpp>
#include <srook/cstring/avx/has_intel_knl_features.hpp>
#include <srook/preprocessor/detail/loop_delim.hpp>

namespace srook {
namespace cstring {
namespace avx {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

#define DEF_256UNROLL(X)\
    __m256i SROOK_PP_CONCAT(m, X) = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(src))

#define STORE_256UNROLL(X)\
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(dst) + X - 1, SROOK_PP_CONCAT(m, X))

#define DEF_512UNROLL(X)\
    __m512i SROOK_PP_CONCAT(m, X) = _mm512_loadu_si512(reinterpret_cast<const __m512i*>(src))

#define STORE_512UNROLL(X)\
    _mm512_storeu_si512(reinterpret_cast<__m512i*>(dst) + X - 1, SROOK_PP_CONCAT(m, X))

#define DELIMITOR ;

template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_16_impl(T dst, const U src)
{
    __m128i m0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(src));
    _mm_storeu_si128(reinterpret_cast<__m128i*>(dst), m0);
}

template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_32_impl(T dst, const U src)
{
    DEF_256UNROLL(1);
    STORE_256UNROLL(1);
}

template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_64_impl(T dst, const U src)
{
    SROOK_PP_LOOP_DELIM(DEF_256UNROLL, 2, DELIMITOR);
    SROOK_PP_LOOP_DELIM(STORE_256UNROLL, 2, DELIMITOR);
}

template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_128_impl(T dst, const U src)
{
    SROOK_PP_LOOP_DELIM(DEF_256UNROLL, 4, DELIMITOR);
    SROOK_PP_LOOP_DELIM(STORE_256UNROLL, 4, DELIMITOR);
}

template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_256_impl(T dst, const U src)
{
    SROOK_PP_LOOP_DELIM(DEF_256UNROLL, 8, DELIMITOR);
    SROOK_PP_LOOP_DELIM(STORE_256UNROLL, 8, DELIMITOR);
}

} // namespace detail

template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_16(T dst, const U src)
{
    detail::memcpy_avx_16_impl(dst, src);
}

template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_32(T dst, const U src)
{
    detail::memcpy_avx_32_impl(dst, src);
}

#if defined(SROOK_CONFIG_ENABLE_AVX512_MEMCPY)
template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_64(T dst, const U src)
{
    if (has_intel_knl_features()) {
        DEF_512UNROLL(1);
        STORE_512UNROLL(1);
    } else {
        detail::memcpy_avx_64_impl(dst, src);
    }
}

template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_128(T dst, const U src)
{
    if (has_intel_knl_features()) {
        SROOK_PP_LOOP_DELIM(DEF_512UNROLL, 2, DELIMITOR);
        SROOK_PP_LOOP_DELIM(STORE_512UNROLL, 2, DELIMITOR);
    } else {
        detail::memcpy_avx_128_impl(dst, src);
    }
}

template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_256(T dst, const U src)
{
    if (has_intel_knl_features()) {
        SROOK_PP_LOOP_DELIM(DEF_512UNROLL, 3, DELIMITOR);
        SROOK_PP_LOOP_DELIM(STORE_512UNROLL, 3, DELIMITOR);
    } else {
        detail::memcpy_avx_256_impl(dst, src);
    }
}
#else
template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_64(T dst, const U src)
{
    detail::memcpy_avx_64_impl(dst, src);
}

template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_128(T dst, const U src)
{
    detail::memcpy_avx_128_impl(dst, src);
}

template <typename T, typename U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_impl_return_type<T, U>::type
memcpy_avx_256(T dst, const U src)
{
    detail::memcpy_avx_256_impl(dst, src);
}
#endif
SROOK_INLINE_NAMESPACE_END
} // namespace avx
} // namespace cstring
} // namespace srook

#undef DEF_256UNROLL
#undef DEF_512UNROLL
#undef STORE_256UNROLL
#undef STORE_512UNROLL
#undef DELIMITOR

#endif
