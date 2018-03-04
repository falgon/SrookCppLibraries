// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_EXTENSION_UNREACHBLE_HPP
#define INCLUDED_SROOK_CONFIG_EXTENSION_UNREACHBLE_HPP

#ifdef __GNUC__
#   include <srook/config/compiler/gcc.hpp>
#   if SROOK_GCC_VERSION >= 40800
#       define SROOK_UNREACHABLE_RETURN(x) __builtin_unreachable()
#   endif
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
