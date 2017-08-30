// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ENABLE_IF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ENABLE_IF_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <bool, class>
struct enable_if;

template <class T>
struct enable_if<true, T> {
    typedef T type;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::enable_if;

#if SROOK_CPP_ALIAS_TEMPLATES
template <bool b, class T>
using enable_if_t = typename enable_if<b, T>::type;
#endif

} // namespace srook

#endif
