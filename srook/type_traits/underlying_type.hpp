// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_TYPE_TRAITS_UNDERYING_TYPE_HPP
#define INCLUDED_SROOK_TMPL_TYPE_TRAITS_UNDERYING_TYPE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/static_assert.hpp>
#include <srook/config/compiler.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct underlying_type 
#if defined(SROOK_GCC)
    : type_constant<__underlying_type(T)> {}
#else
{
    SROOK_STATIC_ASSERT((type_traits::detail::Lnot<is_same<T, T>>::value), "This environment is not supported");
}
#endif
;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
using underlying_type_t = SROOK_DEDUCED_TYPENAME underlying_type<T>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using type_traits::underlying_type;

} // namespace srook

#endif
