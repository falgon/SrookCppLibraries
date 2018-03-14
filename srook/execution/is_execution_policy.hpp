// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_EXECUTION_IS_EXECUTION_POLICY_HPP
#define INCLUDED_SROOK_EXECUTION_IS_EXECUTION_POLICY_HPP

#include <srook/execution/config.hpp>
#include <srook/execution/policies.hpp>
#include <srook/type_traits/true_false_type.hpp>

SROOK_NESTED_NAMESPACE(srook, execution) {
SROOK_INLINE_NAMESPACE(v1)

template <class>
struct is_execution_policy : SROOK_FALSE_TYPE {};

#define SROOK_IS_EXECUTION_POLICY_TRUE_DEF(X)\
    template <>\
    struct is_execution_policy<X> : SROOK_TRUE_TYPE {}

SROOK_IS_EXECUTION_POLICY_TRUE_DEF(srook::execution::sequenced_policy);
SROOK_IS_EXECUTION_POLICY_TRUE_DEF(srook::execution::parallel_policy);
SROOK_IS_EXECUTION_POLICY_TRUE_DEF(srook::execution::parallel_unsequenced_policy);

#ifdef SROOK_HAS_STD_EXECUTION
SROOK_IS_EXECUTION_POLICY_TRUE_DEF(std::execution::sequenced_policy);
SROOK_IS_EXECUTION_POLICY_TRUE_DEF(std::execution::parallel_policy);
SROOK_IS_EXECUTION_POLICY_TRUE_DEF(std::execution::parallel_unsequenced_policy);
#endif
#ifdef SROOK_HAS_STD_EXPERIMENTAL_EXECUTION_POLICY
SROOK_IS_EXECUTION_POLICY_TRUE_DEF(std::experimental::parallel::sequential_execution_policy);
SROOK_IS_EXECUTION_POLICY_TRUE_DEF(std::experimental::parallel::parallel_execution_policy);
SROOK_IS_EXECUTION_POLICY_TRUE_DEF(std::experimental::parallel::parallel_vector_execution_policy);
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(execution, srook)

#undef SROOK_IS_EXECUTION_POLICY_TRUE_DEF
#endif
