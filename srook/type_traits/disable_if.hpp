// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_DISABLE_IF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_DISABLE_IF_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <bool, class>
struct disable_if;

template <class T>
struct disable_if<false, T> {
    typedef T type;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::disable_if;

#if SROOK_CPP_ALIAS_TEMPLATES
template <bool b, class T>
using disable_if_t = typename disable_if<b, T>::type;
#endif

} // namespace srook

#endif
