// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_NEGATION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_NEGATION_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <type_traits>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {
template <class B>
struct negation : bool_constant<!bool(B::value)> {
};
} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::negation;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class B>
constexpr bool negation_v = type_traits::detail::negation<B>::value;
#endif

} // namespace srook

#endif
