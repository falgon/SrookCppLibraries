// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_DERIVATION_INVOKE_RESULT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_DERIVATION_INVOKE_RESULT_HPP
#include <srook/type_traits/detail/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_VARIADIC_TEMPLATES
#include <srook/type_traits/arguments.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/transfer.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class F>
struct derivation_invoke_result 
    : srook::tmpl::vt::transfer<invoke_result, SROOK_DEDUCED_TYPENAME srook::tmpl::vt::concat<F, SROOK_DEDUCED_TYPENAME arguments<F>::type>::type>::type {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F>
using derivation_invoke_result_t = SROOK_DEDUCED_TYPENAME derivation_invoke_result<F>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::derivation_invoke_result;

} // namespace srook

#endif
#endif
