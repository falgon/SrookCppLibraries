// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_EQUAL_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_EQUAL_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/mpl/variadic_types/pack.hpp>
#include <srook/config/feature.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class, class> struct is_equal;

template <class... Ts>
struct is_equal<pack<Ts...>, pack<Ts...>> : SROOK_TRUE_TYPE {};

template <class... L, class... R>
struct is_equal<pack<L...>, pack<R...>> : SROOK_FALSE_TYPE {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_equal;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_equal_v = is_equal<L, R>::value;
#endif

} // namespace srook


#endif
#endif
