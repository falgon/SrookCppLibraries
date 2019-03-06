// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_VECTOR_IMPL_H
#define INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_VECTOR_IMPL_H

#include <srook/config.hpp>
#include <srook/type_traits/detail/has_type_gen.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/tmpl/vt/at.hpp>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

SROOK_TT_DEF_HAS_TYPE_IMPL(exp_tag);
SROOK_TT_DEF_HAS_TYPE(exp_tag);

template <class...>
class vector_impl;

template <class... Xs>
struct is_onemore : bool_constant<(sizeof...(Xs) > 0)> {};

template <std::size_t I>
struct index_bind {
    template <class... Ts>
    struct generate : tmpl::vt::at<I, Ts...> {};
};

template <class>
struct is_vector : SROOK_FALSE_TYPE {};

template <class... Ts>
struct is_vector<vector_impl<Ts...>> : SROOK_TRUE_TYPE {};

} // namespace detail

template <class...>
class vector;

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)
#endif
