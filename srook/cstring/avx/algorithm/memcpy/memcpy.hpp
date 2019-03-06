// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CSTRING_AVX_ALGORITHM_MEMCPY_MEMCPY_HPP
#define INCLUDED_SROOK_CSTRING_AVX_ALGORITHM_MEMCPY_MEMCPY_HPP

#include <srook/cstring/avx/algorithm/memcpy/memcpy_tiny.hpp>
#include <srook/preprocessor/detail/loop_comma.hpp>

namespace srook {
namespace cstring {
namespace avx {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

#define VAL_DECL(X)\
    SROOK_PP_CONCAT(c, X)

#define UNROLL_VAL1(X)\
    SROOK_PP_CONCAT(c, X) = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(src) + X - 1)

#define UNROLL_VAL2(X)\
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(dst) + X - 1, SROOK_PP_CONCAT(c, X))

#define DELIM ;

SROOK_FORCE_INLINE void do_memcpy(unsigned char* dst, const unsigned char* src, std::size_t& size)
{
    for (__m256i SROOK_PP_LOOP_COMMA(VAL_DECL, 8); size >= 256; size -= 256) {
        SROOK_PP_LOOP_DELIM(UNROLL_VAL1, 8, DELIM);
        _mm_prefetch(reinterpret_cast<const char*>(src + 512), _MM_HINT_NTA);
        src += 256;
        SROOK_PP_LOOP_DELIM(UNROLL_VAL2, 8, DELIM);
        dst += 256;
    }
}

#undef VAL_DECL
#undef UNROLL_VAL1
#undef UNROLL_VAL2
#undef DELIM

} // namespace detail

template <class T, class U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME detail::memcpy_return_type<T, U>::type
memcpy(T d, U s, std::size_t size)
{
    unsigned char* dst = reinterpret_cast<unsigned char*>(d);
    const unsigned char* src = reinterpret_cast<const unsigned char*>(s);
    static std::size_t cachesize = 0x200000;

    if (size <= 256) {
        detail::memcpy_tiny(dst, src, size);
        _mm256_zeroupper();
        return dst;
    }
    
    std::size_t padding = (32 - (reinterpret_cast<std::size_t>(dst) & 31)) & 31;
    __m256i head = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(src));
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(dst), head);
    dst += padding;
    src += padding;
    size -= padding;

    if (size <= cachesize) {
        detail::do_memcpy(dst, src, size);
    } else {
        detail::do_memcpy(dst, src, size);
        _mm_sfence();
    }
    detail::memcpy_tiny(dst, src, size);
    _mm256_zeroupper();
    return d;
}

SROOK_INLINE_NAMESPACE_END
} // namespace avx
} // namespace cstring
} // namespace srook

#endif
