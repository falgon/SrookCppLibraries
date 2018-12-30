// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_LIBRARY_CONCEPTS_HASH_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_LIBRARY_CONCEPTS_HASH_HPP

#include <srook/type_traits/detail/config.hpp>
#include <srook/type_traits/is_copy_constructible.hpp>
#include <srook/type_traits/is_destructible.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/is_function_object.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct is_hash 
    : type_traits::detail::Land<
        is_copy_constructible<T&>, 
        is_destructible<T>, 
        is_function_object<T, SROOK_DEDUCED_TYPENAME T::argument_type>,
        is_same<SROOK_DEDUCED_TYPENAME T::result_type, std::size_t>
    > {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_hash_v = is_hash<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::is_hash;

} // namespace srook

#endif
