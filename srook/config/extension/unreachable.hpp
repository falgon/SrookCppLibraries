// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_EXTENSION_UNREACHBLE_HPP
#define INCLUDED_SROOK_CONFIG_EXTENSION_UNREACHBLE_HPP

#ifdef __GNUC__
#   include <srook/config/compiler/gcc.hpp>
#   if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
#       define SROOK_UNREACHABLE_RETURN(x) __builtin_unreachable()
#       define SROOK_UNREACHABLE() __builtin_unreachable()
#   endif
#elif defined(__clang__)
#   if __has_builtin(__builtin_unreachable)
#       define SROOK_UNREACHABLE_RETURN(x) __builtin_unreachable()
#       define SROOK_UNREACHABLE() __builtin_unreachable()
#   endif
#elif defined(_MSC_VER)
#   define SROOK_UNREACHABLE_RETURN(x) __assume(0)
#   define SROOK_UNREACHABLE() __assume(0)
#endif

#ifndef SROOK_UNREACHABLE_RETURN
#   include <srook/config/cpp_predefined/macro_names.hpp>
#   ifdef SROOK_CPLUSPLUS
#       include <cstdlib>
#       define SROOK_UNREACHABLE_RETURN(x) do { std::abort() } while(0)
#   else
#       include <stdlib.h>
#       define SROOK_UNREACHABLE_RETURN(x) do { ::abort(); } while(0)
#   endif
#endif
#endif
