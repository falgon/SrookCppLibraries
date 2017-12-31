// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_THREAD_LOCAL_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_THREAD_LOCAL_HPP

#include <srook/config/compiler.hpp>
#include <srook/config/cpp_predefined.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    define SROOK_TLS thread_local
#elif defined(_GLIBCXX_HAVE_TLS) || SROOK_COMPILER_IS_ILE || defined(__GNUC__)
#    define SROOK_TLS __thread
#elif defined(_MSC_VER) || defined(_hpux)
#    define SROOK_TLS __declspec(thread)
#elif defined(__has_feature)
#    if __has_feature(cxx_thread_local)
#        define SROOK_TLS thread_local
#    endif
#    if __has_feature(c_thread_local)
#        define SROOK_TLS _Thread_local
#    endif
#endif

#endif
