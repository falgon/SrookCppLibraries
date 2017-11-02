// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_RESULT_OF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_RESULT_OF_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_VARIADIC_TEMPLATES
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/library_concepts/INVOKE.hpp>
#include <srook/utility/void_t.hpp>
#include <srook/utility/declval.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class, class, class...>
struct invoke_result;

template <class F, class... Args>
struct invoke_result<typename voider<decltype(library_concepts::INVOKE(declval<F>(), declval<Args>()...))>::type, F, Args...> {
	typedef decltype(library_concepts::INVOKE(declval<F>(), declval<Args>()...)) type;
};

} // namespace detail

template <class F, class... ArgTypes>
struct invoke_result : detail::invoke_result<void, F, ArgTypes...> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::invoke_result;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F, class... ArgTypes>
using invoke_result_t = typename invoke_result<F, ArgTypes...>::type;
#endif

} // namespace srook

#endif
#endif
