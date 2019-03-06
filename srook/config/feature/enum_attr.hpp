// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_ENUM_ATTR_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_ENUM_ATTR_HPP

#include <srook/config/attribute/deprecated.hpp>

#if __cpp_enumerator_attributes
#    define SROOK_ENUM_ATTR SROOK_DEPRECATED
#    define SROOK_ENUM_ATTR_MESSAGE(x) SROOK_DEPRECATED_MESSAGE(x)
#else
#    define SROOK_ENUM_ATTR
#    define SROOK_ENUM_ATTR_MESSAGE(x)
#endif

#endif
