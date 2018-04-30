// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_CSTRING_MEMCPY_HPP
#define INCLUDED_CSTRING_MEMCPY_HPP

#include <srook/config/user_config.hpp>

#if (defined(SROOK_CONFIG_ENABLE_AVX512_MEMCPY) || defined(SROOK_CONFIG_ENABLE_AVX_MEMCPY)) && !defined(SROOK_MEMCPY) && !defined(SROOK_MEMCPY_NONCONST)
#   include <srook/cstring/avx/algorithm/memcpy/memcpy.hpp>
#   define SROOK_MEMCPY_NONCONST(x, y, z) srook::cstring::avx::memcpy(x, y, z)
#endif

#if !defined(SROOK_CONFIG_CHECK_MEMCPY) && !defined(SROOK_MEMCPY) && !defined(SROOK_MEMCPY_NONCONST)
#   if defined(__GNUC__) || defined(__IBMCPP__)
#       define SROOK_MEMCPY(x, y, z) __builtin_memcpy(x, y, z)
#   elif defined(__INTEL_COMPILER) && !defined(SROOK_CONFIG_ENABLE_AVX512_MEMCPY)
#       define SROOK_MEMCPY(x, y, z) _intel_fast_memcpy(x, y, z)
#   endif
#elif !defined(SROOK_MEMCPY_NONCONST)
#   if defined(__GNUC__) || defined(__IBMCPP__)    
#       define BOS0(X) __builtin_object_size (X, 0)
#       define SROOK_MEMCPY(x, y, z) __builtin___memcpy_chk(x, y, z, BOS0(x))
#   elif __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 34 && defined(__linux__)
#           define SROOK_MEMCPY_NONCONST(x, y, z) ::memcpy(x, y, z)
#           define _FORTIFY_SOURCE
#           include <unistd.h>
#           include <features.h>
#           include <cstring>
#   endif
#endif

#if !defined(SROOK_MEMCPY_NONCONST)
#   if defined(__x86_64__) && defined(__linux__) && !defined(__CYGWIN__)
#       include <cstdint>
#       include <unistd.h>
#       include <features.h>
        extern "C" void* memcpy(void*, void*, std::size_t);
#       define SROOK_MEMCPY_NONCONST(x, y, z) ::memcpy(x, y, z)
#   else
#       include <cstring>
#       define SROOK_MEMCPY_NONCONST(x, y, z) std::memcpy(x, y, z)
#   endif
#endif

#include <srook/type_traits.hpp>

namespace srook {
namespace cstring {
SROOK_INLINE_NAMESPACE(v1)

#ifdef SROOK_MEMCPY

template <class T, class U>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME add_pointer<
    SROOK_DEDUCED_TYPENAME enable_if<type_traits::detail::Land<is_convertible<T, void*>, is_convertible<U, const void*>>::value>::type
>::type
memcpy(T p1, U p2, std::size_t n)
{
    return SROOK_MEMCPY(p1, p2, n);
}

#elif defined(SROOK_MEMCPY_NONCONST)

template <class T, class U>
SROOK_DEDUCED_TYPENAME add_pointer<
    SROOK_DEDUCED_TYPENAME enable_if<type_traits::detail::Land<is_convertible<T, void*>, is_convertible<U, const void*>>::value>::type
>::type
memcpy(T p1, U p2, std::size_t n)
{
    return SROOK_MEMCPY_NONCONST(p1, p2, n);
}

#endif
//#undef SROOK_MEMCPY_NONCONST

SROOK_INLINE_NAMESPACE_END
} // namespace cstring

using cstring::memcpy;

} // namespace srook

#endif
