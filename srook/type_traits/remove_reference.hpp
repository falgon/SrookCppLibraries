// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_REMOVE_REFERENCE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_REMOVE_REFERENCE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/is_reference.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct remove_reference {
    typedef T type;
};

template <class T>
struct remove_reference<T&> : remove_reference<T> {
};

template <class T>
struct remove_reference<T&&> : remove_reference<T> {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::remove_reference;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
using remove_reference_t = typename remove_reference<T>::type;
#endif

} // namespace srook

#endif
