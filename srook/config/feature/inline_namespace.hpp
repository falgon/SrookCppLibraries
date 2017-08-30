#ifndef INCLUDED_SROOK_CONFIG_FEATURE_INLINE_NAMESPACE_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_INLINE_NAMESPACE_HPP

#include<srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include<srook/config/cpp_predefined/macro_names.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#define SROOK_INLINE_NAMESPACE(x) inline namespace x { 
#define SROOK_INLINE_NAMESPACE_END }
#else
#define SROOK_INLINE_NAMESPACE(x)
#define SROOK_INLINE_NAMESPACE_END
#endif

#endif
