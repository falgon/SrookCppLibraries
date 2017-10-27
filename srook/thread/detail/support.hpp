#ifndef INCLUDED_SROOK_THREADS_DETAIL_THREADING_SUPPORT_HPP
#define INCLUDED_SROOK_THREADS_DETAIL_THREADING_SUPPORT_HPP
#include <srook/config/compiler/pragma/core.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/env.hpp>

#if SROOK_HAS_THREADS
#    include <srook/thread/detail/support/types.hpp>
#    include <srook/thread/detail/support/primitive.hpp>

#    if SROOK_HAS_THREAD_API_EXTERNAL
#        define SROOK_THREAD_ABI_VISIBILITY SROOK_ATTRIBUTE_FUNCTION_VIS_DEFAULT
#    else
#        define SROOK_THREAD_ABI_VISIBILITY inline SROOK_ATTRIBUTE_INLINE_VISIBILITY
#    endif

#    ifdef _LIBCPP_NO_THREAD_SAFETY_ANALYSIS
#        define SROOK_NO_THREAD_SAFETY_ANALYSIS _LIBCPP_NO_THREAD_SAFETY_ANALYSIS
#    elif defined(__FreeBSD__) && defined(__clang__) && __has_attribute(no_thread_safety_analysis)
#        define SROOK_NO_THREAD_SAFETY_ANALYSIS __attribute__((no_thread_safety_analysis))
#    else
#        define SROOK_NO_THREAD_SAFETY_ANALYSIS
#    endif

#else
#    error "This environment is not supported multi threading"
#endif
#endif
