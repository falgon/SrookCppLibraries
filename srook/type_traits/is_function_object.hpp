// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_FUNCTION_OBJECT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_FUNCTION_OBJECT_HPP

#include <srook/type_traits/detail/config.hpp>
#include <srook/type_traits/is_object.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T, class... Args>
struct is_function_object 
    : type_traits::detail::Land<is_object<T>, is_invocable<T, Args...>> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class... Args>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_function_object_v = is_function_object<T, Args...>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_function_object;

} // namespace srook

#endif
