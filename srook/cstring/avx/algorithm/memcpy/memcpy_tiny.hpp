#ifndef INCLUDED_SROOK_CSTRING_AVX_ALGORITHM_MEMCPY_MEMCPY_TINY_HPP
#define INCLUDED_SROOK_CSTRING_AVX_ALGORITHM_MEMCPY_MEMCPY_TINY_HPP

#include <srook/cstring/avx/algorithm/memcpy/detail/config.hpp>
#include <srook/cstring/avx/algorithm/memcpy/detail/core.hpp>

namespace srook {
namespace cstring {
namespace avx {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <typename T, typename U>
SROOK_FORCE_INLINE T& cast_value(U* p, std::ptrdiff_t x = 0) SROOK_NOEXCEPT_TRUE { return *(T*)(p + x); }

template <typename T, typename U, typename V>
SROOK_FORCE_INLINE T& assign(U* p1, V* p2, std::ptrdiff_t x = 0) SROOK_NOEXCEPT_TRUE { return cast_value<T>(p1, x) = cast_value<T>(p2, x); }

template <typename T, typename U>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<is_convertible<T, U>::value, SROOK_DEDUCED_TYPENAME std::common_type<T, U>::type>::type
prev_assign(T* p1, U* p2) SROOK_NOEXCEPT_TRUE
{
    return *(p1 - 1) = *(p2 - 1);
}

#define DELIM ;

#define OPT_TB0(X, F)\
    case X : F(dd - X, ss - X); SROOK_ATTRIBUTE_FALLTHROUGH

#define OPT_TB1(X, T)\
    case X : assign<T>(dd, ss, -X)

#define OPT_TB(X, T, F)\
    OPT_TB0((X + 128), F);\
    OPT_TB1(X, T)

#define OPT_TB_N0(X, T, F1, F2)\
    OPT_TB0((X + 128), F1);\
    case X : F2(dd - X, ss - X)

#define OPT_TB_N1(X, F1, F2, B)\
    OPT_TB0((X + 128), F1);\
    case X : F2(dd - X, ss - X); F2(dd - B, ss - B)

#define OPT_TB_N2(X, F1, F2, F3, B)\
    OPT_TB0((X + 128), F1);\
    case X : F2(dd - X, ss - X); F3(dd - B, ss - B)

#define OPT_TB_N1_BIND_16(X)\
    OPT_TB_N1((X + 24), memcpy_avx_128, memcpy_avx_16, 16); break

#define OPT_TB_N2_BIND_16_1(X)\
    OPT_TB_N2((X + 40), memcpy_avx_128, memcpy_avx_32, memcpy_avx_16, 16); break

#define OPT_TB_N1_BIND_32(X)\
    OPT_TB_N1((X + 48), memcpy_avx_128, memcpy_avx_32, 32); break

#define OPT_TB_N2_BIND_16_2(X)\
    OPT_TB_N2((X + 72), memcpy_avx_128, memcpy_avx_64, memcpy_avx_16, 16); break

#define OPT_TB_N2_BIND_32(X)\
    OPT_TB_N2((X + 80), memcpy_avx_128, memcpy_avx_64, memcpy_avx_32, 32); break

#define OPT_TB_N1_BIND_64(X)\
    OPT_TB_N1((X + 96), memcpy_avx_128, memcpy_avx_64, 64); break

#define OPT_TB_TAIL_DEF(P, T1, T2, T3, U1, U2)\
    OPT_TB_N0(P, T1, U1, U2); assign<T1>(dd, ss, -2); break;\
    OPT_TB_N0((P + 1), T2, U1, U2); assign<T2>(dd, ss, -4); break;\
    OPT_TB_N0((P + 2), T2, U1, U2); assign<T2>(dd, ss, -4); break;\
    OPT_TB_N0((P + 3), T3, U1, U2); assign<T3>(dd, ss, -8); break;\
    OPT_TB_N0((P + 4), T3, U1, U2); assign<T3>(dd, ss, -8); break;\
    OPT_TB_N0((P + 5), T3, U1, U2); assign<T3>(dd, ss, -8); break;\
    OPT_TB_N0((P + 6), T3, U1, U2); assign<T3>(dd, ss, -8); break

template <class T, class U>
static SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME memcpy_return_type<T, U>::type
memcpy_tiny(T dst, const U src, std::size_t size)
{
    unsigned char* dd = reinterpret_cast<unsigned char*>(dst) + size;
    const unsigned char* ss = reinterpret_cast<const unsigned char*>(src) + size;

    switch (size) {
        OPT_TB0(128, memcpy_avx_128); case 0: break;
        OPT_TB0(129, memcpy_avx_128); case 1: prev_assign(dd, ss); break;
        OPT_TB(2, std::uint16_t, memcpy_avx_128); break;
        OPT_TB(3, std::uint16_t, memcpy_avx_128); prev_assign(dd, ss); break;
        OPT_TB(4, std::uint32_t, memcpy_avx_128); break;
        OPT_TB(5, std::uint32_t, memcpy_avx_128); prev_assign(dd, ss); break;
        OPT_TB(6, std::uint32_t, memcpy_avx_128); assign<std::uint16_t>(dd, ss, -2); break;
        OPT_TB(7, std::uint32_t, memcpy_avx_128); assign<std::uint32_t>(dd, ss, -4); break;
        OPT_TB(8, std::uint64_t, memcpy_avx_128); break;
        OPT_TB(9, std::uint64_t, memcpy_avx_128); prev_assign(dd, ss); break;
        OPT_TB(10, std::uint64_t, memcpy_avx_128); assign<std::uint16_t>(dd, ss, -2); break;
        OPT_TB(11, std::uint64_t, memcpy_avx_128); assign<std::uint32_t>(dd, ss, -4); break;
        OPT_TB(12, std::uint64_t, memcpy_avx_128); assign<std::uint32_t>(dd, ss, -4); break;
        OPT_TB(13, std::uint64_t, memcpy_avx_128); assign<std::uint64_t>(dd, ss, -8); break;
        OPT_TB(14, std::uint64_t, memcpy_avx_128); assign<std::uint64_t>(dd, ss, -8); break;
        OPT_TB(15, std::uint64_t, memcpy_avx_128); assign<std::uint64_t>(dd, ss, -8); break;
        OPT_TB0(144, memcpy_avx_128); case 16: memcpy_avx_16(dd - 16, ss - 16); break;
        OPT_TB0(145, memcpy_avx_128); case 17: memcpy_avx_16(dd - 17, ss - 17); prev_assign(dd, ss); break;
        OPT_TB_TAIL_DEF(18, std::uint16_t, std::uint32_t, std::uint64_t, memcpy_avx_128, memcpy_avx_16);
        SROOK_PP_LOOP_DELIM(OPT_TB_N1_BIND_16, 7, DELIM);
        OPT_TB0(160, memcpy_avx_128); case 32: memcpy_avx_32(dd - 32, ss - 32); break;
        OPT_TB0(161, memcpy_avx_128); case 33: memcpy_avx_32(dd - 33, ss - 33); prev_assign(dd, ss); break;
        OPT_TB_TAIL_DEF(34, std::uint16_t, std::uint32_t, std::uint64_t, memcpy_avx_128, memcpy_avx_32);
        SROOK_PP_LOOP_DELIM(OPT_TB_N2_BIND_16_1, 8, DELIM);
        SROOK_PP_LOOP_DELIM(OPT_TB_N1_BIND_32, 15, DELIM);
        OPT_TB0(192, memcpy_avx_128); case 64: memcpy_avx_64(dd - 64, ss - 64); break;
        OPT_TB0(193, memcpy_avx_128); case 65: memcpy_avx_64(dd - 65, ss - 65); prev_assign(dd, ss); break;
        OPT_TB_TAIL_DEF(66, std::uint16_t, std::uint32_t, std::uint64_t, memcpy_avx_128, memcpy_avx_64);
        SROOK_PP_LOOP_DELIM(OPT_TB_N2_BIND_16_2, 8, DELIM);
        SROOK_PP_LOOP_DELIM(OPT_TB_N2_BIND_32, 16, DELIM);
        SROOK_PP_LOOP_DELIM(OPT_TB_N1_BIND_64, 31, DELIM);
        case 256: memcpy_avx_256(dd - 256, ss - 256); break;
    }
    return dst;
}

#undef DELIM
#undef OPT_TB
#undef OPT_TB0
#undef OPT_TB1
#undef OPT_TB_N0
#undef OPT_TB_N1
#undef OPT_TB_N2
#undef OPT_TB_N2_BIND_16_1
#undef OPT_TB_N2_BIND_16_2
#undef OPT_TB_N2_BIND_32
#undef OPT_TB_N1_BIND_32
#undef OPT_TB_N1_BIND_16
#undef OPT_TB_N1_BIND_64
#undef OPT_TB_TAIL_DEF

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} // namespace avx
} // namespace cstring
} // namespace srook

#endif
