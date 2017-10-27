// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_DETAIL_TMETHOD_TEMPLATE_IMPLICIT_INSTANTIATION_HIDDEN_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_VISIBILITY_DETAIL_TMETHOD_TEMPLATE_IMPLICIT_INSTANTIATION_HIDDEN_HPP

#include <srook/config/user_config.hpp>

#if SROOK_CONFIG_DISABLE_VISIBILITY_ANNOTATIONS
#	define SROOK_ATTRIBUTE_METHOD_TEMPLATE_IMPLICIT_INSTANTIATION_VIS_HIDDEN __attribute__((__visibility__("hidden")))
#else
#	define SROOK_ATTRIBUTE_METHOD_TEMPLATE_IMPLICIT_INSTANTIATION_VIS_HIDDEN
#endif

#endif
