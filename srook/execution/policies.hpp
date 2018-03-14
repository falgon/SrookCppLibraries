// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_EXECUTION_POLICIES_HPP
#define INCLUDED_SROOK_EXECUTION_POLICIES_HPP

#include <srook/execution/config.hpp>

SROOK_NESTED_NAMESPACE(srook, execution) {
SROOK_INLINE_NAMESPACE(v1)

struct SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT sequenced_policy {
    SROOK_EXPLICIT sequenced_policy() SROOK_DEFAULT
};
struct SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT parallel_policy {
    SROOK_EXPLICIT parallel_policy() SROOK_DEFAULT
};
struct SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT parallel_unsequenced_policy {
    SROOK_EXPLICIT parallel_unsequenced_policy() SROOK_DEFAULT
};
#if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
extern const sequenced_policy seq();
extern const parallel_policy par();
extern const parallel_unsequenced_policy par_unseq();
#else
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR sequenced_policy seq{};
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR parallel_policy par{};
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR parallel_unsequenced_policy par_unseq{};
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(execution, srook)

#endif
