// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ADD_RVLAUE_REFERENCE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ADD_RVLAUE_REFERENCE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/is_reference.hpp>
#include <srook/type_traits/is_void.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, bool = !is_reference<T>::value && !is_void<T>::value>
struct add_rvalue_reference_impl {
    typedef T type;
};

template <class T>
struct add_rvalue_reference_impl<T, true> {
    typedef T&& type;
};

} // namespace detail

template <class T>
struct add_rvalue_reference : detail::add_rvalue_reference_impl<T> {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::add_rvalue_reference;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
#endif

} // namespace srook

#endif
