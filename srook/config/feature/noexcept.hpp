// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_NOEXCEPT_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_NOEXCEPT_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if defined(_MSC_VER) && (!defined(__clang__) || (_MSC_VER < 1910))
#    if _MSC_VER < 1910
#        define SROOK_NOEXCEPT(...) _NOEXCEPT(__VA_ARGS__)
#        define SROOK_MEMFN_NOEXCEPT(...) SROOK_NOEXCEPT(__VA_ARGS__)
#        define SROOK_NOEXCEPT_TRUE SROOK_NOEXCEPT(true)
#   else
#       define SROOK_NOEXCEPT(...) noexcept(noexcept(__VA_ARGS__))
#       define SROOK_MEMFN_NOEXCEPT(...) SROOK_NOEXCEPT(__VA_ARGS__)
#       define SROOK_NOEXCEPT_TRUE SROOK_NOEXCEPT(true)
#   endif
#elif defined(__SUNPRO_CC) && __SUNPRO_CC <= 0x5150
#    define SROOK_NOEXCEPT(...) noexcept(noexcept(__VA_ARGS__))
#    define SROOK_MEMFN_NOEXCEPT(...) SROOK_NOEXCEPT(__VA_ARGS__)
#    define SROOK_NOEXCEPT_TRUE SROOK_NOEXCEPT(true)
#elif (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#    if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 180021114)
#        define SROOK_NOEXCEPT(...) noexcept(noexcept(__VA_ARGS__))
#        define SROOK_MEMFN_NOEXCEPT(...) SROOK_NOEXCEPT(__VA_ARGS__)
#        define SROOK_NOEXCEPT_TRUE noexcept(true)
#    else
// for this issue : https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52869
#        if defined(__GNUC__) or defined(__GNUG__)
#            define SROOK_NOEXCEPT(...) noexcept(false)
#            define SROOK_MEMFN_NOEXCEPT(...) SROOK_NOEXCEPT(__VA_ARGS__)
#        else
#            define SROOK_NOEXCEPT(...) noexcept(noexcept(__VA_ARGS__))
#            define SROOK_MEMFN_NOEXCEPT(...) SROOK_NOEXCEPT(__VA_ARGS__)
#        endif
#        define SROOK_NOEXCEPT_TRUE noexcept(true)
#    endif
#else
#    define SROOK_NOEXCEPT_TRUE throw()
#    define SROOK_NOEXCEPT(...)
#    define SROOK_MEMFN_NOEXCEPT(...) SROOK_NOEXCEPT(__VA_ARGS__)
#endif

#endif
