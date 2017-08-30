// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_RESULT_OF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_RESULT_OF_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/concepts/cxx17/invoke.hpp>
#include <utility>

namespace srook {
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPLUSPLUS < SROOK_CPLUSPLUS14_CONSTANT

template <class>
struct resulf_of;

template <class F, class... Param>
struct resulf_of<F(Param...)> {
    using type = decltype(cxx17::concept::INVOKE(std::declval<F>(), std::declval<Param>()...));
};

#elif SROOK_CPLUSPLUS <= SROOK_CPLUSPLUS14_CONSTANT

SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <typename Void, typename, typename...>
struct invoke_result {
};

template <typename F, typename... Args>
struct invoke_result<decltype(void(cxx17::concept::INVOKE(std::declval<F>(), std::declval<Args>()...))), F, Args...> {
    using type = decltype(cxx17::concept::INVOKE(std::declval<F>(), std::declval<Args>()...));
};
SROOK_INLINE_NAMESPACE_END

} // namespace detail

template <class>
struct
#if SROOK_CPLUSPLUS <= SROOK_CPLUSPLUS17_CONSTANT
    [[deprecated]]
#endif
    result_of;

template <class F, class... Param>
struct
#if SROOK_CPLUSPLUS == SROOK_CPLUSPLUS17_CONSTANT
    [[deprecated]]
#endif
    result_of<F(Param...)> : type_traits::detail::invoke_result<void, F, Param...>{};

template <class F, class... Param>
[[deprecated]] using result_of_t
#if SROOK_CPLUSPLUS == SROOK_CPLUSPLUS17_CONSTANT
    [[deprecated]]
#endif
    = typename result_of<F, Param...>::type;

#if SROOK_CPLUSPLUS == SROOK_CPLUSPLUS17_CONSTANT

template <class F, class... Param>
struct invoke_result : type_traits::detail::invoke_result<void, F, Param...> {
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class F, class... Param>
using invoke_result_t = typename invoke_result<F, Param...>::type;
#endif

#endif

#endif

} // namespace srook

#endif
