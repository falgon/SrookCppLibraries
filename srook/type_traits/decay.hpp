// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_DECAY_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_DECAY_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/add_pointer.hpp>
#include <srook/type_traits/is_array.hpp>
#include <srook/type_traits/is_function.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/remove_extent.hpp>
#include <srook/type_traits/remove_reference.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class U, bool = is_array<U>::value, bool = is_function<U>::value>
struct decay_impl;

template <class U>
struct decay_impl<U, false, false> {
    typedef typename remove_cv<U>::type type;
};

template <class U>
struct decay_impl<U, true, false> {
    typedef typename remove_extent<U>::type* type;
};

template <class U>
struct decay_impl<U, false, true> {
    typedef typename add_pointer<U>::type type;
};

} // namespace detail

template <class T>
struct decay {
    typedef typename detail::decay_impl<typename remove_reference<T>::type>::type type;
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::decay;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
using decay_t = typename decay<T>::type;
#endif

} // namespace srook

#endif
