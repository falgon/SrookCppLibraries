#ifndef INCLUDED_SROOK_CONFIG_FEATURE_INLINE_VARIABLE_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_INLINE_VARIABLE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>

#if SROOK_CPP_INLINE_VARIABLES
#    define SROOK_INLINE_VARIABLE inline
#else
#    define SROOK_INLINE_VARIABLE
#endif

#endif
