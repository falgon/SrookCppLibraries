// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_CURRENT_FUNCTION_HPP
#define INCLUDED_SROOK_CONFIG_CURRENT_FUNCTION_HPP

#ifndef INCLUDED_SROOK_CONFIG_FEATURE_INLINE_NAMESPACE_HPP
#   include <srook/config/feature/inline_namespace.hpp>
#endif
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_FORCE_INLINE_HPP
#   include <srook/config/attribute/force_inline.hpp>
#endif
#ifndef INCLUDED_SROOK_CONFIG_USER_CONFIG_HPP
#   include <srook/config/user_config.hpp>
#endif

namespace srook {
namespace config {

SROOK_FORCE_INLINE void current_function_helper()
{
#if defined(SROOK_CONFIG_DISABLE_CURRENT_FUNCTION)
#   define SROOK_CURRENT_FUNCTION "(unknown)"
#elif defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#   define SROOK_CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#   define SROOK_CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#   define SROOK_CURRENT_FUNCTION __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#   define SROOK_CURRENT_FUNCTION __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#   define SROOK_CURRENT_FUNCTION __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#   define SROOK_CURRENT_FUNCTION __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#   define SROOK_CURRENT_FUNCTION __func__
#elif defined(BOOST_CURRENT_FUNCTION)
#   define SROOK_CURRENT_FUNCTION BOOST_CURRENT_FUNCTION
#else
#   define SROOK_CURRENT_FUNCTION "(unknown)"
#endif
}

} // namespace config
} // namespace srook

#endif
