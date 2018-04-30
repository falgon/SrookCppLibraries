// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CSTRING_AVX_HAS_INTEL_KNL_FEATURES_HPP
#define INCLUDED_SROOK_CSTRING_AVX_HAS_INTEL_KNL_FEATURES_HPP

#include <srook/config.hpp>
#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1300)
#   include <immintrin.h>
#else
#   include <cstdint>
#   ifdef _MSC_VER
#       include <srook/config/compiler/msvc/includes/intrin.h>
#       include <intrin.h>
#   endif
#endif

namespace srook {
namespace cstring {
namespace avx {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {
    
#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1300)
SROOK_CONSTEXPR bool has_intel_knl_features_impl() SROOK_NOEXCEPT_TRUE
{
    SROOK_CONSTEXPR_OR_CONST unsigned long knl_features = (_FEATURE_AVX512F | _FEATURE_AVX512ER | _FEATURE_AVX512PF | _FEATURE_AVX512CD );
    return _may_i_use_cpu_feature(knl_features);
}
#else

SROOK_FORCE_INLINE void do_cpuid(std::uint32_t eax, std::uint32_t ecx, std::uint32_t* abcd)
{
#ifdef _MSC_VER
    __cpuidex(abcd, eax, ecx);
#else
    std::uint32_t ebx = 0, edx = 0;
#   if defined(__i386__) && defined (__PIC__)
     __asm__ ( "movl %%ebx, %%edi \n\t cpuid \n\t xchgl %%ebx, %%edi" : "=D" (ebx),
#   else
     __asm__ ( "cpuid" : "+b" (ebx),
#   endif
    "+a" (eax), "+c" (ecx), "=d" (edx) );
     abcd[0] = eax; abcd[1] = ebx; abcd[2] = ecx; abcd[3] = edx;
#endif
}

bool check_xcr0_zmm()
{
    std::uint32_t xcr0 = 0; 
    std::uint32_t zmm_ymm_xmm = (7 << 5) | (1 << 2) | (1 << 1);
#ifdef _MSC_VER
    xcr0 = reinterpret_cast<std::uint32_t>(_xgetbv(0));
#else
    __asm__ ("xgetbv" : "=a" (xcr0) : "c" (0) : "%edx" );
#endif
    return ((xcr0 & zmm_ymm_xmm) == zmm_ymm_xmm);
}

bool has_intel_knl_features_impl()
{
    std::uint32_t abcd[4];
    std::uint32_t osxsave_mask = (1 << 27);
    std::uint32_t avx512_knl_mask = (1 << 16) | // AVX-512F
                                    (1 << 26) | // AVX-512PF
                                    (1 << 27) | // AVX-512ER
                                    (1 << 28);  // AVX-512CD
    do_cpuid(7, 0, abcd);
    if ((abcd[1] & avx512_knl_mask) != avx512_knl_mask) return false;

    do_cpuid(1, 0, abcd);
    if ((abcd[2] & osxsave_mask) != osxsave_mask) return false;
    if (!check_xcr0_zmm()) return false;
    return true;
}
#endif

} // namespace detail

static bool has_intel_knl_features()
{
    static int knl_features_available = -1;
    if (knl_features_available < 0) knl_features_available = detail::has_intel_knl_features_impl();
    return knl_features_available;
}

SROOK_INLINE_NAMESPACE_END
} // namespace avx
} // namespace cstring
} // namespace srook

#endif
