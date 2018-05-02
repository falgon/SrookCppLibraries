// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_STRONG_ENUM_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_STRONG_ENUM_HPP

#include <srook/config/attribute/visibility.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/noexcept_detection.hpp>

#ifdef __clang__
#    define SROOK_STRONG_ENUM_BEGIN(x) _LIBCPP_DECLARE_STRONG_ENUM(x)
#    define SROOK_STRONG_ENUM_EPILOG(x) _LIBCPP_DECLARE_STRONG_ENUM_EPILOG(x)
#elif (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#    define SROOK_STRONG_ENUM_BEGIN(x) enum class SROOK_ATTRIBUTE_ENUM_VIS_DEFAULT x
#    define SROOK_STRONG_ENUM_EPILOG(x)
#else
#    define SROOK_STRONG_ENUM_BEGIN(x)              \
        struct SROOK_ATTRIBUTE_ENUM_VIS_DEFAULT x { \
            enum lx
#    define SROOK_STRONG_ENUM_EPILOG(x)                                            \
        lx v;                                                                      \
        SROOK_FORCE_INLINE x(lx v) : v_(v) {}                                      \
        SROOK_FORCE_INLINE explicit x(int v) : v_(static_cast<lx>(v)) {}           \
        SROOK_FORCE_INLINE operator int() const SROOK_NOEXCEPT_TRUE { return v_; } \
        }                                                                          \
        ;
#endif

#endif
