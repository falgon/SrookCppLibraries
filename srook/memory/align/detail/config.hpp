// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_DETAIL_CONFIG_HPP
#define INCLUDED_SROOK_MEMORY_DETAIL_CONFIG_HPP

#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature/noexcept.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <cstddef>
#ifdef __cplusplus
#   include <cassert>
#else
extern "C" {
#   include <assert.h>
}
#endif

#endif
