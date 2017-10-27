// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_CONJUNCTION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_CONJUNCTION_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <type_traits>

#if !SROOK_CPP_VARIADIC_TEMPLATES
#    error "must useable variadic templates"
#else

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class...>
struct conjunction : std::true_type {
};

template <class B1>
struct conjunction<B1> : B1 {
};

template <class B1, class... Bn>
struct conjunction<B1, Bn...> : std::conditional<bool(B1::value), conjunction<Bn...>, B1>::type {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::conjunction;

#    if SROOK_CPP_VARIABLE_TEMPLATES
template <class... B>
SROOK_INLINE_VARIABLE constexpr bool conjunction_v = type_traits::detail::conjunction<B...>::value;
#    endif

} // namespace srook

#endif
#endif
