// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_CONJUNCTION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_CONJUNCTION_HPP
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/type_traits/detail/logical.hpp>

#if (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && SROOK_CPP_VARIADIC_TEMPLATES

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class... Ts>
struct conjunction : detail::Land<Ts...> {};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::conjunction;

#    if SROOK_CPP_VARIABLE_TEMPLATES
template <class... B>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool conjunction_v = type_traits::detail::conjunction<B...>::value;
#    endif

} // namespace srook

#endif
#endif
